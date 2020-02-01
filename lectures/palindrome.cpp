#include<iostream>
#include<iterator>
#include<list>

using namespace std;

/* REVERSE:
    Write a function that checks whether a container contains a polindrome.
    To do so, write a reverse function that inverts the container, that has an iterator that can move bidirectional.
*/

// Test container for palindrome.
template<typename Bidirectional>
bool is_palindrome(Bidirectional first, Bidirectional last){
    last--;

    while(true){
        if (first == last){
            // We arrive at the middle position and all elements so far were the same.
            return true;
        } else {
            if (*first != *last){
                // We found an element that was different
                return false;
            } else {
                // Iterate, but make sure the we are not in the middle
                first++;
                if (first == last) return true;
                last--;
            }
        }
    }
}

// Small test for palindrome
int main(){
    list<int>v1 = {1, 2, 5,  4, 1}; 
    cout << is_palindrome(v1.begin(), v1.end()) << endl;
    return 0;
}