#include<iostream>
#include<cmath>

using namespace std;

class duo{
    public:
        duo():first(0.0), second(0.0){}

        void set_first(float first){
            this->first = first;
        }

        void set_second(float second){
            this->second = second;
        }

        float get_first(){
            return this->first;
        }

        float get_second(){
            return this->second;
        }

    protected:
        float first, second;
};

class point:public duo{
    public:
        float length(){
            return sqrt(first* first + second* second);
        }
};
