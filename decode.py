"""
Decoded transitions.tsv

The file is a 2-symbol Turing machine with 2452 states (one per line).
  - Line i is state number i; its name is i written in base 52 with the
    alphabet A-Z then a-z (line 0 = "AA", line 1 = "AB", ..., line 2451 = "vH").
  - Each line is two triples: (write, move, next) when reading 0,
    then (write, move, next) when reading 1.
  - "wi" is never defined as a line: it is the HALT state.
  - Start state: AA (line 0). Blank symbol: 0.

Input/output convention (the one the machine is built for):
  - A number n is written in unary: n consecutive 1s on a blank tape.
  - The head starts on the RIGHTMOST 1.
  - The machine runs until it re-enters state AA. At that point the tape holds
    a single block of f(n) ones with the head on its rightmost cell.
  - It then starts over on f(n) forever. The halt state is never reached.

What f computes:
  f(n) = TABLE[n % 210]      (210 = 2*3*5*7)
  TABLE is a permutation of 0..209 of order 6, so applying f six times
  returns the original residue.

Trap: if the head starts on the LEFTMOST 1 of a block of 31+ ones, the machine
runs a ~2^32-step busy counter before doing the same computation. The result
is identical, it is only there to make naive simulation look like it hangs.
"""

TABLE = [
      0, 148, 117,  45, 192,  68, 166, 101, 208,  60,  78, 152, 120, 195, 196,
      5,  71, 123, 136,  15,  82, 165,  22,   8, 112,  93, 185,  85, 126,  23,
     31,  49,  37, 177, 158, 118,  98, 156, 140,  62,  38, 128, 184,  46,  35,
     50, 104,  74,  36, 167,  55,  79,  77,  72,  54, 153, 129, 143, 162, 199,
      9, 125,  87,  64, 142, 175,  11, 146, 181,  58,  70,   6, 100, 191,  40,
    182, 110, 119, 150, 102,   3, 113,  20,  19, 180, 134,   4,  39, 197,  88,
    161,   2, 188,  30,  65, 202,  41,  26,  52, 133,  33, 114,  94, 103, 193,
     16, 106, 115,  95, 176,  76, 157, 183, 168,   7, 144, 179,  21, 207,  48,
    121,  12, 170, 205,  75,  29, 190, 189,  96, 206, 107,  59,  90,  99,  27,
    169,  18, 109, 203, 139, 151,  28,  63, 198,  34,  67, 145, 122,  84, 200,
     10,  47,  66,  80,  56, 155, 137, 132, 130, 154,  42, 173, 135, 105, 159,
    174, 163,  25,  81, 171, 147,  69,  53, 111,  91,  51,  32, 172, 160, 178,
    186,  83, 124,  24, 116,  97, 201, 187,  44, 127, 194,  73,  86, 138, 204,
     13,  14,  89,  57, 131, 149,   1, 108,  43, 141,  17, 164,  92,  61, 209,
]


def f(n: int) -> int:
    """One pass of the machine (closed form, O(1))."""
    if n < 0:
        raise ValueError("n must be non-negative")
    return TABLE[n % 210]


def f_iter(n: int, k: int) -> int:
    """k passes of the machine. Order is 6, so only k % 6 matters."""
    if k == 0:
        return n
    r = n % 210
    for _ in range((k - 1) % 6 + 1):
        r = TABLE[r]
    return r


# ---------------------------------------------------------------------------
# Reference simulator (test oracle). Slow for big n, use it only to verify.
# ---------------------------------------------------------------------------
import string
from collections import defaultdict

_ALPHA = string.ascii_uppercase + string.ascii_lowercase


def _state_index(name: str) -> int:
    return _ALPHA.index(name[0]) * 52 + _ALPHA.index(name[1])


def load_machine(path: str):
    rules = []
    with open(path) as fh:
        for line in fh:
            p = line.split()
            if len(p) == 6:
                rules.append([(int(p[0]), p[1], p[2]), (int(p[3]), p[4], p[5])])
    return rules


def simulate_one_pass(rules, n: int, max_steps: int = 10**9) -> int:
    tape = defaultdict(int)
    for i in range(n):
        tape[i] = 1
    head, state, steps = max(n - 1, 0), "AA", 0
    while True:
        write, move, nxt = rules[_state_index(state)][tape[head]]
        tape[head] = write
        head += 1 if move == "R" else -1
        state, steps = nxt, steps + 1
        if state in ("AA", "wi") or steps >= max_steps:
            break
    return sum(tape.values())


if __name__ == "__main__":
    import sys
    path = sys.argv[1] if len(sys.argv) > 1 else "transitions.tsv"
    rules = load_machine(path)
    assert sorted(TABLE) == list(range(210))
    for n in list(range(0, 260)) + [431, 637]:
        assert simulate_one_pass(rules, n) == f(n), n
    print("closed form matches the machine for all tested n")