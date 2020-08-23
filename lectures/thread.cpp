#include<iostream>
#include<string>
#include<thread>

using namespace std;

const int N_THREADS = 8;
const long N_STUFF = 1000000000;

void message(){
    cout << "This is my Message!" << endl;
};

void simple_example(){
    // Declare a thread with a lambda expression
    thread foo([](){
        cout << "Hello World! " << endl;
    });

    // Define another thread with a message
    thread bar(message);

    bar.join();
    foo.join();
}

void do_stuff(){
    double num;
    for(int idx = 0; idx < N_STUFF; ++idx){
        num += 2.0;
    }
}

void test_parallelism(){
    thread thread_array[N_THREADS];
    for(int n_thread = 0; n_thread < N_THREADS; ++n_thread){
        thread_array[n_thread] = thread(do_stuff);
    }

    for(int n_thread = 0; n_thread < N_THREADS; ++n_thread){
        thread_array[n_thread].join();
    }
}

int main(){
    test_parallelism();
}