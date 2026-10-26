#!/usr/bin/env python3
"""Generate the README stats block and SVG cards from the repo's folders.

The folder names are the single source of truth:
    Problems/P1 - Two Sum - Easy        -> a solved problem
    Contests/Biweekly Contest 194       -> a contest (its P1, P2... are contest-local)

Everything between <!-- STATS:START --> and <!-- STATS:END --> in README.md,
and every file in .github/readme/assets/, is regenerated on each run.

Standard library only, so the GitHub Action needs no `pip install`.
"""
from __future__ import annotations

import html
import json
import math
import re
import subprocess
import sys
import urllib.request
from collections import Counter
from dataclasses import dataclass, field
from datetime import date, datetime, timedelta, timezone
from pathlib import Path
from urllib.parse import quote

TOOL_DIR = Path(__file__).resolve().parent          # .github/readme
ROOT = TOOL_DIR.parent.parent
README = ROOT / "README.md"
PROBLEMS_DIR = ROOT / "Problems"
CONTESTS_DIR = ROOT / "Contests"
ASSETS = TOOL_DIR / "assets"
CACHE_PATH = TOOL_DIR / "cache.json"
CONFIG_PATH = TOOL_DIR / "config.json"
ASSETS_URL = "./" + ASSETS.relative_to(ROOT).as_posix()

PROBLEM_RE = re.compile(r"^P(\d+) - (.+) - (Easy|Medium|Hard)$")
CONTEST_RE = re.compile(r"^(Weekly|Biweekly) Contest (\d+)$")
MARKER_RE = re.compile(r"(<!-- STATS:START -->)(.*?)(<!-- STATS:END -->)", re.DOTALL)

DIFFICULTIES = ("Easy", "Medium", "Hard")
DIFF_COLORS = {"Easy": "#00b8a3", "Medium": "#ffc01e", "Hard": "#ff375f"}

THEMES = {
    "dark": {
        "bg": "#282828", "border": "#3e3e3e", "text": "#eff1f6", "muted": "#9a9a9a",
        "track": "#3e3e3e", "pill": "#3e3e3e", "divider": "#3e3e3e",
        "bar_track": {"Easy": "#2c3b38", "Medium": "#47402a", "Hard": "#4a2c32"},
        "heat": ["#393939", "#0e4429", "#006d32", "#26a641", "#39d353"],
    },
    "light": {
        "bg": "#ffffff", "border": "#e5e5e5", "text": "#262626", "muted": "#8c8c8c",
        "track": "#f0f0f0", "pill": "#f2f3f4", "divider": "#ebebeb",
        "bar_track": {"Easy": "#e2f6f3", "Medium": "#fff6dd", "Hard": "#ffe7ec"},
        "heat": ["#ebedf0", "#9be9a8", "#40c463", "#30a14e", "#216e39"],
    },
}

LANGUAGES = {
    ".cpp": "C++", ".cc": "C++", ".cxx": "C++", ".c": "C", ".py": "Python",
    ".java": "Java", ".js": "JavaScript", ".ts": "TypeScript", ".go": "Go",
    ".rs": "Rust", ".cs": "C#", ".kt": "Kotlin", ".swift": "Swift", ".rb": "Ruby",
    ".dart": "Dart", ".php": "PHP", ".scala": "Scala", ".sql": "SQL",
}

# Mirrors the Advanced / Intermediate / Fundamental grouping on LeetCode profiles.
# Tags not listed here fall into Intermediate.
ADVANCED = {
    "Dynamic Programming", "Backtracking", "Divide and Conquer", "Trie", "Union Find",
    "Monotonic Stack", "Monotonic Queue", "Segment Tree", "Binary Indexed Tree",
    "Topological Sort", "Shortest Path", "Bitmask", "Graph", "Minimum Spanning Tree",
    "Strongly Connected Component", "Eulerian Circuit", "Biconnected Component",
    "Rolling Hash", "Suffix Array", "Line Sweep", "Memoization", "Game Theory",
    "Combinatorics", "Number Theory", "Geometry", "Hash Function", "String Matching",
    "Ordered Set", "Quickselect", "Probability and Statistics", "Reservoir Sampling",
}
FUNDAMENTAL = {
    "Array", "String", "Sorting", "Two Pointers", "Linked List", "Matrix", "Simulation",
    "Stack", "Queue", "Enumeration", "Counting Sort", "Bucket Sort", "Radix Sort",
    "Merge Sort", "Brainteaser", "Database", "Shell", "Concurrency",
}
SKILL_LEVELS = (("Advanced", "Hard"), ("Intermediate", "Medium"), ("Fundamental", "Easy"))

GRAPHQL_URL = "https://leetcode.com/graphql"
QUESTION_QUERY = """query q($slug: String!) {
  question(titleSlug: $slug) { questionFrontendId difficulty acRate topicTags { name } }
}"""
TOTALS_QUERY = "{ allQuestionsCount { difficulty count } }"
CALENDAR_QUERY = """query userProfileCalendar($username: String!) {
  matchedUser(username: $username) {
    userCalendar { streak totalActiveDays submissionCalendar }
  }
}"""


