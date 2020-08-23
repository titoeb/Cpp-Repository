#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int>v(100, 3);
    for(vector<int>::iterator p = v.begin(); p != v.end(); ++p){
        cout << *p << endl;
    } 
}