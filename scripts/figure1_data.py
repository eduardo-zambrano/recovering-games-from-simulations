"""
figure1_data.py

Generate the data file for Figure 1 of "Recovering Games from Simulations:
The El Farol Bar Problem Revisited" — a 300-day post-burn-in window of
aggregate attendance.

Usage:
    python figure1_data.py <attendance_input> <output_dat>

Input format (attendance_input):
    One integer per line, the daily attendance count produced by Arthur's
    code. Expected length: 10,000 (full run).

Output format (output_dat):
    Two columns separated by a space:
        day_index  attendance
    Days are 1..300, post-burn-in (i.e., raw days 501..800 of the simulation).
"""

import sys
from pathlib import Path

BURN_IN = 500
WINDOW = 300


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <attendance_input> <output_dat>", file=sys.stderr)
        sys.exit(1)

    in_path = Path(sys.argv[1])
    out_path = Path(sys.argv[2])

    attendance = []
    with in_path.open() as f:
        for line in f:
            tokens = line.split()
            if not tokens:
                continue
            attendance.append(int(tokens[-1]))

    if len(attendance) < BURN_IN + WINDOW:
        print(
            f"Error: input has {len(attendance)} lines; need at least "
            f"{BURN_IN + WINDOW}.",
            file=sys.stderr,
        )
        sys.exit(1)

    window = attendance[BURN_IN : BURN_IN + WINDOW]

    with out_path.open("w") as f:
        for i, a in enumerate(window, start=1):
            f.write(f"{i} {a}\n")

    print(f"Wrote {WINDOW} lines to {out_path}")


if __name__ == "__main__":
    main()
