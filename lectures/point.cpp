#include <iostream>
using namespace std;

// Define a new class point that implements a point in a two coordingate system.
class point{
    public:
        // constructors
        point():x(0.0), y(0.0){}
        point(double x, double y):x(x), y(y){}

        double getx(){
            return x;
        }
        double gety(){
            return y;
        }
        void setx(double v){
            x = v;
        }
        void sety(double v){
            y = v;
        }
    private:
        double x,y;
};

// Overload sum operator for the point
point operator+ (point& p1, point& p2){
    point sum = point();
    sum.setx(p1.getx() + p2.getx());
    sum.sety(p1.gety() + p2.gety());
    return sum;
}

/* overload << for printing
 Everything about this program is fine, but the following method. I would like to use 'const point& p' instead of point p here, 
but then, I can't use 'cout << a + b << endl;' due the call by reference and can't acces the methods p.gety() due to const. I am */
ostream& operator<< (ostream& out, point p){
    out << "(" << p.getx() << ", " << p.gety() << ")";
    return out;
}