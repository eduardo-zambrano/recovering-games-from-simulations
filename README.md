# Replication materials for "Recovering Games from Simulations: The El Farol Bar Problem Revisited"

This repository contains the source code, data, and reproduction scripts for the paper:

> Zambrano, Eduardo. "Recovering Games from Simulations: The El Farol Bar Problem Revisited." *Journal of Economic Behavior & Organization*, special issue in honor of Reinhard Selten (forthcoming).

The paper argues that simulations of Arthur's (1994) El Farol Bar Problem implement a *prediction game* (PG) in which agents forecast aggregate attendance, scored by absolute prediction error, rather than the *attendance game* (AG) typically written down by analysts. The two games have different mixed Nash equilibria, and the simulation regularities match PG.

## Repository contents

```
.
├── README.md              this file
├── LICENSE                MIT for new code; Arthur (1994) attribution
├── code/                  C source code (Arthur's original simulation)
│   ├── Project1.cpp       main loop
│   ├── define.h           parameters (TOTPERSONS=100, CRITNUM=60, ETA=0.05, etc.)
│   ├── agents.h           agent setup, predictor selection, attendance decisions
│   ├── forecast.h         the 21 predictors, accuracy update, ranking
│   ├── history.h          attendance history bookkeeping
│   ├── extern.h           extern declarations
│   └── global.h           global state
├── data/                  Output data files used to render the paper's figures
│   ├── arthurs_200days.dat        seed-42, days 1-200 attendance series
│   ├── arthurs_300days.dat        seed-42, days 1-300 (used for Figure 1)
│   ├── arthurs_attendance.dat     seed-42, full 10,000-period attendance series
│   ├── arthurs_conditional.dat    E[A_{t+1} | A_t] data for Figure 2
│   └── arthurs_histogram.dat      cross-sectional predictor-usage histogram
└── scripts/               Python scripts for post-processing and figure data generation
    ├── figure1_data.py    300-day post-burn-in window for Figure 1
    ├── figure2_data.py    conditional-mean E[A_{t+1} | A_t] for Figure 2
    ├── moments.py         summary statistics (mean / median / SD / lag-1 AC / W-W)
    └── multi_seed.py      run simulator across multiple seeds; CSV summary
```

## The 21 predictors in Arthur's code

Each agent monitors a random subset of `MAXHEED = 10` predictors out of these 21. Each predictor maps the recent history of attendance to a forecast for the next period. The predictors are defined in `code/forecast.h`; the labels follow `code/global.h`.

| ID | Label | Forecast rule |
|----|-------|---------------|
| 0  | R.e.e. (rational expectations) | constant `CRITNUM` $= 60$ |
| 1  | Near r.e.e. | constant `CRITNUM + 1` $= 61$ |
| 2  | Extrapolator | `hist[0] + (hist[0] - hist[1])`, capped to $[0, 100]$ |
| 3  | Reflect around half | $100 - $ `hist[0]` |
| 4  | Too many?1 | if `hist[0] > 80` → 30; if `hist[0] < 20` → 70; else `hist[0]` |
| 5  | Too many?2 | if `hist[0] > 70` → 40; if `hist[0] < 30` → 60; else `hist[0]` |
| 6  | Too many?3 | if `hist[0] > 90` → 10; if `hist[0] < 10` → 90; else `hist[0]` |
| 7  | Fifty | constant 50 |
| 8  | Trend/rev1 | extrapolate using the gap to `hist[4]`, with extreme-case reversal |
| 9  | Trend/rev2 | extrapolate using the gap to `hist[2]`, with extreme-case reversal |
| 10 | Av. prev 3 | average of `hist[0], hist[1], hist[2]` |
| 11 | Same last | `hist[0]` (same as last week) |
| 12 | 2-cycle | `hist[1]` |
| 13 | 3-cycle | `hist[2]` |
| 14 | 4-cycle | `hist[3]` |
| 15 | 5-cycle | `hist[4]` |
| 16 | 6-cycle | `hist[5]` |
| 17 | 7-cycle | `hist[6]` |
| 18 | 8-cycle | `hist[7]` |
| 19 | 9-cycle | `hist[8]` |
| 20 | 10-cycle | `hist[9]` |

