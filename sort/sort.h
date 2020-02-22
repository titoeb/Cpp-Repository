#ifndef SORT_H
#define SORT_H

#include<iostream>
#include<vector>
#include<algorithm>

#include "helpers.h"

using namespace std;

template<class Sortable>
void selectionsort(vector<Sortable>& data);

template<class Sortable>
void insertionsort(vector<Sortable>& data);

template<class Sortable>
void bubblesort(vector<Sortable>& data);

template<class Sortable>
void quicksort(vector<Sortable>& data);

template<class Sortable>
void mergesort(vector<Sortable>& data);

template<class Sortable>
void introsort(vector<Sortable>& data);

template<class Sortable>
void heapsort(vector<Sortable>& data);

template<class Sortable>
void quicksort_standard_library(vector<Sortable>& data);

#include "sort.cpp"
#endif