# ---------------------------------------------------------------- model

@dataclass
class Problem:
    number: int
    title: str
    difficulty: str
    folder: str
    languages: list[str] = field(default_factory=list)
    solved: date | None = None
    tags: list[str] = field(default_factory=list)
    ac_rate: float | None = None
    slug: str = ""


@dataclass
class Contest:
    kind: str
    number: int
    folder: str
    solved: int
    date: date | None


# ---------------------------------------------------------------- helpers

def slugify(title: str) -> str:
    """'Pow(x, n)' -> 'powx-n', matching LeetCode's URL slugs for most titles."""
    cleaned = re.sub(r"[^a-z0-9\s-]", "", title.lower())
    return re.sub(r"[\s-]+", "-", cleaned).strip("-")


def git_first_commit_date(folder: str) -> date | None:
    """Date the folder first appeared in git history (used as the 'solved' date)."""
    try:
        out = subprocess.run(
            ["git", "log", "--diff-filter=A", "--format=%cs", "--", folder],
            cwd=ROOT, capture_output=True, text=True, check=True,
        ).stdout.split()
    except (OSError, subprocess.CalledProcessError):
        return None
    return date.fromisoformat(out[-1]) if out else None


def detect_languages(path: Path) -> list[str]:
    found = {
        LANGUAGES[f.suffix.lower()]
        for f in path.rglob("*")
        if f.is_file() and f.suffix.lower() in LANGUAGES
        and not any(part.startswith(".") for part in f.relative_to(path).parts)
    }
    return sorted(found)


def graphql(query: str, variables: dict | None = None) -> dict | None:
    body = json.dumps({"query": query, "variables": variables or {}}).encode()
    request = urllib.request.Request(GRAPHQL_URL, data=body, headers={
        "Content-Type": "application/json",
        "Referer": "https://leetcode.com",
        "User-Agent": "Mozilla/5.0 (leetcode-readme-generator)",
    })
    try:
        with urllib.request.urlopen(request, timeout=20) as response:
            return json.load(response).get("data")
    except Exception as error:  # network trouble must never fail the build
        print(f"  ! LeetCode API unavailable: {error}")
        return None


def esc(text: str) -> str:
    return html.escape(str(text), quote=True)


def text_width(text: str, size: float = 12, bold: bool = False) -> float:
    """Rough width estimate for a system sans-serif font."""
    return len(text) * size * (0.6 if bold else 0.54)


def text_run(x: float, y: float, pieces: list[tuple[str, str, float, bool]],
             anchor: str = "start") -> str:
    """One line made of differently styled pieces: (text, color, size, bold).

    Some renderers anchor each <tspan> separately when text-anchor is end or
    middle, so we compute the start x ourselves and always anchor at start.
    The pieces then flow naturally; only the line's position is estimated.
    """
    total = sum(text_width(t, s, b) for t, _, s, b in pieces)
    start = x - total if anchor == "end" else x - total / 2 if anchor == "middle" else x
    bold_attr = ' font-weight="600"'
    spans = "".join(
        f'<tspan fill="{color}" font-size="{size}"{bold_attr if bold else ""}>{esc(t)}</tspan>'
        for t, color, size, bold in pieces
    )
    return f'<text x="{start:.1f}" y="{y}" xml:space="preserve">{spans}</text>'


def fmt_date(value: date | None) -> str:
    return value.strftime("%b %d, %Y") if value else "-"


# ---------------------------------------------------------------- scanning

def scan() -> tuple[list[Problem], list[Contest]]:
    problems: list[Problem] = []
    contests: list[Contest] = []
    invalid: list[str] = []

    def subfolders(parent: Path) -> list[Path]:
        if not parent.is_dir():
            return []
        return sorted(p for p in parent.iterdir() if p.is_dir() and not p.name.startswith("."))

    for path in subfolders(PROBLEMS_DIR):
        rel = path.relative_to(ROOT).as_posix()
        if m := PROBLEM_RE.match(path.name):
            problems.append(Problem(
                number=int(m[1]), title=m[2].strip(), difficulty=m[3], folder=rel,
                languages=detect_languages(path), solved=git_first_commit_date(rel),
            ))
        else:
            invalid.append(f"{rel}' must look like 'P123 - Title - Easy|Medium|Hard")

    for path in subfolders(CONTESTS_DIR):
        rel = path.relative_to(ROOT).as_posix()
        if m := CONTEST_RE.match(path.name):
            solved = sum(1 for p in subfolders(path) if PROBLEM_RE.match(p.name))
            contests.append(Contest(m[1], int(m[2]), rel, solved, git_first_commit_date(rel)))
        else:
            invalid.append(f"{rel}' must look like 'Weekly Contest 123' or 'Biweekly Contest 123")

    numbers = Counter(p.number for p in problems)
    duplicates = [n for n, c in numbers.items() if c > 1]

    if invalid or duplicates:
        print("Folder naming errors:")
        for message in invalid:
            print(f"  x '{message}'")
        for n in duplicates:
            print(f"  x problem {n} appears in more than one folder")
        sys.exit(1)

    return problems, contests


