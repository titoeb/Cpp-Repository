#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test Hexgraph

#include <boost/test/unit_test.hpp>

#include "../hexgraph.h"

// A small sanity test for hexgraph.
BOOST_AUTO_TEST_CASE(Test_Hexgraph_Direct_Connections) {
  hexGraph test(3);
  test.addNode(0, 0);
  test.addNode(1, 1);
  test.addNode(2, 2);


  // Check Node (0, 0)
  // (0, 0) should be connected to itself.
  BOOST_CHECK_EQUAL(test.is_connected(0,0,0,0), true);
  
  // (0, 0) should be connected to (1, 0)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,1,0), true);

  // (0, 0) should be connected to (0, 1)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,0,1), true);

  // Check the false connection
  // (0, 0) should not be connected to (1, 1)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,1,1), false);

  // (0, 0) should not be connected to (0, 2)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,0,2), false);

  // (0, 0) should not be connected to (1, 2)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,1,2), false);

  // (0, 0) should not be connected to (2,0)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,2,0), false);

  // (0, 0) should not be connected to (2, 1)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,2,1), false);

  // (0, 0) should not be connected to (2, 2)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,2,2), false);


    // check Node (1, 1)
  // (1, 1) should be connected to itself
  BOOST_CHECK_EQUAL(test.is_connected(1,1,1,1), true);

  // (1, 1) should be connected to (0, 1)
  BOOST_CHECK_EQUAL(test.is_connected(1,1,0,1), true);

  // (1, 1) should be connected to (0, 2)
  BOOST_CHECK_EQUAL(test.is_connected(1,1,0,2), true);

  // (1, 1) should be connected to (1, 0)
  BOOST_CHECK_EQUAL(test.is_connected(1,1,1,0), true);

  // (1, 1) should be connected to (1, 2)
  BOOST_CHECK_EQUAL(test.is_connected(1,1,1,2), true);

  // (1, 1) should be connected to (2, 0)
  BOOST_CHECK_EQUAL(test.is_connected(1,1,2,0), true);

  // (1, 1) should be connected to (2, 1)
  BOOST_CHECK_EQUAL(test.is_connected(1,1,2,1), true);

  // (1, 1) should not be connect to (0, 0)
  BOOST_CHECK_EQUAL(test.is_connected(1,1,0,0), false);

  // (1,1) should not be connected to (2, 2) 
  BOOST_CHECK_EQUAL(test.is_connected(1,1,2,2), false);


  // Check Node (2, 2)
  // (2,2) should be connected to (2,1)
  BOOST_CHECK_EQUAL(test.is_connected(2,2,2,1), true);

  // (2,2) should be connected to (1,2)
  BOOST_CHECK_EQUAL(test.is_connected(2,2,1,2), true);

  // Add some additional nodes to make (0,0) and (2, 2) connected.
  test.addNode(1, 0);
  test.addNode(2, 1);

  // Check some nodes indirect connections
  // (0,0) should be connected to (2,2)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,2,2), true);
}

BOOST_AUTO_TEST_CASE(Test_Hexgraph_Indirect_Connections) {
  hexGraph test(3);
  test.addNode(0, 0);
  test.addNode(1, 1);
  test.addNode(2, 2);
  test.addNode(1, 0);
  test.addNode(2, 1);

  // Check some nodes indirect connections
  // (0,0) should be connected to (2,2)
  BOOST_CHECK_EQUAL(test.is_connected(0,0,2,2), true);
}

BOOST_AUTO_TEST_CASE(Test_Hexgraph_is_in){
  hexGraph test(3);
  test.addNode(0, 0);
  test.addNode(1, 1);
  test.addNode(2, 2);

  // All the inserted nodes should be in there.
  BOOST_CHECK_EQUAL(test.node_exists(0,0), true);
  BOOST_CHECK_EQUAL(test.node_exists(1,1), true);
  BOOST_CHECK_EQUAL(test.node_exists(2,2), true);
}