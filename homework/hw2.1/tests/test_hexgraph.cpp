#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test Hexgraph

#include <boost/test/unit_test.hpp>

#include "../hexgraph.h"

// A small sanity test for hexgraph.
BOOST_AUTO_TEST_CASE(Test_Hexgraph_1) {
  hexGraph test(3);
  test.addNode(0, 0);
  test.addNode(1, 1);
  test.addNode(2, 1);
  
  // (0, 0) should be connected to itself.
  BOOST_CHECK_EQUAL(test.is_connected(0,0,0,0), true);
  
  // (0, 0) should be connected to (1, 1)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,1,1), true);

  // (0, 0) should be connected to (2, 1)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,2,1), true);
}
