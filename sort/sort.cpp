#include "sort.h"

// --------------------------------------------------------------------
// Helper functions
// --------------------------------------------------------------------
template<class Sortable>
int inline argmin(vector<Sortable>& data, int start, int end){
    int min_idx = start;

    for(int idx = start+1; idx < end; ++idx){
        if (data[idx] < data[min_idx]){
            min_idx = idx;
        }
    }

    return min_idx;
}

template<class Sortable>
void inline swap(vector<Sortable>& data, int idx_1, int idx_2){
    Sortable tmp = data[idx_1];
    data[idx_1] = data[idx_2];
    data[idx_2] = tmp;
}

// insert data from idx_1 at position idx_2 and move all entries up one.
template<class Sortable>
void inline insert(vector<Sortable>& data, int insert_into, int taken_from){
    Sortable final_insert = data[taken_from];
    Sortable tmp = data[insert_into];
    Sortable tmp_buffer;

    for(int idx = insert_into; idx < taken_from; ++idx){
        tmp_buffer = data[idx + 1];
        data[idx + 1] = tmp;
        tmp = tmp_buffer;
    }   
    data[insert_into] = final_insert;
}

template<class Sortable>
void print(vector<Sortable>& data){
    for(auto element: data){
        cout << element << " ";
    }
    cout << endl;
}

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
Sortable med3(Sortable a, Sortable b, Sortable c){
    if((b <= a && c >= a)|| (c <= a && b >= a)){
        return a;
    }
    if((a <= b && c >= b)|| (c <= b && a >= b)){
        return b;
    }
    if((a <= c && b >= c)|| (b <= c && a >= c)){
        return c;
    }
    cout << "THIS CAN'T BE!!" << endl;
}
    
template<class Sortable>
Sortable pivot_med3(vector<Sortable>& data, int start, int end){
    end = end - 1;
   return med3(data[start], data[static_cast<int>(static_cast<double>(start + end) / 2.0)], data[end]);
}

template<class Sortable>
Sortable pivot_middle(vector<Sortable>& data, int start, int end){
   return data[static_cast<int>( static_cast<double>(start + end) / 2.0)];
}

template<class Sortable>
int find_sort_partition(vector<Sortable>& data, int start, int end){
   Sortable pivot = pivot_middle(data, start, end);
   int i = start;
   int j = end - 1;

    while(true){
        while(data[i] < pivot){
            i += 1;
        }
        while(data[j] > pivot){
            j -= 1;
        }
        if(i >= j){
            return j;
        } else {
            swap(data, i, j);
        }
    }
}

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
void mergesort(vector<Sortable>& data){

}

// Intro Sort
template<class Sortable>
void introsort(vector<Sortable>& data){

}

// Heap Sort
template<class Sortable>
void heapsort(vector<Sortable>& data){
    
}