@dataclass
class Activity:
    """Daily activity for the heatmap, from LeetCode or (as a fallback) from git."""
    per_day: Counter
    noun: str                      # "submissions" (LeetCode) or "solved" (git fallback)
    active_days: int | None = None  # LeetCode's own numbers, when available
    max_streak: int | None = None


def fetch_calendar(cache: dict, username: str | None) -> None:
    """Refresh the cached LeetCode submission calendar (the profile heatmap's data)."""
    if not username:
        return
    data = graphql(CALENDAR_QUERY, {"username": username})
    user = (data or {}).get("matchedUser")
    if data is not None and not user:
        print(f"  ! LeetCode user '{username}' not found. Check leetcode_username in config.json.")
    calendar = (user or {}).get("userCalendar")
    if not calendar:
        return  # keep whatever was cached last time
    raw = json.loads(calendar.get("submissionCalendar") or "{}")
    days = {
        datetime.fromtimestamp(int(ts), timezone.utc).date().isoformat(): count
        for ts, count in raw.items() if count
    }
    cache["calendar"] = {
        "username": username,
        "days": days,
        "streak": calendar.get("streak"),
        "totalActiveDays": calendar.get("totalActiveDays"),
    }


def load_activity(cache: dict, problems: list[Problem], username: str | None) -> Activity:
    calendar = cache.get("calendar")
    if calendar and calendar.get("username") == username:
        per_day = Counter({date.fromisoformat(d): n for d, n in calendar["days"].items()})
        return Activity(per_day, "submissions", calendar.get("totalActiveDays"), calendar.get("streak"))
    print("  ! No LeetCode calendar available, falling back to git commit dates.")
    return Activity(Counter(p.solved for p in problems if p.solved), "solved")


def enrich(problems: list[Problem], config: dict) -> tuple[dict | None, Activity]:
    """Attach LeetCode metadata, fetching only problems missing from the cache."""
    cache = json.loads(CACHE_PATH.read_text()) if CACHE_PATH.exists() else {}
    questions = cache.setdefault("questions", {})
    overrides = config.get("slug_overrides", {})

    for p in problems:
        key = str(p.number)
        p.slug = overrides.get(key) or slugify(p.title)
        if key not in questions:
            data = graphql(QUESTION_QUERY, {"slug": p.slug})
            q = (data or {}).get("question")
            if q and q["questionFrontendId"] == key:
                questions[key] = {
                    "slug": p.slug,
                    "difficulty": q["difficulty"],
                    "acRate": round(q["acRate"], 1),
                    "tags": [t["name"] for t in q["topicTags"]],
                }
            elif q:
                print(f"  ! P{key}: slug '{p.slug}' belongs to problem "
                      f"{q['questionFrontendId']}. Add the right slug to slug_overrides.")
            elif data is not None:
                print(f"  ! P{key}: no LeetCode problem with slug '{p.slug}'. "
                      f"Add it to slug_overrides in scripts/config.json.")
        if meta := questions.get(key):
            p.slug, p.tags, p.ac_rate = meta["slug"], meta["tags"], meta["acRate"]
            if meta["difficulty"] != p.difficulty:
                print(f"  ! P{key}: folder says {p.difficulty}, LeetCode says {meta['difficulty']}")

    # Total problem counts change as LeetCode adds problems, so refresh each run.
    data = graphql(TOTALS_QUERY)
    if data and data.get("allQuestionsCount"):
        cache["totals"] = {row["difficulty"]: row["count"] for row in data["allQuestionsCount"]}

    username = config.get("leetcode_username")
    fetch_calendar(cache, username)

    CACHE_PATH.parent.mkdir(exist_ok=True)
    CACHE_PATH.write_text(json.dumps(cache, indent=2, sort_keys=True) + "\n")
    return cache.get("totals"), load_activity(cache, problems, username)


# ---------------------------------------------------------------- SVG cards

def svg(width: int, height: int, theme: dict, style: str, body: str, label: str) -> str:
    return (
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" '
        f'viewBox="0 0 {width} {height}" role="img" aria-label="{esc(label)}">\n'
        f"<style>\n"
        f"text{{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',Helvetica,Arial,sans-serif;"
        f"white-space:pre}}\n"
        f".fade{{opacity:0;animation:fade .5s ease-out forwards}}\n"
        f"@keyframes fade{{to{{opacity:1}}}}\n"
        f"{style}</style>\n"
        f'<rect x=".5" y=".5" width="{width - 1}" height="{height - 1}" rx="12" '
        f'fill="{theme["bg"]}" stroke="{theme["border"]}"/>\n'
        f"{body}</svg>\n"
    )


