#ifndef SELECT_H
#define SELECT_H

#include "helpers.h"

using namespace std;

template<class Sortable>
Sortable quickselect_internal(vector<Sortable>& data, int kth, int start, int end);

template<class Sortable>
Sortable quickselect(vector<Sortable>& data, int kth);

#include "select.cpp"
#endif
