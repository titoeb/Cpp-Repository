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

// Create a random vector containing values between min and max
template<class Sortable>
vector<Sortable> sorted_vector(int length, Sortable min, Sortable max){

    // Create the container.
    vector<Sortable> random_vector(length);
    Sortable step = static_cast<double>(max - min) / length;

    // Assign random values.
    for(int idx=0; idx < length; ++idx){
        random_vector[idx] = min + static_cast<Sortable>(step * idx);
    }
    
    return  random_vector;
}

template<class Sortable>
vector<Sortable> reverse_sorted_vector(int length, Sortable min, Sortable max){

    // Create the container.
    vector<Sortable> random_vector(length);
    Sortable step = static_cast<double>(max - min) / length;

    // Assign random values.
    for(int idx=0; idx < length; ++idx){
        random_vector[idx] = max - static_cast<Sortable>(step * idx);
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

template<class Sortable>
double benchmark_sorting_random(int n_times, int length, void(*sorting)(vector<Sortable>& data)){
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

template<class Sortable>
double benchmark_sorting_sorted(int n_times, int length, void(*sorting)(vector<Sortable>& data)){
    double time = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto test = sorted_vector<double>(length, -100.0, 100.0);

    for(int idx=0; idx<n_times; ++idx){
        // Generate a random vectors
        auto test = sorted_vector<double>(length, -100.0, 100.0);

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

template<class Sortable>
double benchmark_reverse_sorting_sorted(int n_times, int length, void(*sorting)(vector<Sortable>& data)){
    double time = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto test = sorted_vector<double>(length, -100.0, 100.0);

    for(int idx=0; idx<n_times; ++idx){
        // Generate a random vectors
        auto test = reverse_sorted_vector<double>(length, -100.0, 100.0);

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

// Sort random generated arrays and return average sorting time.
template<class Sortable>
double benchmark_sorting(int n_times, int length, void(*sorting)(vector<Sortable>& data)){
    double random_sorting = benchmark_sorting_random(n_times, length, sorting);
    double sorted_sorting = benchmark_sorting_sorted(n_times, length, sorting);
    double reverse_sorted_sorting = benchmark_reverse_sorting_sorted(n_times, length, sorting);

    cout << "Random sorting took " << random_sorting << endl;
    cout << "Sorted sorting took " << sorted_sorting << endl;
    cout << "Reverse Sorted Sorting took " << reverse_sorted_sorting << endl;

    return (random_sorting + sorted_sorting + reverse_sorted_sorting) / 3.0;
}

// Helpers for quicksort
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

// Helper functions for other search algorithms
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