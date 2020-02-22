#ifndef HELPERS_H
#define HELPERS_H

#include<vector>
#include<iterator>
#include<iostream>

using namespace std;

template<class Sortable>
vector<Sortable> random_vector(int length, Sortable in, Sortable max);

// Check wether a random vector is sorted smallest to largest value
template<class Sortable>
bool sorted(vector<Sortable>& candidate);

#include "helpers.cpp"
#endif