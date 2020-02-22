#ifndef HELPERS_H
#define HELPERS_H

#include<vector>
#include<iterator>
#include<iostream>
#include<random>
#include <chrono>

using namespace std;

template<class Sortable>
vector<Sortable> random_vector(int length, Sortable min, Sortable max);

// Check wether a random vector is sorted smallest to largest value
template<class Sortable>
bool sorted(vector<Sortable>& candidate);

// Sort random generated arrays and return average sorting time.
template<class Sortable>
double benchmark_sorting(int n_times, int length, void(*sorting)(vector<Sortable>& data));

#include "helpers.cpp"
#endif