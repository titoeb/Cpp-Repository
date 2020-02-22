#include<iostream>

using namespace std;

class base_class{
    public:
        int i;
        void print_i() const{
            cout << i << " inside the base class." << endl;
        }
};

class special_class: public base_class{
    public:
        void print_i() const{
            cout << i << " inside special class." << endl;
        }
};

int main(){
    base_class b;
    base_class* pb = &b;

    special_class s;
    special_class* ps = &s;

    base_class* pbs = &s;

    b.i = 1;
    s.i = 2;

    //pb->print_i();
    //ps->print_i();
    pbs->print_i();

    return 0;
}