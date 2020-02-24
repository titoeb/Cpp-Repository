#include "select.h"

// Quick Select!
template<class Sortable>
Sortable quickselect_internal(vector<Sortable>& data, int kth, int start, int end){
   if(end > start + 1){
       int pivot = find_sort_partition(data, start, end);
       if (pivot > kth){
           return quickselect_internal(data,kth,  start, pivot);
       } else {
           return quickselect_internal(data, kth,  pivot + 1, end);
       }
   } else {
       return data[start];
   }
}

template<class Sortable>
Sortable quickselect(vector<Sortable>& data, int kth){
    return quickselect_internal(data, kth, 0, data.size());
}
