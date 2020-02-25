#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test Sort

#include <boost/test/unit_test.hpp>
#include "helpers.h"
#include "sort.h"
#include "select.h"
 
// SET-UP:
const int N_TIMES = 100;
const int LENGTH  = 1000;
bool printing = false;

// Helper function to avoid repetitive code in testing:
// Testing a given sorting algorithm on random data
template<class Sortable>
void random_test_sorting(int n_times, int length, void(*sorting)(vector<Sortable>& data)){
    auto test = random_vector<double>(length, -100.0, 100.0);

    for(int idx=0; idx<n_times; ++idx){
        // Generate a random vectors
        test = random_vector<double>(length, -100.0, 100.0);

        // if print is true print it out
        if(printing){
            cout << "Random vector: " << endl;
            for(auto elem: test) cout << elem << " ";
            cout << endl;
        }

        // Sort the vector
        sorting(test);

        if(printing){
            cout << "Sorted vector: " << endl;
            for(auto elem: test) cout << elem << " ";
            cout << endl;
        }

        // Assert that the vector is sorted.
        BOOST_CHECK_EQUAL(sorted(test), true);
    }
}

// Check wether a random vector is sorted smallest to largest value
template<class Sortable>
bool kth_value(vector<Sortable>& candidate, Sortable value, int k){
    quicksort(candidate);
    if(candidate[k] == value){
        return true;
    } else {
        return false;
    }
}

template<class Sortable>
void random_test_kth(const int n_times, const int length, Sortable(*find_kth)(vector<Sortable>& data, int kth)){
    auto test = random_vector<double>(length, -100.0, 100.0);
    double kth;
    bool result;
    int random_idx;

    // generate a random idx
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(0,length);
    for(int idx=0; idx<n_times; ++idx){
        // Generate a random vectors
        test = random_vector<double>(length, -100.0, 100.0);

        // Generate random index to find:
        random_idx = dist6(rng); 

        // Sort the vector
        kth = find_kth(test, random_idx);

        // Assert that the vector is sorted.
        result = kth_value(test, kth, random_idx);
        BOOST_CHECK_EQUAL(result, true);
    }
}

// TESTING 
BOOST_AUTO_TEST_CASE(Test_kth_value){

    vector<double> test = {0.0, 4.0, -1.0, 2.0};
    bool result;

    print(test);

    cout << quickselect(test, 2) << endl;

    result = kth_value(test, quickselect(test, 3), 3);
    BOOST_CHECK_EQUAL(result, true);

    result = kth_value(test, 4.0, 2);
    BOOST_CHECK_EQUAL(result, false);
    
    result = kth_value(test, 2.0 , 2);
    BOOST_CHECK_EQUAL(result, true);
} 

BOOST_AUTO_TEST_CASE(Test_quicksort){
    random_test_kth(N_TIMES, LENGTH, &quickselect<double>);
}

/*
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


BOOST_AUTO_TEST_CASE(Test_quicksort){
    random_test_sorting(N_TIMES, LENGTH, &quicksort<double>);
}

BOOST_AUTO_TEST_CASE(Test_std){
    random_test_sorting(N_TIMES, LENGTH, &quicksort_standard_library<double>);
}

BOOST_AUTO_TEST_CASE(Test_selectionsort){
    random_test_sorting(N_TIMES, LENGTH, &selectionsort<double>);
}

BOOST_AUTO_TEST_CASE(Test_insertionsort){
    random_test_sorting(N_TIMES, LENGTH, &insertionsort<double>);
}

BOOST_AUTO_TEST_CASE(Test_bubblesort){
    random_test_sorting(N_TIMES, LENGTH, &bubblesort<double>);
} 

BOOST_AUTO_TEST_CASE(Test_mergesort_1){
    random_test_sorting(N_TIMES, LENGTH, &mergesort<double>);
}

BOOST_AUTO_TEST_CASE(Test_heapsort){
    random_test_sorting(N_TIMES, LENGTH, &heapsort<double>);
}

BOOST_AUTO_TEST_CASE(Test_merge_1){
    vector<double> test = {0.0, 3.0, 2.0, 4.0};
    vector<double> buffer(test.size());
    merge(test, buffer, 0, 2, 2, 4);
    BOOST_CHECK_EQUAL(sorted(test), true);
}

BOOST_AUTO_TEST_CASE(Test_merge_2){
    vector<double> test = {0.0, 2.0, 3.0, 4.0};
    vector<double> buffer(test.size());
    merge(test, buffer, 0, 2, 2, 4);
    BOOST_CHECK_EQUAL(sorted(test), true);
}

BOOST_AUTO_TEST_CASE(Test_merge_3){
    vector<double> test = {3.0, 4.0, 0.0, 2.0};
    vector<double> buffer(test.size());
    merge(test, buffer, 0, 2, 2, 4);
    BOOST_CHECK_EQUAL(sorted(test), true);
}*/