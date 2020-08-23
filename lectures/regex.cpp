#include<iostream>
#include<regex>
#include<string>

using namespace std;

int main(){
    bool is_in;

    // Put in some strings to test for.
    string tests[] = {"ira.txt", "data.txt", "ira3.txt", "a.out"};

    // Put in the pattern we are looking for
    regex pattern("[a-z]+\\.txt");

    // Iterate over the strings, look for the pattern and put it out;
    for(int idx = 0; idx < 4; ++idx){
        is_in = regex_match(tests[idx], pattern);

        if(is_in){
            // Valid file name
            cout <<  '"' << tests[idx] << '"' << " is a valid file name!" << endl;
        } else {
            // Invalid file name
            cout << '"' <<  tests[idx] << '"' << " is not a valid file name!" << endl;

        }
    }
}

