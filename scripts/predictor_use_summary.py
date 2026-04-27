"""
predictor_use_summary.py

Aggregate the per-day predictor-use histogram from a seed-42 raw output file
into a CSV summary.

Usage:
    python predictor_use_summary.py <raw_input> <output_csv>

Input format:
    Each line: day attendance use[0] use[1] ... use[20]
Output format (CSV):
    predictor,total_uses,share_full,total_uses_postburnin,share_postburnin
"""

import sys
from pathlib import Path

BURN_IN = 500
TOTPREDICTORS = 21


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <raw_input> <output_csv>", file=sys.stderr)
        sys.exit(1)
    in_path = Path(sys.argv[1])
    out_path = Path(sys.argv[2])

    total = [0] * TOTPREDICTORS
    post = [0] * TOTPREDICTORS

    with in_path.open() as f:
        for line in f:
            tokens = line.split()
            if len(tokens) < 2 + TOTPREDICTORS:
                continue
            day = int(tokens[0])
            uses = [int(x) for x in tokens[2 : 2 + TOTPREDICTORS]]
            for k in range(TOTPREDICTORS):
                total[k] += uses[k]
                if day > BURN_IN:
                    post[k] += uses[k]

    total_full = sum(total)
    total_post = sum(post)

    with out_path.open("w") as out:
        out.write("predictor,total_uses,share_full,total_uses_postburnin,share_postburnin\n")
        for k in range(TOTPREDICTORS):
            sf = total[k] / total_full * 100 if total_full else 0
            sp = post[k] / total_post * 100 if total_post else 0
            out.write(f"{k},{total[k]},{sf:.4f},{post[k]},{sp:.4f}\n")
    print(f"Wrote predictor-use summary to {out_path}")


if __name__ == "__main__":
    main()
