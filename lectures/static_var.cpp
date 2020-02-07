#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

void incr(int& i){
    static int n = 1;
    i = n++;
}

void outvec(int i){
    cout << i << endl;
}

void old_style(){
    vector<int> v(6);
    for_each(v.begin(), v.end(), incr);
    for_each(v.begin(), v.end(), outvec);
}

void new_style(){
    vector<int>v(6);
    for_each(v.begin(), v.end(), [](int& i){static int n = 1; i = n++;});
    for_each(v.begin(), v.end(), [](int i){cout << i << endl;});
}

int main(){
    cout << "Old Style: " << endl;
    old_style();

    cout << "New Style: " << endl;
    new_style();

    cout << endl << "You should not see a difference." << endl;

    return 0;
}

