#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test Sort

#include <boost/test/unit_test.hpp>
#include "helpers.h"

#include<vector>

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