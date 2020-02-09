#include<iostream>
#include "play_hex.h"
using namespace std;

int main(){
    int size;
    cout << "Welcome the game of hash." << endl;
    cout << "Please insert the size of the board. The size should be more than 1." << endl;
    cin >> size;

    play_hex(size);
}

