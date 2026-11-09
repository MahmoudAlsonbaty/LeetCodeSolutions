#!/usr/bin/env python3
"""Scaffold a LeetCode problem folder from its URL.

Usage (from anywhere, once the repo root is on PATH):
    lc <url-or-slug>               solved problem  -> Problems/P1 - Two Sum - Easy/main.cpp
    lc <url-or-slug> --attempt     attempt         -> Problems/AT-P1 - Two Sum - Easy/main.cpp
    lc --promote <url-or-slug>     rename an AT- attempt to a solved folder

By default the problem's starter code (class Solution + function signature) is
fetched from LeetCode's public API, no login needed. With --clipboard, code you
copied from the editor is used instead, when it looks like this problem's code.

The file is built from templates/main.<ext>. Placeholders:
    {{SOLUTION}} {{FUNCTION}} {{NUMBER}} {{TITLE}} {{DIFFICULTY}} {{SLUG}} {{URL}}

Standard library only, so it runs anywhere Python 3.9+ is installed.
"""
from __future__ import annotations

import argparse
import json
import platform
import re
import shutil
import subprocess
import sys
import urllib.request
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parent
PROBLEMS_DIR = ROOT / "Problems"
TEMPLATES_DIR = ROOT / "templates"
CONFIG_PATH = ROOT / ".github" / "readme" / "config.json"

# Keep in sync with .github/readme/generate_readme.py
ATTEMPT_PREFIX = "AT-"

# LeetCode langSlug -> file extension. Add a templates/main.<ext> to support more.
LANGUAGES = {"cpp": "cpp", "python3": "py", "java": "java", "c": "c"}

GRAPHQL_URL = "https://leetcode.com/graphql"
QUESTION_QUERY = """query q($slug: String!) {
  question(titleSlug: $slug) {
    questionFrontendId title titleSlug difficulty isPaidOnly metaData
    codeSnippets { langSlug code }
  }
}"""

INVALID_PATH_CHARS = re.compile(r'[<>:"/\\|?*]')


class LcError(Exception):
    """A user-facing error: printed without a traceback."""


@dataclass
class Question:
    number: str
    title: str
    slug: str
    difficulty: str
    function: str
    snippets: dict[str, str]
    paid: bool

    @property
    def url(self) -> str:
        return f"https://leetcode.com/problems/{self.slug}/"

    @property
    def folder_title(self) -> str:
        """Title made safe for Windows paths ('?', ':' and friends removed)."""
        return INVALID_PATH_CHARS.sub("", self.title).strip()

    def folder_name(self, attempt: bool) -> str:
        name = f"P{self.number} - {self.folder_title} - {self.difficulty}"
        return ATTEMPT_PREFIX + name if attempt else name


# ---------------------------------------------------------------- LeetCode

def parse_slug(value: str) -> str:
    """Accept a full URL (any sub-page), a contest problem URL, or a bare slug."""
    value = value.strip()
    if m := re.search(r"/problems/([a-z0-9-]+)", value):
        return m[1]
    if re.fullmatch(r"[a-z0-9-]+", value):
        return value
    raise LcError(f"Can't find a problem slug in '{value}'. "
                  "Pass a link like https://leetcode.com/problems/two-sum/")


def fetch_question(slug: str) -> Question:
    body = json.dumps({"query": QUESTION_QUERY, "variables": {"slug": slug}}).encode()
    request = urllib.request.Request(GRAPHQL_URL, data=body, headers={
        "Content-Type": "application/json",
        "Referer": "https://leetcode.com",
        "User-Agent": "Mozilla/5.0 (lc-scaffold)",
    })
    try:
        with urllib.request.urlopen(request, timeout=20) as response:
            q = (json.load(response).get("data") or {}).get("question")
    except Exception as error:
        raise LcError(f"Couldn't reach LeetCode: {error}") from error
    if not q:
        raise LcError(f"No LeetCode problem with slug '{slug}'.")

    meta = json.loads(q.get("metaData") or "{}")
    # Regular problems expose "name"; design problems (LRU Cache...) expose "classname".
    function = meta.get("name") or meta.get("classname") or "solve"
    return Question(
        number=q["questionFrontendId"],
        title=q["title"],
        slug=q["titleSlug"],
        difficulty=q["difficulty"],
        function=function,
        snippets={s["langSlug"]: s["code"] for s in (q.get("codeSnippets") or [])},
        paid=bool(q.get("isPaidOnly")),
    )


# ---------------------------------------------------------------- clipboard

def read_clipboard() -> str:
    """Best effort, per OS. Returns '' when nothing can be read."""
    system = platform.system()
    commands = {
        "Windows": [["powershell", "-NoProfile", "-Command",
                     "[Console]::OutputEncoding=[Text.Encoding]::UTF8; Get-Clipboard -Raw"]],
        "Darwin": [["pbpaste"]],
    }.get(system, [["wl-paste", "--no-newline"], ["xclip", "-selection", "clipboard", "-o"]])
    for cmd in commands:
        if not shutil.which(cmd[0]):
            continue
        try:
            out = subprocess.run(cmd, capture_output=True, timeout=5, check=True).stdout
            return out.decode("utf-8", errors="replace").replace("\r\n", "\n")
        except (OSError, subprocess.SubprocessError):
            continue
    return ""


