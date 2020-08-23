
#include<map>
#include<unordered_map>
#include<string>
#include<iostream>

using namespace std;

int main(){
    
    map<unsigned long, string> worker;
    unordered_map<unsigned int, unsigned int> payroll;

    // Create some workers and their respective pay.
    unsigned int total_pay = 0;
    worker[1] = "Tim Toebrock";
    payroll[1] = 40000;
    worker[200] = "Eva Schmitz";
    payroll[200] = 55000;

    // Write out the workers.
    for(auto p = worker.begin(); p!= worker.end(); ++p){
        cout << "Name: " << (*p).second << "\t id no. " << (*p).first << endl;
    }

    // Compute the total pay.
    for(auto p = payroll.begin(); p!= payroll.end(); ++p){
        total_pay += (*p).second;
    }

    cout << "The total pay is " << total_pay << endl;

    // Write out the total pay.
    return 0;
}