def card_stats(problems: list[Problem], totals: dict | None, theme: dict) -> str:
    counts = {d: sum(p.difficulty == d for p in problems) for d in DIFFICULTIES}
    total = len(problems)
    width, height = 720, 200
    cx, cy, r = 110, 100, 62
    circumference = 2 * math.pi * r
    parts: list[str] = []
    style = [
        ".arc{fill:none;stroke-width:9}",
        ".bar{transform-box:fill-box;transform-origin:left;transform:scaleX(0);"
        "animation:grow .9s ease-out forwards}",
        "@keyframes grow{to{transform:scaleX(1)}}",
    ]

    # Ring: one arc per difficulty, drawn in sequence.
    parts.append(f'<g transform="rotate(-90 {cx} {cy})">')
    parts.append(f'<circle cx="{cx}" cy="{cy}" r="{r}" class="arc" stroke="{theme["track"]}"/>')
    nonzero = [d for d in DIFFICULTIES if counts[d]]
    gap = 4 if len(nonzero) > 1 else 0
    offset = 0.0
    for i, d in enumerate(nonzero):
        length = circumference * counts[d] / total - gap
        style.append(f"@keyframes arc{i}{{to{{stroke-dasharray:{length:.1f} {circumference:.1f}}}}}")
        parts.append(
            f'<circle cx="{cx}" cy="{cy}" r="{r}" class="arc" stroke="{DIFF_COLORS[d]}" '
            f'stroke-dasharray="0 {circumference:.1f}" stroke-dashoffset="{-offset:.1f}" '
            f'style="animation:arc{i} .9s ease-out {i * .25:.2f}s forwards"/>'
        )
        offset += length + gap
    parts.append("</g>")

    all_total = (totals.get("All") or sum(totals.get(d, 0) for d in DIFFICULTIES)) if totals else None
    center = [(str(total), theme["text"], 32, True)]
    if all_total:
        center.append((f"/{all_total}", theme["muted"], 13, False))
    parts.append(text_run(cx, cy + 4, center, "middle"))
    parts.append(f'<text x="{cx}" y="{cy + 26}" text-anchor="middle" fill="{theme["muted"]}" '
                 f'font-size="12">Solved</text>')

    # Difficulty bars, out of LeetCode's totals when available.
    x0, bar_w = 215, 270
    for i, d in enumerate(DIFFICULTIES):
        y = 56 + i * 48
        out_of = (totals or {}).get(d)
        share = counts[d] / out_of if out_of else (counts[d] / total if total else 0)
        fill = max(bar_w * share, 8 if counts[d] else 0)
        parts.append(f'<text x="{x0}" y="{y}" fill="{DIFF_COLORS[d]}" font-size="13" '
                     f'font-weight="600">{d}</text>')
        count_text = [(str(counts[d]), theme["text"], 13, True)]
        if out_of:
            count_text.append((f"/{out_of}", theme["muted"], 13, False))
        parts.append(text_run(x0 + bar_w, y, count_text, "end"))
        parts.append(f'<rect x="{x0}" y="{y + 8}" width="{bar_w}" height="8" rx="4" '
                     f'fill="{theme["bar_track"][d]}"/>')
        if fill:
            parts.append(f'<rect x="{x0}" y="{y + 8}" width="{fill:.1f}" height="8" rx="4" '
                         f'fill="{DIFF_COLORS[d]}" class="bar" style="animation-delay:{i * .15:.2f}s"/>')

    # Languages column.
    lx = 530
    parts.append(f'<line x1="{lx - 18}" y1="28" x2="{lx - 18}" y2="{height - 28}" '
                 f'stroke="{theme["divider"]}"/>')
    parts.append(f'<text x="{lx}" y="44" fill="{theme["text"]}" font-size="14" '
                 f'font-weight="600">Languages</text>')
    langs = Counter(lang for p in problems for lang in p.languages).most_common(4)
    if not langs:
        parts.append(f'<text x="{lx}" y="76" fill="{theme["muted"]}" font-size="12">'
                     f'No solution files yet</text>')
    for i, (lang, n) in enumerate(langs):
        y = 66 + i * 32
        w = text_width(lang) + 20
        parts.append(f'<g class="fade" style="animation-delay:{.3 + i * .1:.2f}s">'
                     f'<rect x="{lx}" y="{y}" width="{w:.0f}" height="22" rx="11" fill="{theme["pill"]}"/>'
                     f'<text x="{lx + w / 2:.1f}" y="{y + 15}" text-anchor="middle" '
                     f'fill="{theme["text"]}" font-size="12">{esc(lang)}</text>'
                     + text_run(width - 22, y + 15, [(str(n), theme["text"], 12, True),
                                                     (" solved", theme["muted"], 12, False)], "end")
                     + "</g>")

    label = f"{total} solved: " + ", ".join(f"{counts[d]} {d}" for d in DIFFICULTIES)
    return svg(width, height, theme, "\n".join(style) + "\n", "\n".join(parts) + "\n", label)


