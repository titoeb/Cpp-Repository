#include "helpers.h"

// Create a random vector containing values between min and max
template<class Sortable>
vector<Sortable> random_vector(int length, Sortable min, Sortable max){

    // Initiate the random number generator.
    random_device device;
    mt19937 generator(device());
    uniform_real_distribution<double> distribution(static_cast<double>(min), static_cast<double>(max));

    // Create the container.
    vector<Sortable> random_vector(length);

    // Assign random values.
    for(auto element=random_vector.begin(); element != random_vector.end(); ++element){
        *element = static_cast<Sortable>(distribution(generator) );
    }
    
    return  random_vector;
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

// Sort random generated arrays and return average sorting time.
template<class Sortable>
double benchmark_sorting(int n_times, int length, void(*sorting)(vector<Sortable>& data)){
    double time = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto test = random_vector<double>(length, -100.0, 100.0);

    for(int idx=0; idx<n_times; ++idx){
        // Generate a random vectors
        test = random_vector<double>(length, -100.0, 100.0);

        // Measure time to sort it
        start = std::chrono::high_resolution_clock::now();
        sorting(test);
        end = std::chrono::high_resolution_clock::now();

        time = time + static_cast<double> (chrono::duration_cast<std::chrono::microseconds>(end - start).count());

        // Ensure that the vector really is sorted correctly now.
        if (!sorted(test)){
            cout << "The Search function does not work!" << endl;
            return -1.0;
        }
    }

    return time / static_cast<double>(n_times);
}