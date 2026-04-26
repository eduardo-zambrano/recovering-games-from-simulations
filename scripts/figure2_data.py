"""
figure2_data.py

Generate the data file for Figure 2 of "Recovering Games from Simulations:
The El Farol Bar Problem Revisited" — the conditional mean E[A_{t+1} | A_t]
across the full 9,500-day post-burn-in series, with the 19-unit
discontinuity at the 60/61 boundary.

Usage:
    python figure2_data.py <attendance_input> <output_dat>

Input format (attendance_input):
    One integer per line, the daily attendance count produced by Arthur's
    code. Expected length: 10,000 (full run).

Output format (output_dat):
    Four columns separated by spaces:
        A_t  E[A_{t+1} | A_t]  std_error  count
    Only values of A_t with at least MIN_COUNT observations are emitted.
"""

import sys
from collections import defaultdict
from pathlib import Path
import statistics

BURN_IN = 500
MIN_COUNT = 30


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

    series = attendance[BURN_IN:]

    buckets = defaultdict(list)
    for t in range(len(series) - 1):
        a_t = series[t]
        a_tp1 = series[t + 1]
        buckets[a_t].append(a_tp1)

    with out_path.open("w") as f:
        for a_t in sorted(buckets):
            values = buckets[a_t]
            n = len(values)
            if n < MIN_COUNT:
                continue
            mean = statistics.mean(values)
            sd = statistics.stdev(values) if n > 1 else 0.0
            se = sd / (n**0.5) if n > 0 else 0.0
            f.write(f"{a_t} {mean:.3f} {se:.3f} {n}\n")

    print(f"Wrote conditional-mean data to {out_path}")


if __name__ == "__main__":
    main()
