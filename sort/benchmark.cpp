#include "helpers.h"
#include "sort.h"

// SET-UP:
const int N_TIMES = 10000;
const int LENGTH  = 1000;

int main(){

    // Benchmark the standard library:
    double time = benchmark_sorting(N_TIMES, LENGTH, &quicksort_standard_library<double>);
    cout << "Sorting a vector of size 1000 takes on averge " << time << " milliseconds when sorting with the std library" << endl << endl;

    // Benchmark  selectionsort:
    time = benchmark_sorting(N_TIMES, LENGTH, &selectionsort<double>);
    cout << "Sorting a vector of size 1000 takes on averge " << time << " milliseconds when sorting with selectionsort" << endl << endl;

    // Benchmark insertionsort:
    time = benchmark_sorting(N_TIMES, LENGTH, &insertionsort<double>);
    cout << "Sorting a vector of size 1000 takes on averge " << time << " milliseconds when sorting with insertionsort" << endl << endl;

    // Benchmark bubblesort:
    time = benchmark_sorting(N_TIMES, LENGTH, &bubblesort<double>);
    cout << "Sorting a vector of size 1000 takes on averge " << time << " milliseconds when sorting with bubblesort" << endl << endl;

    // Benchmark quicksort:
    time = benchmark_sorting(N_TIMES, LENGTH, &quicksort<double>);
    cout << "Sorting a vector of size 1000 takes on averge " << time << " milliseconds when sorting with quicksort" << endl << endl;

    // Benchmark mergesort:
    time = benchmark_sorting(N_TIMES, LENGTH, &mergesort<double>);
    cout << "Sorting a vector of size 1000 takes on averge " << time << " milliseconds when sorting with mergesort" << endl << endl;

    // Benchmark introsort:
    time = benchmark_sorting(N_TIMES, LENGTH, &introsort<double>);
    cout << "Sorting a vector of size 1000 takes on averge " << time << " milliseconds when sorting with introsort" << endl << endl;

    // Benchmark heapsort:
    time = benchmark_sorting(N_TIMES, LENGTH, &heapsort<double>);
    cout << "Sorting a vector of size 1000 takes on averge " << time << " milliseconds when sorting with heapsort" << endl << endl;
}
