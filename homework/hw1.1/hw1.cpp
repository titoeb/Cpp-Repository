// C++ Course, homework 1
// Convert this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function

// the following is the 
#include <iostream>
#include <vector>

const int N = 40;
using namespace std;

// Compute the sum of data and store it in the integer accumulator.
inline void sum(vector<int> data, int& accumulator){
    accumulator = 0;

    for(int i = 0; i < data.size(); ++i){
        accumulator = accumulator + data[i];
    }
}

// Example of the usage of the sum function.
int main(){
    int accumulator = 0;
    vector<int> data;

    // Put the numbers 0, ... , N into the vector
    for(int i = 0; i < N; ++i){
        data.push_back(i);
    }

    // Compute the sum of the vector with the sum function defined above.
    sum(data, accumulator);

    // Return the output to the user.
    cout << "sum is " << accumulator << endl;
    return 0;
}