Predictors 0 and 1 are the *anchor* predictors; together they account for roughly 77% of agent choices in the seed-42 run (see paper, Section 4.4). Predictor 7 is a third constant (forecast 50) that the paper calls out as the most prominent non-anchor.

## How to reproduce the figures

### Prerequisites

- A C++ compiler (gcc, clang, or MSVC). Tested with Apple clang on macOS.
- Python 3.10+. The post-processing scripts use only the standard library.

### One-shot reproduction

```bash
bash scripts/reproduce_all.sh
```

This builds the simulator, runs the seed-42 simulation for 10,000 periods, regenerates the Figure 1 and Figure 2 data files, computes the predictor-use summary, and runs the 50-seed robustness sweep. It also prints the Section 4.2 statistics for verification.

### Step-by-step

**Build the simulator.**

```bash
cd code
make
```

This produces `code/elfarol`. The binary takes two arguments:

```
./elfarol SEED DAYS
```

and writes one line per day to stdout:

```
day attendance use[0] use[1] ... use[20]
```

where `use[k]` is the number of agents who used predictor `k` that day.

**Run the seed-42 simulation.**

```bash
./elfarol 42 10000 > ../data/seed42_full.dat
```

**Generate figure data.**

```bash
cd ..
awk '{print NR, $2}' data/seed42_full.dat > data/arthurs_attendance.dat
python3 scripts/figure1_data.py data/arthurs_attendance.dat data/arthurs_300days.dat
python3 scripts/figure2_data.py data/arthurs_attendance.dat data/arthurs_conditional.dat
python3 scripts/predictor_use_summary.py data/seed42_full.dat data/predictor_use_summary.csv
```

The paper's Figures 1 and 2 are rendered by LaTeX/`pgfplots` directly from `arthurs_300days.dat` and `arthurs_conditional.dat`.

**Verify the Section 4.2 statistics.**

```bash
python3 scripts/moments.py data/arthurs_attendance.dat --burn-in 500
```

Expected output (matching the paper):

```
mean         57.86
median       60
sd           13.27
lag-1 AC     -0.33
above/below/at 60: 4717/4527/256   (post-burn-in)
WW runs      6946
WW z-stat    48.39
```

### Multi-seed robustness

```bash
python3 scripts/multi_seed.py --seeds 1-50 \
    --executable code/elfarol \
    --output data/multi_seed.csv \
    --burn-in 500 --days 10000
```

A precomputed `data/multi_seed.csv` is shipped in the repository for convenience; the command above regenerates it.

### Reproducibility note

The simulation uses C-library `rand()` for randomization, which is libc-dependent. The aggregate moments of the seed-42 attendance series (mean, median, SD, lag-1 AC, runs counts, conditional means) are robust across Linux glibc and Apple Silicon clang builds. The fine-grained predictor-usage shares may differ by 0.5--1.5 percentage points across builds because the random heed-set assignments differ.

## Figures rendered in the paper

The paper compiles its figures directly from the `.dat` files using LaTeX/`pgfplots`. Both figures can be regenerated by running `pdflatex` on the paper source; the `.dat` files in `data/` are the inputs.

- **Figure 1**: 300-day post-burn-in window of attendance (seed 42), with capacity line at 60. Source: `arthurs_300days.dat`.
- **Figure 2**: Conditional mean E[A_{t+1} | A_t] across the 9,500-day post-burn-in series, with the 19-unit discontinuity at the 60/61 boundary. Source: `arthurs_conditional.dat`.

## Citation

```bibtex
@article{zambrano2026recovering,
  author  = {Zambrano, Eduardo},
  title   = {Recovering Games from Simulations: The {El Farol} Bar Problem Revisited},
  journal = {Journal of Economic Behavior \& Organization},
  year    = {2026},
  note    = {Special issue in honor of Reinhard Selten}
}
```

## License

Arthur's original C source is reproduced here for academic-research purposes; original copyright is W. Brian Arthur (1994), Santa Fe Institute. The post-processing scripts and reproduction infrastructure are released under MIT license.

## Contact

Eduardo Zambrano · Department of Economics · California Polytechnic State University · ezambran@calpoly.edu
