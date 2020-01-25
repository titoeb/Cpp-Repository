#include <iostream>

// The + operator must be usable to aggregate multiple values.
template <class summable>

inline summable sum(const summable data[], int size, summable accu = 0){
    for(int j = 0; j < size; ++j){
        accu += data[j];
    }
    return accu;
}

int main(){
    int arr[5] = {0, 1, 2, 3, 4};
    double arr_double[5] = {0.0, 1.0, 2.0, 3.0, 4.0};
    long arr_long[5] = {0, 1, 2, 3, 4};

    std::cout << "Sum of int array: " << sum(arr, sizeof(arr)/sizeof(arr[0])) << std::endl;
    std::cout << "Sum of double array: " << sum(arr_double, sizeof(arr_double)/sizeof(arr_double[0])) << std::endl;
    std::cout << "Sum of double array: " << sum(arr_long, sizeof(arr_long)/sizeof(arr_long[0])) << std::endl;

    return 0;
}