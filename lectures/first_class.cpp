#include <iostream>
#include "point.cpp" // Include the point class and its overloaded operators.

int main(){
    // Create point A and print it.
    point a = point(4.5, 3.5);
    cout << "A: " << a << endl;

    // Create point B and print it.
    point b = point(5.5, 6.5);
    cout << "B: " << b << endl;

    // Create the sum of A, B and print it.
    // Either creating it directly
    point sum = a + b;
    cout << "a + b = " << sum << endl;

    // Or creating it implicitly.
    cout << a+b << endl;

    return 0;
}