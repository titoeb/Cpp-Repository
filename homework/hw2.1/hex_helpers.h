#ifndef HEX_HELPERS_H
#define HEX_HELPERS_H

#include<iostream>
#include<queue>
#include<ctime>
#include<cstdlib>

using namespace std;

// Short logic to convert map to coordinate and vice versa
int coordinate2node(int x_coordinate, int y_coordinate, int dimensions_board);
int node2coordinate_x(int node, int dimensions_board);
int node2coordinate_y(int node, int dimensions_board);

// check whether a node is in the board
bool is_in(int x_coordinate, int y_coordinate, int dimensions_board);

// check whether an integer is neither in dquee a or b.
bool not_in_deques(int node,  deque<int> deque1, deque<int> deque2);

// Random integer between min and max
int rand_int(int begin, int end);

#endif




