#include<iostream>
#include<string>

using namespace std;

class simple{
    public:
        // Compiler-generated constructor
        simple() = default;

        // Surpressed conversion constructor
        simple(double x)= delete;

        // Finally, a real constructor:
        simple(int x, int y):p(x), q(y){};

        // Delegate constructor
        simple(int x): simple(x, 1){};

        // Move semantics
        simple(simple&& x): simple(x.p, x.q){
            x.p = x.q = 0;
        }

    private:
        // default initiallizer can be overriden
        int p = 0;
        int q = 1;
};

class rational: public simple{
    public:
        
        // implicitly declares constructors, but use base
        using simple::simple;
};

int main(){
    return 0;
}
