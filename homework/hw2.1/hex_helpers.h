#ifndef HEX_HELPERS_H
#define HEX_HELPERS_H

#include<iostream>
using namespace std;

// Short logic to convert map to coordinate and vice versa
int coordinate2node(int x_coordinate, int y_coordinate, int dimensions_board);
int node2coordinate_x(int node, int dimensions_board);
int node2coordinate_y(int node, int dimensions_board);
bool is_in(int x_coordinate, int y_coordinate, int dimensions_board);

#endif