def pick_solution(question: Question, lang: str, use_clipboard: bool) -> tuple[str, str]:
    """Return (code, source description)."""
    if use_clipboard:
        clip = read_clipboard().strip()
        # Only trust the clipboard if it is plausibly this problem's code,
        # so a stale copied URL or text never lands in main.cpp.
        if clip and question.function in clip:
            return clip, "clipboard"
        if clip:
            print(f"  ! Clipboard doesn't mention '{question.function}', ignoring it.")
    snippet = question.snippets.get(lang)
    if snippet is None:
        raise LcError(f"LeetCode has no '{lang}' starter code for this problem.")
    return snippet.strip(), "LeetCode starter code"


# ---------------------------------------------------------------- files

def render(template: str, question: Question, solution: str) -> str:
    values = {
        "SOLUTION": solution,
        "FUNCTION": question.function,
        "NUMBER": question.number,
        "TITLE": question.title,
        "DIFFICULTY": question.difficulty,
        "SLUG": question.slug,
        "URL": question.url,
    }
    for key, value in values.items():
        template = template.replace("{{" + key + "}}", value)
    return template


def slugify(title: str) -> str:
    """Same rule as generate_readme.py, to detect when an override is needed."""
    cleaned = re.sub(r"[^a-z0-9\s-]", "", title.lower())
    return re.sub(r"[\s-]+", "-", cleaned).strip("-")


def ensure_slug_override(question: Question) -> None:
    """Keep README links correct when the folder title can't reproduce LeetCode's slug."""
    if slugify(question.folder_title) == question.slug or not CONFIG_PATH.exists():
        return
    config = json.loads(CONFIG_PATH.read_text(encoding="utf-8"))
    overrides = config.setdefault("slug_overrides", {})
    if overrides.get(question.number) != question.slug:
        overrides[question.number] = question.slug
        CONFIG_PATH.write_text(json.dumps(config, indent=2) + "\n", encoding="utf-8")
        print(f"  + Added slug override {question.number} -> {question.slug} to config.json")


def find_existing(number: str) -> list[Path]:
    """Any folder for this problem number, solved or attempted."""
    if not PROBLEMS_DIR.is_dir():
        return []
    pattern = re.compile(rf"^({re.escape(ATTEMPT_PREFIX)})?P{number} - ")
    return [p for p in PROBLEMS_DIR.iterdir() if p.is_dir() and pattern.match(p.name)]


def open_in_editor(path: Path) -> None:
    code = shutil.which("code")
    if code:
        subprocess.run([code, "-r", str(path)], check=False)


# ---------------------------------------------------------------- commands

def create(args: argparse.Namespace) -> Path:
    question = fetch_question(parse_slug(args.problem))
    ext = LANGUAGES.get(args.lang)
    template_path = TEMPLATES_DIR / f"main.{ext}"
    if ext is None or not template_path.exists():
        raise LcError(f"No template for '{args.lang}'. Expected {template_path}")

    folder = PROBLEMS_DIR / question.folder_name(args.attempt)
    target = folder / template_path.name
    others = [p for p in find_existing(question.number) if p != folder]
    if others:
        print("  ! Problem already has: " + ", ".join(p.name for p in others))
    if target.exists() and not args.force:
        raise LcError(f"{target.relative_to(ROOT)} already exists. Use --force to overwrite.")

    solution, source = pick_solution(question, args.lang, args.clipboard)
    template = template_path.read_text(encoding="utf-8")
    folder.mkdir(parents=True, exist_ok=True)
    target.write_text(render(template, question, solution), encoding="utf-8")
    if not args.attempt:
        ensure_slug_override(question)

    if question.paid:
        print("  ! Premium problem.")
    print(f"Created {target.relative_to(ROOT)}  (solution from {source}, function '{question.function}')")
    return target


def promote(args: argparse.Namespace) -> Path:
    question = fetch_question(parse_slug(args.problem))
    source = PROBLEMS_DIR / question.folder_name(attempt=True)
    target = PROBLEMS_DIR / question.folder_name(attempt=False)
    if not source.is_dir():
        raise LcError(f"No attempt folder {source.relative_to(ROOT)}")
    if target.exists():
        raise LcError(f"{target.relative_to(ROOT)} already exists.")
    # git mv keeps history when the attempt was committed; plain rename otherwise.
    tracked = subprocess.run(["git", "ls-files", "--error-unmatch", str(source)],
                             cwd=ROOT, capture_output=True).returncode == 0
    if tracked:
        subprocess.run(["git", "mv", str(source), str(target)], cwd=ROOT, check=True)
    else:
        source.rename(target)
    ensure_slug_override(question)
    print(f"Promoted to {target.relative_to(ROOT)}")
    return target


def main() -> None:
    parser = argparse.ArgumentParser(prog="lc", description="Scaffold a LeetCode problem folder.")
    parser.add_argument("problem", help="problem URL or slug")
    parser.add_argument("-a", "--attempt", action="store_true",
                        help=f"create an attempt folder ({ATTEMPT_PREFIX}P...), ignored by the README workflow")
    parser.add_argument("--promote", action="store_true",
                        help="rename an existing attempt folder to a solved one")
    parser.add_argument("-l", "--lang", default="cpp", choices=sorted(LANGUAGES),
                        help="LeetCode language (default: cpp)")
    parser.add_argument("-c", "--clipboard", action="store_true",
                        help="use code copied from the editor instead of the starter code")
    parser.add_argument("-f", "--force", action="store_true", help="overwrite an existing file")
    parser.add_argument("-o", "--open", action="store_true", help="open the file in VS Code")
    args = parser.parse_args()

    try:
        path = promote(args) if args.promote else create(args)
    except LcError as error:
        sys.exit(f"Error: {error}")
    if args.open:
        open_in_editor(path)


if __name__ == "__main__":
    main()
