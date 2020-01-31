#include<iostream>
#include<cassert>
#include<vector>
#include<iterator>

using namespace std;

// Possible 'color' of the card.
enum class suit: short{SPADE, HEART, DIAMOND, CLUB};

// operator<< overloading for suit
ostream& operator<< (ostream& out, const suit& p){
    switch(p){
        case suit::SPADE:
            cout << "SPADE";
            break;
        case suit::HEART:
            cout << "HEART";
            break;
        case suit::DIAMOND:
            cout << "DIAMOND";
            break;
        case suit::CLUB:
            cout << "CLUB";
            break;
    }
    return out;
}

// operator++ overloading for suit
suit operator++ (const suit& col){
    return static_cast<suit>(( static_cast<int>(col) + 1) % static_cast<int>(suit::CLUB));
}

// Pips defines the value a cart can have.
class pips{
    public:
        // Construtors
        // In default take value one.
        pips():v(1){}
        
        // Constructor with
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
    cout << "(" << c.s << ", " << c.v  << ")";
    return out;
}

class Deck{
    public:
    // Constructors
        // Empty constructor, no other constructor needed.
        Deck(){
            // Initiallize the deck.
            this->deck.resize(100);
            // Be aware this depends on
                // 1) that the ++ operator is overloaded for the suit class enum
                // 2) that the enum class suit is number continously 0, ..., n and does not have custom numeration.
            for(auto s = static_cast<int> (suit::SPADE); s <= static_cast<int>(suit::CLUB); ++s){
                for(int i = 1; i < 14; ++i){
                    card c(static_cast<suit>(s), i);
                    this->deck[i-1] = c;
                }
            }
        }
    
    // Custom methods
        // print out the deck, this could also be done via overloading of operator<<
        void print(){
            for(auto c = this->deck.begin(); c != this->deck.end(); ++c){
               if(c != this->deck.begin()){
                    cout << ", " << *c;
                } else {
                    cout << *c;
                }
            }
            cout << endl;
        }
    private:
        vector<card> deck;
};

class Hand{
    public:
    // Constructors
        // Empty constructor
        Hand(){}

        // Constructor with an initial card
        Hand(card c){ // I decide to copy the card explicitly, so that it cannot be change from out of the class
            this->cards[cards.size()-1] = c;
        }
    // Custom methods
        // print out the deck, this could also be done via overloading of operator<<
        void print(){
            for(auto c = this->cards.begin(); c != this->cards.end(); ++c){
                if(c != this->cards.begin()){
                    cout << ", " << *c;
                } else {
                    cout << *c;
                }
            }
            cout << endl;
        }

        // Add a cart to the deck
        void add(card c){
            this->cards.resize(this->cards.size()+1);
            this->cards[cards.size() - 1] = c;
        }  
        // Check whether the hand is a flush
        bool is_flush(){
            suit s = this->cards[0].get_suit();
            for(auto p: this->cards){
                cout << p << endl;
            }
            return true;
        }

        // Check whether the hand is a straight.
        bool is_straight(){

        }
    private:
        vector<card> cards;
};


int main(){
    card c(suit::SPADE, 1);
    Hand h;
    h.add(c);
    h.print();

    card c2(suit::SPADE, 2);
    h.add(c2);
    h.print();
    /* -------------------------
        I am currently at 18:00
    -------------------------- */

    return 1;
}