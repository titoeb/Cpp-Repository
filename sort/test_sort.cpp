#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test Sort

#include <boost/test/unit_test.hpp>
#include "helpers.h"
#include "sort.h"

// SET-UP:
const int N_TIMES = 10000;
const int LENGTH  = 1000;

// Helper function to avoid repetitive code in testing:
// Testing a given sorting algorithm on random data
template<class Sortable>
void random_test_sorting(int n_times, int length, void(*sorting)(vector<Sortable>& data)){
    auto test = random_vector<double>(length, -100.0, 100.0);

    for(int idx=0; idx<n_times; ++idx){
        // Generate a random vectors
        test = random_vector<double>(length, -100.0, 100.0);

        // Sort the vector
        sorting(test);

        // Assert that the vector is sorted.
        BOOST_CHECK_EQUAL(sorted(test), true);
        
    }
}

// Testing the test for sorted arrays
BOOST_AUTO_TEST_CASE(Test_Helpers){

    // Sorted vectors for double
    vector<double> test_1 = {-1.0, 0.0, 0.1, 0.4, 1.0};
    BOOST_CHECK_EQUAL(sorted(test_1), true);

    vector<double> test_2 = {-1.0, 0.0,0.0,  0.1, 0.4, 1.0};
    BOOST_CHECK_EQUAL(sorted(test_2), true);

    vector<double> test_3 = {-1.0, -1.0, -1.0, -1.0};
    BOOST_CHECK_EQUAL(sorted(test_3), true);

    // Not sorted vectors for double
    vector<double> test_4 = {-0.0, -1.0, -1.0, -1.0};
    BOOST_CHECK_EQUAL(sorted(test_4), false);

    // Not sorted vectors for double
    vector<double> test_5 = {-1.0, -1.0, -1.0, -2.0};
    BOOST_CHECK_EQUAL(sorted(test_5), false);

     // Not sorted vectors for double
    vector<double> test_6 = {-1.0, -0.0, -1.0, -0.0};
    BOOST_CHECK_EQUAL(sorted(test_6), false);
}

BOOST_AUTO_TEST_CASE(Test_std){
    benchmark_sorting(N_TIMES, LENGTH, &quicksort_standard_library<double>);
}