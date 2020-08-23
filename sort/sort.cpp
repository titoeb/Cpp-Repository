#include "sort.h"
// --------------------------------------------------------------------
// The search algorithms
// --------------------------------------------------------------------

// Use the standard library sort as a benchmark!
template<class Sortable>
void quicksort_standard_library(vector<Sortable>& data){
    sort(data.begin(), data.end());
}

// Selection sort!
template<class Sortable>
void selectionsort(vector<Sortable>& data){
    for(int idx = 0; idx < data.size(); ++idx){
        swap(data, idx, argmin(data, idx, data.size()));
    }
}

// Insertion Sort!
template<class Sortable>
void insertionsort(vector<Sortable>& data, int start, int end){
    for(int idx = (start + 1); idx < end; ++idx){
        for(int idx_reverse = idx - 1; idx_reverse >= 0; --idx_reverse){
            if((data[idx_reverse] > data[idx]) || (idx_reverse == 0 && data[idx_reverse] <= data[idx])){
                insert(data, idx, idx_reverse);
                break;
            }
        }
    }
}

template<class Sortable>
void insertionsort(vector<Sortable>& data){
    insertionsort(data, 0, static_cast<int>(data.size()));
}

// Bubble sort!
template<class Sortable>
void bubblesort(vector<Sortable>& data){
    bool swapped = true;
    int n_iterations = 1;
    while(swapped){
        swapped = false;
        for(int idx = 0; idx < data.size() - n_iterations; ++idx){
            if (data[idx] > data[idx + 1]){
                swap(data, idx, idx + 1);
                swapped = true;
            }
        }
        n_iterations += 1;
    }
}

// Quick sort!
template<class Sortable>
void quicksort_internal(vector<Sortable>& data, int start, int end){
   if(end > start + 1){
       int pivot = find_sort_partition(data, start, end);
       quicksort_internal(data, start, pivot);
       quicksort_internal(data, pivot + 1, end);
   }
}

template<class Sortable>
void quicksort(vector<Sortable>& data){
    quicksort_internal(data, 0, data.size());
}

// Merge sort
template<class Sortable>
void merge(vector<Sortable>& data,vector<Sortable>& buffer, int start_1, int end_1, int start_2, int end_2){
    /*cout << "merge(data, buffer, " << start_1 << ", " << end_1 << ", " << start_2 << ", " << end_2 << ")" << endl;
    cout << "\tBefore Sorting: ";
    for(auto elem: data) cout << elem << " ";
    cout << endl;*/


    // Merge the two sections data[start_1:end_1], data[start2:end_2] into the buffer
    int iter_1 = start_1;
    int iter_2 = start_2;
    int buffer_idx = 0;
    while((iter_1 < end_1) && (iter_2 < end_2)){
        if (data[iter_1] < data[iter_2]){
            // Append from start_1, end_1 to the buffer
            buffer[buffer_idx] = data[iter_1];
            ++buffer_idx;
            ++iter_1;
        } else {
            // Append from start_2, end_1 to the buffer.
            buffer[buffer_idx] = data[iter_2];
            ++buffer_idx;
            ++iter_2;
        }
    }

    while(iter_1 < end_1){
        buffer[buffer_idx] = data[iter_1];
        ++buffer_idx;
        ++iter_1;
    }

    while(iter_2 < end_2){
        buffer[buffer_idx] = data[iter_2];
        ++buffer_idx;
        ++iter_2;
    }

    iter_1 = start_1;
    iter_2 = start_2;
    // Write the buffer back into the original array.
    for(int idx = 0; idx < buffer_idx; ++idx){
        if (iter_1 <  end_1){
            data[iter_1] = buffer[idx];
            ++iter_1;
        } else {
            data[iter_2] = buffer[idx];
            iter_2++;
        }
    }

    /*cout << "\tAfter Sorting: ";
    for(auto elem: data) cout << elem << " ";
    cout << endl;*/
}

template<class Sortable>
void mergesort_internal(vector<Sortable>& data, vector<Sortable>& buffer, int start, int end){
    int middle = static_cast<int>(static_cast<double>(start + end) / 2.0);

    //cout << "mergesort_internal(data, buffer, " << start <<", " << end << ")" << endl;
    //cout << "\tmiddle: " << middle << endl; 
    // Call mergesort on subarrays
    if ((end - start) > 1){
        mergesort_internal(data, buffer, start, middle);
        mergesort_internal(data, buffer, middle, end);

        if((end-start) == 2){
            if(data[start] > data[end-1]){
                swap(data, start, end-1);
            }
        } else {
            merge(data, buffer, start, middle, middle, end);
        }
    }
    // I know that within start, middle and middle, end the arrays are sorted
    // I have to merge these two arrays now.
    
}
template<class Sortable>
void mergesort_internal(vector<Sortable>& data, int start, int end){
    // Create the buffer
    vector<Sortable> buffer(data.size());
    mergesort_internal(data, buffer, start, end);
}

template<class Sortable>
void mergesort(vector<Sortable>& data){
    mergesort_internal(data, 0, data.size());
}

// Heap Sort
/* To improve:
    - Build your own heap
    - Make it in place by storing references to the vectors element in the heap.
*/
template<class Sortable>
void heapsort(vector<Sortable>& data){
    // Built the heap
    make_heap(data.begin(), data.end());
    sort_heap(data.begin(), data.end());
}