def card_heatmap(activity: Activity, theme: dict, today: date) -> str:
    per_day = activity.per_day
    last_sunday = today - timedelta(days=(today.weekday() + 1) % 7)
    start = last_sunday - timedelta(weeks=52)
    days = [start + timedelta(days=i) for i in range((today - start).days + 1)]

    in_year = sum(per_day[d] for d in days)
    active = sum(1 for d in days if per_day[d])
    streak = best = 0
    for d in days:
        streak = streak + 1 if per_day[d] else 0
        best = max(best, streak)
    # Prefer LeetCode's own figures so the card matches the profile page.
    active = activity.active_days if activity.active_days is not None else active
    best = activity.max_streak if activity.max_streak is not None else best
    # Shade relative to the busiest day, since submission counts vary a lot.
    peak = max((per_day[d] for d in days), default=0)

    width, height, step, cell = 720, 180, 13, 10
    x0, y0 = 18, 54
    heat = theme["heat"]
    parts = [
        text_run(20, 34, [(str(in_year), theme["text"], 14, True),
                          (f" {activity.noun} in the past year", theme["muted"], 14, False)]),
        text_run(width - 20, 34, [("Total active days: ", theme["muted"], 12, False),
                                  (str(active), theme["text"], 12, True),
                                  ("    Max streak: ", theme["muted"], 12, False),
                                  (str(best), theme["text"], 12, True)], "end"),
    ]

    last_label_col = -10
    for i, d in enumerate(days):
        col, row = divmod(i, 7)
        n = per_day[d]
        level = 0 if n == 0 else max(1, math.ceil(4 * n / peak))
        parts.append(f'<rect x="{x0 + col * step}" y="{y0 + row * step}" width="{cell}" '
                     f'height="{cell}" rx="2" fill="{heat[level]}" class="fade" '
                     f'style="animation-delay:{col * 12}ms"/>')
        if row == 0 and d.day <= 7 and col - last_label_col >= 4:
            parts.append(f'<text x="{x0 + col * step}" y="{y0 + 7 * step + 14}" '
                         f'fill="{theme["muted"]}" font-size="11">{d.strftime("%b")}</text>')
            last_label_col = col

    return svg(width, height, theme, "", "\n".join(parts) + "\n",
               f"{in_year} {activity.noun} in the past year, {active} active days, max streak {best}")


def card_skills(problems: list[Problem], theme: dict) -> str | None:
    tags = Counter(t for p in problems for t in p.tags)
    if not tags:
        return None

    def level(tag: str) -> str:
        return "Advanced" if tag in ADVANCED else "Fundamental" if tag in FUNDAMENTAL else "Intermediate"

    width, x_pills, right, row_h = 720, 150, 700, 32
    parts = [f'<text x="20" y="36" fill="{theme["text"]}" font-size="14" font-weight="600">Skills</text>']
    y, index = 58, 0
    for name, color_key in SKILL_LEVELS:
        group = sorted(((t, n) for t, n in tags.items() if level(t) == name), key=lambda x: (-x[1], x[0]))
        if not group:
            continue
        parts.append(f'<circle cx="24" cy="{y + 11}" r="4" fill="{DIFF_COLORS[color_key]}"/>')
        parts.append(f'<text x="34" y="{y + 15}" fill="{theme["text"]}" font-size="13">{name}</text>')
        x = x_pills
        for tag, n in group:
            count = f" x{n}"
            w = text_width(tag) + text_width(count) + 22
            if x + w > right:
                x, y = x_pills, y + row_h
            parts.append(
                f'<g class="fade" style="animation-delay:{index * 40}ms">'
                f'<rect x="{x}" y="{y}" width="{w:.0f}" height="22" rx="11" fill="{theme["pill"]}"/>'
                + text_run(x + 11, y + 15, [(tag, theme["text"], 12, False),
                                            (count, theme["muted"], 12, False)])
                + "</g>"
            )
            x += w + 8
            index += 1
        y += row_h + 6

    return svg(width, y + 6, theme, "", "\n".join(parts) + "\n",
               "Topics covered: " + ", ".join(f"{t} ({n})" for t, n in tags.most_common()))


# ---------------------------------------------------------------- banner

SYNTAX = {
    "dark": {"kw": "#569cd6", "type": "#4ec9b0", "fn": "#dcdcaa", "cm": "#6a9955",
             "p": "#d4d4d4", "editor": "#1e1e1e", "bar": "#282828", "gutter": "#6e7681"},
    "light": {"kw": "#0000ff", "type": "#267f99", "fn": "#795e26", "cm": "#008000",
              "p": "#262626", "editor": "#ffffff", "bar": "#f7f7f8", "gutter": "#a0a0a0"},
}
ACCEPTED = "#2cbb5d"
MONO = "ui-monospace,SFMono-Regular,Menlo,Consolas,'Liberation Mono',monospace"


