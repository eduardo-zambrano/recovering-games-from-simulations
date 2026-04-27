#!/bin/bash
#
# reproduce_all.sh — end-to-end reproduction script for
# "Recovering Games from Simulations: The El Farol Bar Problem Revisited"
#
# Builds the simulator, runs the seed-42 simulation, runs the 50-seed
# robustness sweep, and regenerates all figure data files.
#
# Usage:  bash scripts/reproduce_all.sh
#
# Output: data/arthurs_attendance.dat, data/arthurs_300days.dat,
#         data/arthurs_conditional.dat, data/predictor_use_summary.csv,
#         data/multi_seed.csv, and a binary at code/elfarol.

set -e

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

echo "=== 1. Building simulator ==="
cd code
make
cd ..

echo "=== 2. Running seed-42 simulation (10,000 days) ==="
code/elfarol 42 10000 > data/seed42_full.dat
awk '{print NR, $2}' data/seed42_full.dat > data/arthurs_attendance.dat
echo "    Wrote data/arthurs_attendance.dat ($(wc -l < data/arthurs_attendance.dat) lines)"

echo "=== 3. Generating Figure 1 data (300-day post-burn-in window) ==="
python3 scripts/figure1_data.py data/arthurs_attendance.dat data/arthurs_300days.dat

echo "=== 4. Generating Figure 2 data (conditional means) ==="
python3 scripts/figure2_data.py data/arthurs_attendance.dat data/arthurs_conditional.dat

echo "=== 5. Computing predictor-use summary ==="
python3 scripts/predictor_use_summary.py data/seed42_full.dat data/predictor_use_summary.csv

echo "=== 6. Running 50-seed robustness sweep ==="
python3 scripts/multi_seed.py --seeds 1-50 --executable code/elfarol \
    --output data/multi_seed.csv --burn-in 500

echo "=== 7. Verifying paper Section 4.2 statistics ==="
python3 scripts/moments.py data/arthurs_attendance.dat --burn-in 500

echo
echo "Done. All artifacts under data/."
