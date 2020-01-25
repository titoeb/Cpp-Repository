#include <iostream>

using namespace std;

template<class summable>
inline summable sum(const summable data[], int len, summable accumulator = 0){
    for(int i = 0; i < len; ++i) accumulator = accumulator  + data[i];
    return accumulator;
}

template<class printable>
inline void print_data(const printable data[], int len){
    for(int i = 0; i< len; ++i) cout << data[i] << endl;
}

int main(){
    int int_array[5] = {0, 1, 2, 3, 4};
    double double_array[5] = {0.0, 1.0, 2.0, 3.0, 4.0};

    cout << "Array_int: " << endl;
    print_data(int_array, 5);
    cout << "The int_array sum is " << sum(int_array, 5) << endl;
    
    cout << "double_array: " << endl;
    print_data(double_array, 5);
    cout << "The double_array sum is " << sum(double_array, 5) << endl;
}