def banner_code(language: str, total: int) -> tuple[str, list[list[tuple[str, str]]]]:
    """A tiny 'solution' in the user's main language. Tokens are (text, syntax kind)."""
    comment = f"{total} and counting"
    if language == "Python":
        return "solution.py", [
            [("class", "kw"), (" ", "p"), ("Solution", "type"), (":", "p")],
            [("    ", "p"), ("def", "kw"), (" ", "p"), ("solved", "fn"), ("(self, p: ", "p"),
             ("list", "type"), (") -> ", "p"), ("int", "type"), (":", "p")],
            [("        ", "p"), ("return", "kw"), (" ", "p"), ("len", "fn"), ("(p)  ", "p"),
             (f"# {comment}", "cm")],
        ]
    if language == "Java":
        return "Solution.java", [
            [("class", "kw"), (" ", "p"), ("Solution", "type"), (" {", "p")],
            [("    ", "p"), ("public", "kw"), (" ", "p"), ("int", "kw"), (" ", "p"),
             ("solved", "fn"), ("(", "p"), ("List", "type"), ("<", "p"), ("Problem", "type"),
             ("> p) {", "p")],
            [("        ", "p"), ("return", "kw"), (" p.", "p"), ("size", "fn"), ("(); ", "p"),
             (f"// {comment}", "cm")],
            [("    }", "p")],
            [("}", "p")],
        ]
    return "solution.cpp", [
        [("class", "kw"), (" ", "p"), ("Solution", "type"), (" {", "p")],
        [("public", "kw"), (":", "p")],
        [("    ", "p"), ("int", "kw"), (" ", "p"), ("solved", "fn"), ("(", "p"),
         ("vector", "type"), ("<", "p"), ("Problem", "type"), (">& p) {", "p")],
        [("        ", "p"), ("return", "kw"), (" p.", "p"), ("size", "fn"), ("(); ", "p"),
         (f"// {comment}", "cm")],
        [("    }", "p")],
        [("};", "p")],
    ]


