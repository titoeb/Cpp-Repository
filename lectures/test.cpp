#include<iostream>

using namespace std;

#define foo1(a)(a * a)

int main(){
    
    cout << "foo1 = " << foo1( 1 + 2 ) << "\n";
    return 0;
}
