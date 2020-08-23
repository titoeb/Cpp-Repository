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


// Helpers for quicksort
template<class Sortable>
Sortable med3(Sortable a, Sortable b, Sortable c);
    
template<class Sortable>
Sortable pivot_med3(vector<Sortable>& data, int start, int end);

template<class Sortable>
Sortable pivot_middle(vector<Sortable>& data, int start, int end);

template<class Sortable>
int find_sort_partition(vector<Sortable>& data, int start, int end);

// Helper functions for other search algorithms
template<class Sortable>
int argmin(vector<Sortable>& data, int start, int end);

template<class Sortable>
void swap(vector<Sortable>& data, int idx_1, int idx_2);

// insert data from idx_1 at position idx_2 and move all entries up one.
template<class Sortable>
void insert(vector<Sortable>& data, int insert_into, int taken_from);

template<class Sortable>
void print(vector<Sortable>& data);

#include "helpers.cpp"
#endif