def card_banner(problems: list[Problem], totals: dict | None, theme_name: str,
                config: dict) -> str:
    """An editor window that types a solution, hits Submit and gets 'Accepted'.

    Animated with SMIL, which plays inside <img> on GitHub (CSS can't animate
    clip widths reliably across browsers).
    """
    theme, syn = THEMES[theme_name], SYNTAX[theme_name]
    width, height, bar_h = 720, 230, 40
    total = len(problems)
    counts = {d: sum(p.difficulty == d for p in problems) for d in DIFFICULTIES}
    langs = Counter(lang for p in problems for lang in p.languages).most_common(1)
    filename, lines = banner_code(langs[0][0] if langs else "C++", total)
    title = config.get("banner_title", "LeetCode Solutions")
    subtitle = config.get("banner_subtitle", "")
    editor_w = 420
    char_w, line_h, code_x, code_y = 7.6, 22, 52, bar_h + 34

    parts = [
        # editor body and window chrome
        f'<path d="M1 {bar_h} H{editor_w} V{height - 1} H13 a12 12 0 0 1 -12 -12 Z" '
        f'fill="{syn["editor"]}"/>',
        f'<path d="M1 {bar_h} V13 a12 12 0 0 1 12 -12 H{width - 13} a12 12 0 0 1 12 12 V{bar_h} Z" '
        f'fill="{syn["bar"]}"/>',
        f'<line x1="1" y1="{bar_h}" x2="{width - 1}" y2="{bar_h}" stroke="{theme["border"]}"/>',
        f'<line x1="{editor_w}" y1="{bar_h}" x2="{editor_w}" y2="{height - 1}" stroke="{theme["border"]}"/>',
    ]
    for i, color in enumerate(("#ff5f57", "#febc2e", "#28c840")):
        parts.append(f'<circle cx="{20 + i * 17}" cy="{bar_h / 2}" r="5.5" fill="{color}"/>')
    parts.append(text_run(82, bar_h / 2 + 5, [(title, theme["text"], 13, True)]
                          + ([(f"  ·  {subtitle}", theme["muted"], 13, False)] if subtitle else [])))

    # file tab on the editor
    parts.append(f'<text x="{code_x - 32}" y="{bar_h + 20}" font-size="11" fill="{theme["muted"]}" '
                 f'class="mono">{esc(filename)}</text>')

    # typed code: each line is revealed by a growing clip rect, with a moving caret.
    # Indentation is applied through x (browsers collapse leading spaces in SVG text).
    t = 0.4
    defs = []
    for i, tokens in enumerate(lines):
        y = code_y + 18 + i * line_h
        indent = len(tokens[0][0]) - len(tokens[0][0].lstrip(" "))
        tokens = [(tokens[0][0][indent:], tokens[0][1])] + tokens[1:]
        tokens = [tok for tok in tokens if tok[0]]
        chars = sum(len(tok) for tok, _ in tokens)
        x_from = code_x + indent * char_w
        w = chars * char_w + 4
        dur = max(0.18, chars * 0.026)
        defs.append(
            f'<clipPath id="l{i}"><rect x="{x_from:.1f}" y="{y - 15}" width="0" height="{line_h}" '
            f'data-final="{w:.1f}"><animate attributeName="width" from="0" to="{w:.1f}" '
            f'begin="{t:.2f}s" dur="{dur:.2f}s" fill="freeze"/></rect></clipPath>'
        )
        parts.append(f'<text x="{code_x - 14}" y="{y}" text-anchor="end" font-size="12" '
                     f'fill="{syn["gutter"]}" class="mono">{i + 1}</text>')
        spans = "".join(f'<tspan fill="{syn[kind]}">{esc(tok)}</tspan>' for tok, kind in tokens)
        parts.append(f'<text x="{x_from:.1f}" y="{y}" font-size="12.6" class="mono" '
                     f'xml:space="preserve" clip-path="url(#l{i})">{spans}</text>')
        # the caret stays (blinking) on the last line, and leaves the others
        caret_end = "" if i == len(lines) - 1 else f' end="{t + dur:.2f}s"'
        parts.append(
            f'<rect x="{x_from:.1f}" y="{y - 13}" width="2" height="16" fill="{theme["text"]}" '
            f'opacity="0" class="caret">'
            f'<set attributeName="opacity" to="1" begin="{t:.2f}s"{caret_end}/>'
            f'<animate attributeName="x" from="{x_from:.1f}" to="{x_from + w - 2:.1f}" '
            f'begin="{t:.2f}s" dur="{dur:.2f}s" fill="freeze"/></rect>'
        )
        t += dur + 0.08
    typed_at = t

    # Run / Submit buttons; Submit gets "clicked" once typing finishes
    parts.append(f'<rect x="{width - 150}" y="9" width="58" height="22" rx="6" fill="{theme["pill"]}"/>'
                 f'<text x="{width - 121}" y="24" text-anchor="middle" font-size="12" '
                 f'fill="{theme["text"]}">Run</text>')
    parts.append(
        f'<g><rect x="{width - 84}" y="9" width="70" height="22" rx="6" fill="{ACCEPTED}"/>'
        f'<text x="{width - 49}" y="24" text-anchor="middle" font-size="12" font-weight="600" '
        f'fill="#ffffff">Submit</text>'
        f'<animate attributeName="opacity" values="1;.45;1" begin="{typed_at:.2f}s" dur=".35s"/></g>'
    )

    # result panel slides in after submitting
    rx = editor_w + 26
    shown = typed_at + 0.45
    all_total = (totals.get("All") or sum(totals.get(d, 0) for d in DIFFICULTIES)) if totals else None
    latest = max((p for p in problems if p.solved), key=lambda p: (p.solved, p.number), default=None)
    panel = [
        f'<text x="{rx}" y="{bar_h + 44}" font-size="24" font-weight="700" fill="{ACCEPTED}">Accepted</text>',
        text_run(rx, bar_h + 70, [(str(total), theme["text"], 13, True),
                                  (f" / {all_total} solved" if all_total else " solved",
                                   theme["muted"], 13, False)]),
    ]
    px = rx
    for d in DIFFICULTIES:
        label = f"{counts[d]} {d}"
        w = text_width(label, 12) + 30
        panel.append(f'<rect x="{px:.1f}" y="{bar_h + 86}" width="{w:.0f}" height="24" rx="12" '
                     f'fill="{theme["pill"]}"/>'
                     f'<circle cx="{px + 12:.1f}" cy="{bar_h + 98}" r="3.5" fill="{DIFF_COLORS[d]}"/>'
                     f'<text x="{px + 20:.1f}" y="{bar_h + 102}" font-size="12" '
                     f'fill="{theme["text"]}">{esc(label)}</text>')
        px += w + 6
    if latest:
        name = f"{latest.number}. {latest.title}"
        name = name if len(name) <= 30 else name[:29] + "…"
        panel.append(f'<text x="{rx}" y="{bar_h + 140}" font-size="11" fill="{theme["muted"]}" '
                     f'letter-spacing="1">LATEST</text>'
                     f'<text x="{rx}" y="{bar_h + 160}" font-size="13" fill="{theme["text"]}">'
                     f'{esc(name)}</text>')
    parts.append(
        f'<g opacity="0" transform="translate(12 0)">'
        f'<animate attributeName="opacity" from="0" to="1" begin="{shown:.2f}s" dur=".5s" fill="freeze"/>'
        f'<animateTransform attributeName="transform" type="translate" from="12 0" to="0 0" '
        f'begin="{shown:.2f}s" dur=".5s" fill="freeze"/>'
        + "".join(panel) + "</g>"
    )

    style = (f"text.mono{{font-family:{MONO}}}\n"
             ".caret{animation:blink 1s step-end infinite}"
             "@keyframes blink{50%{fill-opacity:0}}\n")
    body = "<defs>" + "".join(defs) + "</defs>\n" + "\n".join(parts) + "\n"
    return svg(width, height, theme, style, body, f"{title}: {total} problems solved")


