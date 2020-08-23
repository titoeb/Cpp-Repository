#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define SIDES 6
#define R_SIDE (rand() % SIDES + 1)
#define N_DICE 2

void simulation(){
    int trials, d1, d2, n_dice, result;
    int* outcomes;
    double sum_probability = 0.0, current_probability;

    // Set a seed for random program
    srand(clock());

    // Get the number of simulation from the user.

    printf("Enter number of trials\n");
    scanf("%d", &trials);
    // Allocate a int array to store the outputs.
    outcomes = (unsigned int*) malloc(sizeof(unsigned int) * ((SIDES * N_DICE) + 1));
    for(int j =0; j < trials; j++){
        outcomes[j] = 0;
    }

    // Compute probabilites
    for(int j=0; j < trials; ++j){
        result = R_SIDE + R_SIDE;
        outcomes[result]++;
    }

    // output results of the simulation
    printf("probability\n");
    for(int j=N_DICE; j <= (N_DICE * SIDES); ++j){
        current_probability = (double) outcomes[j] / (double) trials;
        sum_probability = sum_probability + current_probability;

        printf("j=%d n = %i p = %lf\n", j,outcomes[j], current_probability);
    }
    printf("Sum for the probabilities was %lf\n", sum_probability);
    free(outcomes);
}

int main(){
    simulation();
    return 0;
}

