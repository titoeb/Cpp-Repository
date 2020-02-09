#include<iostream>
#include<cmath>

using namespace std;

template <class numeric>
class duo{
    public:
        // Constructors 

        duo(numeric first, numeric second):first(first), second(second){}

        // Print
        void print(){
            cout << "(" << this->first << ", " << this->second << ")" << endl;
        }

        // Getters & Setters
        void set_first(numeric first){
            this->first = first;
        }

        void set_second(numeric second){
            this->second = second;
        }

        numeric get_first(){
            return this->first;
        }

        numeric get_second(){
            return this->second;
        }

    protected:
        numeric first, second;
};

template <class numeric>
class point:public duo<numeric>{
    public:
        // constructor
        point(numeric first, numeric second):duo<numeric>(first, second){}

        numeric length(){
            return sqrt(duo<numeric>::first + duo<numeric>::second);
        }
};

int main(){
    point<double> b(10.0, 10.0);
    b.print();
    cout << b.length() << endl;
    return 0;
}