# ---------------------------------------------------------------- README

def picture(name: str, alt: str) -> str:
    return (
        "<picture>\n"
        f'  <source media="(prefers-color-scheme: dark)" srcset="{ASSETS_URL}/{name}-dark.svg">\n'
        f'  <img src="{ASSETS_URL}/{name}-light.svg" alt="{esc(alt)}" width="720">\n'
        "</picture>"
    )


def difficulty_text(d: str) -> str:
    return "$\\color{" + DIFF_COLORS[d] + "}{\\textsf{" + d + "}}$"


def folder_link(folder: str) -> str:
    return "./" + quote(folder)


def build_block(problems: list[Problem], contests: list[Contest], has_skills: bool,
                config: dict) -> str:
    counts = {d: sum(p.difficulty == d for p in problems) for d in DIFFICULTIES}
    out = ["", '<p align="center">', picture("stats", f"{len(problems)} problems solved"), "</p>",
           '<p align="center">', picture("heatmap", "Solve activity over the past year"), "</p>"]
    if has_skills:
        out += ['<p align="center">', picture("skills", "Topics covered"), "</p>"]

    recent = sorted((p for p in problems if p.solved), key=lambda p: (p.solved, p.number),
                    reverse=True)[: config.get("recent_count", 5)]
    if recent:
        out += ["", "## Recent AC", "", "| | Problem | Difficulty | Pushed |", "|:-:|---|:-:|:-:|"]
        out += [f"| ✅ | [{p.number}. {p.title}](https://leetcode.com/problems/{p.slug}/) "
                f"| {difficulty_text(p.difficulty)} | {fmt_date(p.solved)} |" for p in recent]

    out += ["", "## Problem List", "",
            f"<sub>{len(problems)} solved &nbsp;·&nbsp; "
            + " &nbsp;·&nbsp; ".join(f"{counts[d]} {d}" for d in DIFFICULTIES) + "</sub>", "",
            "| Status | Title | Acceptance | Difficulty | Solution |",
            "|:-:|---|:-:|:-:|:-:|"]
    for p in sorted(problems, key=lambda p: p.number):
        title = p.title.replace("|", "\\|")
        accept = f"{p.ac_rate:.1f}%" if p.ac_rate is not None else "-"
        langs = " · ".join(p.languages) or "Code"
        out.append(f"| ✅ | [{p.number}. {title}](https://leetcode.com/problems/{p.slug}/) "
                   f"| {accept} | {difficulty_text(p.difficulty)} "
                   f"| [{langs}]({folder_link(p.folder)}) |")

    if contests:
        out += ["", "## Contests", "", "| Contest | Solved | Pushed | Solutions |", "|---|:-:|:-:|:-:|"]
        for c in sorted(contests, key=lambda c: (c.date or date.min, c.number), reverse=True):
            out.append(f"| 🏆 {c.kind} Contest {c.number} | {c.solved} | {fmt_date(c.date)} "
                       f"| [View]({folder_link(c.folder)}) |")
        out += ["", "<sub>Contest problems are listed separately and are not counted in the totals above.</sub>"]

    out.append("")
    return "\n".join(out)


def main() -> None:
    config = json.loads(CONFIG_PATH.read_text()) if CONFIG_PATH.exists() else {}
    problems, contests = scan()
    totals, activity = enrich(problems, config)
    today = datetime.now(timezone.utc).date()  # LeetCode's calendar days are UTC

    ASSETS.mkdir(exist_ok=True)
    skills_written = False
    for name, theme in THEMES.items():
        (ASSETS / f"banner-{name}.svg").write_text(card_banner(problems, totals, name, config))
        (ASSETS / f"stats-{name}.svg").write_text(card_stats(problems, totals, theme))
        (ASSETS / f"heatmap-{name}.svg").write_text(card_heatmap(activity, theme, today))
        skills = card_skills(problems, theme)
        if skills:
            (ASSETS / f"skills-{name}.svg").write_text(skills)
            skills_written = True

    if not README.exists() or not MARKER_RE.search(README.read_text(encoding="utf-8")):
        sys.exit("README.md needs <!-- STATS:START --> and <!-- STATS:END --> markers.")
    text = README.read_text(encoding="utf-8")
    block = build_block(problems, contests, skills_written, config)
    README.write_text(MARKER_RE.sub(lambda m: m[1] + block + m[3], text), encoding="utf-8")

    counts = Counter(p.difficulty for p in problems)
    print(f"Generated: {len(problems)} problems ({counts['Easy']} Easy, {counts['Medium']} Medium, "
          f"{counts['Hard']} Hard), {len(contests)} contests")


if __name__ == "__main__":
    main()
