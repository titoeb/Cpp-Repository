#include<iostream>
#include<cassert>


using namespace std;

// Possible 'color' of the card.
enum class suit: short{SPADE, HEART, DIAMOND, CLUB};
// operator<< overloading for suit
ostream& operator<< (ostream& out, const suit& p){
    cout << p;
    return out;
}

// Pips defines the value a cart can have.
class pips{
    public:
        // Construtors
        pips(int val):v(val){
            assert(v>0 && v<14);
        }
        friend ostream& operator<< (ostream& out, const pips& p);
        
        // Getter and setter
        int get_pips(){
            return v;
        }

    private:
        int v;
};

// operator<< overloading for pips
ostream& operator<< (ostream& out, const pips& p){
    cout << p.v;
    return out;
}

// Define the class.
class card{
    public:
    // Constructors
        // empty constructor results in a SPADE with value 1.
        card():s(suit::SPADE), v(1){}

        // You can also just give the suit and the SPADE
        card(suit s, pips v):s(s), v(v){}

    // friends
        // friend for overloading the operator<<
        friend ostream& operator<<(ostream& out, const card& c);

    // Getter / Setter
        pips get_pips() const{
            return v;
        }
        suit get_suit() const{
            return s;
        }
        
    private:
        // A card has a value (pips) and a 'color' (german) suit.
        suit s; 
        pips v;
};

// Overload operator<< for the card type.
ostream& operator<<(ostream& out, const card& c){
    cout << c.v << c.s;
    return out;
}


int main(){
    return 1;
}