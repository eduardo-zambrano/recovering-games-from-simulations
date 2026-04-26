"""
moments.py

Compute summary statistics for an attendance series produced by Arthur's
simulation: mean, median, SD, lag-1 autocorrelation, count above/below/at
60, and the Wald--Wolfowitz runs-test z-statistic for excess alternation
around the median.

Usage:
    python moments.py <attendance_input> [--burn-in N]

Defaults: burn-in = 500.
"""

import argparse
import statistics
from pathlib import Path


def lag1_autocorrelation(series):
    n = len(series)
    if n < 2:
        return 0.0
    mean = statistics.mean(series)
    num = sum((series[t] - mean) * (series[t + 1] - mean) for t in range(n - 1))
    den = sum((series[t] - mean) ** 2 for t in range(n))
    return num / den if den > 0 else 0.0


def wald_wolfowitz(series, threshold):
    """Number of runs around `threshold` and the asymptotic z-statistic."""
    above = [s > threshold for s in series]
    below = [s < threshold for s in series]
    n_above = sum(above)
    n_below = sum(below)
    n = n_above + n_below
    if n_above == 0 or n_below == 0:
        return 0, 0.0
    runs = 1
    last_signed = None
    for s in series:
        if s == threshold:
            continue
        signed = s > threshold
        if last_signed is None:
            last_signed = signed
            continue
        if signed != last_signed:
            runs += 1
            last_signed = signed
    expected = (2 * n_above * n_below) / n + 1
    var = (2 * n_above * n_below * (2 * n_above * n_below - n)) / (n * n * (n - 1))
    sd = var**0.5 if var > 0 else 0.0
    z = (runs - expected) / sd if sd > 0 else 0.0
    return runs, z


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path)
    parser.add_argument("--burn-in", type=int, default=500)
    parser.add_argument("--threshold", type=int, default=60)
    args = parser.parse_args()

    attendance = []
    with args.input.open() as f:
        for line in f:
            tokens = line.split()
            if not tokens:
                continue
            attendance.append(int(tokens[-1]))

    full = attendance
    post = attendance[args.burn_in :]

    for label, series in (("full", full), ("post-burn-in", post)):
        n = len(series)
        mean = statistics.mean(series)
        median = statistics.median(series)
        sd = statistics.stdev(series) if n > 1 else 0.0
        ac1 = lag1_autocorrelation(series)
        n_above = sum(1 for s in series if s > args.threshold)
        n_below = sum(1 for s in series if s < args.threshold)
        n_at = sum(1 for s in series if s == args.threshold)
        runs, z = wald_wolfowitz(series, args.threshold)
        print(f"--- {label} (n = {n}) ---")
        print(f"  mean         {mean:.4f}")
        print(f"  median       {median}")
        print(f"  sd           {sd:.4f}")
        print(f"  lag-1 AC     {ac1:.4f}")
        print(f"  above/below/at {args.threshold}: {n_above}/{n_below}/{n_at}")
        print(f"  WW runs      {runs}")
        print(f"  WW z-stat    {z:.2f}")


if __name__ == "__main__":
    main()
