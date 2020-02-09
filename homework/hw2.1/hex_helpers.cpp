#include "hex_helpers.h"
// Short logic to convert map to coordinate and vice versa
int coordinate2node(int x_coordinate, int y_coordinate, int dimensions_board){
    return x_coordinate * dimensions_board + y_coordinate;
}

int node2coordinate_x(int node, int dimensions_board){
    return node / dimensions_board;
}

int node2coordinate_y(int node, int dimensions_board){
    return node % dimensions_board;
}

bool is_in(int x_coordinate, int y_coordinate, int dimensions_board){
    // Test wether the coordinates would fall into the dimensions of the board

    // Test x_coordinate
        if (x_coordinate < 0) return false;
        if (x_coordinate >= dimensions_board) return false;

    // Test y_coordinate
        if (y_coordinate < 0) return false;
        if (y_coordinate >= dimensions_board) return false;
    
    return true;
}
