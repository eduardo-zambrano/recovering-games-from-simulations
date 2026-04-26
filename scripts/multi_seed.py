"""
multi_seed.py

Run the El Farol simulator across multiple seeds and compile a CSV summary
of moments. Used to produce the 50-seed robustness statistics reported in
the paper.

Usage:
    python multi_seed.py --seeds 1-50 --output multi_seed.csv \
        --executable ../code/elfarol --burn-in 500

The simulator binary is expected to:
    1. Read the seed from a command-line argument or environment variable
       (modify Project1.cpp's `srand` call to read `getenv("SEED")` or
       `argv[1]`).
    2. Write daily attendance to stdout, one integer per line, for
       EXPT_LENGTH days.

This script is a template; depending on how the binary is wired, the
subprocess call below may need adjustment.
"""

import argparse
import csv
import os
import statistics
import subprocess
import sys
from pathlib import Path

import moments  # local import; same directory


def parse_seed_spec(spec):
    """Parse a seed range like '1-50' or '1,3,5'."""
    seeds = []
    for chunk in spec.split(","):
        if "-" in chunk:
            a, b = chunk.split("-")
            seeds.extend(range(int(a), int(b) + 1))
        else:
            seeds.append(int(chunk))
    return seeds


def run_one(executable, seed):
    """Run the simulator with a given seed; return list of attendance ints."""
    env = os.environ.copy()
    env["SEED"] = str(seed)
    proc = subprocess.run(
        [str(executable), str(seed)], capture_output=True, text=True, env=env
    )
    if proc.returncode != 0:
        raise RuntimeError(f"seed {seed}: simulator failed: {proc.stderr}")
    return [int(x) for x in proc.stdout.split() if x.strip()]


def summarize(series, burn_in, threshold):
    post = series[burn_in:]
    n = len(post)
    mean = statistics.mean(post)
    median = statistics.median(post)
    sd = statistics.stdev(post) if n > 1 else 0.0
    ac1 = moments.lag1_autocorrelation(post)
    runs, z = moments.wald_wolfowitz(post, threshold)
    return {
        "n": n,
        "mean": mean,
        "median": median,
        "sd": sd,
        "lag1_ac": ac1,
        "ww_runs": runs,
        "ww_z": z,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--seeds", required=True)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--executable", required=True, type=Path)
    parser.add_argument("--burn-in", type=int, default=500)
    parser.add_argument("--threshold", type=int, default=60)
    args = parser.parse_args()

    seeds = parse_seed_spec(args.seeds)
    rows = []
    for seed in seeds:
        try:
            series = run_one(args.executable, seed)
            stats = summarize(series, args.burn_in, args.threshold)
            stats["seed"] = seed
            rows.append(stats)
            print(
                f"seed {seed}: mean={stats['mean']:.2f} median={stats['median']} "
                f"sd={stats['sd']:.2f} ac={stats['lag1_ac']:.3f}"
            )
        except RuntimeError as exc:
            print(f"seed {seed}: ERROR ({exc})", file=sys.stderr)

    fieldnames = ["seed", "n", "mean", "median", "sd", "lag1_ac", "ww_runs", "ww_z"]
    with args.output.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for row in rows:
            writer.writerow(row)
    print(f"Wrote {len(rows)} rows to {args.output}")


if __name__ == "__main__":
    main()
