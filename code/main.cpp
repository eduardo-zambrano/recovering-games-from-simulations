// Modified version of Arthur's Project1.cpp for verification:
//  * srand(SEED) where SEED is read from argv[1] (or 42 by default)
//  * EXPT_LENGTH overridable from argv[2]
//  * Writes attendance to stdout, one int per line
//  * Also writes per-day predictor usage histogram to stderr

#include "define.h"
#include "extern.h"
#include "global.h"
#include "agents.h"
#include "forecast.h"
#include "history.h"

int main(int argc, char **argv) {
    int seed = 42;
    long int total_days = 10000;
    if (argc >= 2) seed = atoi(argv[1]);
    if (argc >= 3) total_days = atol(argv[2]);

    srand(seed);

    day = 1;
    ofp = fopen("/dev/null", "w");
    ofplot = fopen("/dev/null", "w");

    Initiate_history(pastdays);
    Initiate_predictors(forecast);
    sort(forecast);
    Initiate_agents(person);

    while (day <= total_days) {
        Make_new(forecast);
        Make_choice(forecast, person, predictor_use);
        todays_number = Calculate_number(person);

        // Write attendance to stdout
        printf("%ld %d", day, todays_number);
        // Write the predictor-use histogram (21 entries) on the same line
        for (int k = 0; k < TOTPREDICTORS; k++) {
            printf(" %d", predictor_use[k]);
        }
        printf("\n");

        Update_accuracy(todays_number, forecast);
        sort(forecast);
        Update_history(pastdays, todays_number);
        ++day;
    }
    return 0;
}
