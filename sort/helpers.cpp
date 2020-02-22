#include "helpers.h"

// Create a random vector containing values between min and max
template<class Sortable>
vector<Sortable> random_vector(int length, Sortable in, Sortable max){
    vector<Sortable> random_vector(length);

    // Assign random values.
    for(auto element=random_vector.start(); element != random_vector.end(); ++element){
        //element = static_cast<Sortable>();
    }
}

// Check wether a random vector is sorted smallest to largest value
template<class Sortable>
bool sorted(vector<Sortable>& candidate){
    for(auto element = 0; element < candidate.size(); ++element){

        // If the current element is larger then the next element, then the vector is not sorted!
        if (candidate[element] > candidate[element + 1]){
            return false;
        }

        // If the next element is the final element then return True
        if ((element + 2) == candidate.size()){
            return true;
        }
    }
}