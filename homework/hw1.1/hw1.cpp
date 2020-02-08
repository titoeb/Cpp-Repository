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

inline void sum(vector<int> data, int& accumulator){
    accumulator = 0;

    for(int i = 0; i < data.size(); ++i){
        accumulator = accumulator + data[i];
    }
}

int main(){
    int accumulator = 0;
    vector<int> data;

    for(int i = 0; i < N; ++i){
        data.push_back(i);
    }

    sum(data, accumulator);
    cout << "sum is " << accumulator << endl;
    return 0;
}