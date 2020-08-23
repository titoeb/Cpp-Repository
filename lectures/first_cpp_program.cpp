#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
const int sides = 6;

// Simulate  a single throw of a dice with sides sides
inline int r_side(){
    return rand() % sides + 1;
}

int simulation(){
    const int n_dice = 2;
    int d1, d2;
    int trials;

    srand(clock());
    cout << "\nEnter number of trials: ";
    cin >> trials; 
    int* outcomes = new int[n_dice * sides + 1];

    // Simulate the outcomes
    for(int j=0; j < trials; ++j){
        outcomes[r_side() + r_side()]++;
    }

    // print the results
    for(int j=2; j < sides * n_dice + 1; ++j){
        cout << "j = " << j << " p = " << static_cast<double>(outcomes[j])/trials << endl;
    }
    return 0;
}

int main(void){
    return simulation();
}

