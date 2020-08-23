#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>

using namespace std;

// Possible 'color' of the card.
enum class suit : short
{
    SPADE,
    HEART,
    DIAMOND,
    CLUB
};

// operator<< overloading for suit
ostream &operator<<(ostream &out, const suit &p)
{
    switch (p)
    {
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
suit operator++(const suit &col)
{
    return static_cast<suit>((static_cast<int>(col) + 1) % static_cast<int>(suit::CLUB));
}

// Pips defines the value a cart can have.
class pips
{
public:
    // Construtors
    // In default take value one.
    pips() : v(1) {}

    // Constructor with
    pips(int val) : v(val)
    {
        assert(v > 0 && v < 14);
    }
    friend ostream &operator<<(ostream &out, const pips &p);

    // Getter and setter
    int get_pips()
    {
        return v;
    }

private:
    int v;
};

// operator<< overloading for pips
ostream &operator<<(ostream &out, const pips &p)
{
    cout << p.v;
    return out;
}

// Define the class.
class card
{
public:
    // Constructors
    // empty constructor results in a SPADE with value 1.
    card() : s(suit::SPADE), v(1) {}

    // You can also just give the suit and the SPADE
    card(suit s, pips v) : s(s), v(v) {}

    // friends
    // friend for overloading the operator<<
    friend ostream &operator<<(ostream &out, const card &c);

    // Getter / Setter
    pips get_pips() const
    {
        return v;
    }
    suit get_suit() const
    {
        return s;
    }

private:
    // A card has a value (pips) and a 'color' (german) suit.
    suit s;
    pips v;
};

// Overload operator<< for the card type.
ostream &operator<<(ostream &out, const card &c)
{
    cout << "(" << c.s << ", " << c.v << ")";
    return out;
}

// This class simulates a hand of 5 cards as in poker
class hand
{
public:
    // Constructors
    // Empty constructor
    hand() {}

    // Constructor with an initial card
    hand(card c)
    { // I decide to copy the card explicitly, so that it cannot be change from out of the class
        this->cards[cards.size() - 1] = c;
    }
    // Custom methods
    // print out the deck, this could also be done via overloading of operator<<
    void print()
    {
        for (auto c = this->cards.begin(); c != this->cards.end(); ++c)
        {
            if (c != this->cards.begin())
            {
                cout << ", " << *c;
            }
            else
            {
                cout << *c;
            }
        }
        cout << endl;
    }

    // Add a cart to the deck
    void add(card c)
    {
        this->cards.resize(this->cards.size() + 1);
        this->cards[cards.size() - 1] = c;
    }

    // Check whether the hand is a flush
    bool is_flush()
    {
        auto last = this->cards.begin();
        for (auto p = (this->cards.begin() + 1); p != this->cards.end(); ++p)
        {
            if (p->get_suit() != last->get_suit())
            {
                return false;
            }
            last = p;
        }
        return true;
    }

    // Check whether the hand is a straight.
    bool is_straight()
    {
        int pips_v[5], i = 0;

        // Put the value of the cards in local array.
        for (auto p = this->cards.begin(); p != this->cards.end(); ++p)
        {
            pips_v[i] = (p->get_pips()).get_pips();
            i++;
        }

        // Sort the array.
        sort(pips_v, pips_v + 5);

        // Test whether the sorted array is a straight or not.

        // First test the special case of 1, 10, 11, 12, 13
        if ((pips_v[0] == 1) && (pips_v[1] == 10) && (pips_v[2] == 11) && (pips_v[3] == 12) && (pips_v[4] == 13))
        {
            return true;
        }

        // The hand may still be a flush if all values are ascending by one.
        for (int i = 0; i < 4; i++)
        { // A bit odd: We compare first to second, second to third and so on ... therefore we need n -1 iterations

            // It at any point the past value is not the current value -1 then the order is not ascending only.
            if (pips_v[i] != (pips_v[i + 1] - 1))
            {
                return false;
            }
        }
        return true;
    }

private:
    vector<card> cards;
};

// This class simulates a full poker deck of 52 cards.
class deck
{
public:
    // Constructors
    // Empty constructor, no other constructor needed.
    deck()
    {
        // Initiallize the deck.
        this->cards.resize(52);
        // Be aware this depends on
        // 1) that the ++ operator is overloaded for the suit class enum
        // 2) that the enum class suit is number continously 0, ..., n and does not have custom numeration.
        for (auto s = static_cast<int>(suit::SPADE); s <= static_cast<int>(suit::CLUB); ++s)
        {
            for (int i = 1; i < 14; ++i)
            {
                card c(static_cast<suit>(s), i);
                this->cards[i - 1] = c;
            }
        }
    }

    // Custom methods
    // print out the deck, this could also be done via overloading of operator<<
    void print()
    {
        for (auto c = this->cards.begin(); c != this->cards.end(); ++c)
        {
            if (c != this->cards.begin())
            {
                cout << ", " << *c;
            } else {
                cout << *c;
            }
        }
        cout << endl;
    }

    // Shoufle deck
    void shuffle()
    {
        // Initiallize random numbers.
        srand(time(0));

        // Use random shuffle from STL algorithms
        random_shuffle(this->cards.begin(), this->cards.end());
    }
    // Put the first five cards from cards into hand
    void give_hand(hand &h)
    {
        for (int i = 4; i >= 0; --i)
        { // I do it reverse to get intuitive order of the first card of cards into hand
            h.add(this->cards[i]);
        }
    }

private:
    vector<card> cards;
};


// Simulation of straight flush
float simulate_straight_flush(int n_draws)
{
    int n_hits = 0;
    hand h;
    deck d;

    for (int i = 0; i < n_draws; ++i)
    {
        // Create an empty hand.
        h = hand();

        // shuffle the deck.
        d.shuffle();

        // fill the hand with the first n cards
        d.give_hand(h);

        // This sumulation counts as hit (succes) if the randomly drawn hand is both a flush and a straight.
        n_hits = n_hits + static_cast<int>(h.is_straight() && h.is_flush());
    }

    return static_cast<float>(n_hits) / static_cast<float>(n_draws);
}

int main(){

    int n_simulations;
    float percentage_straight_flush;

    // Get the user input on the number of simulations
    cout << "How many simulations should be drawn?" << endl;
    cin >> n_simulations;

    // Simulate the draws
    percentage_straight_flush = simulate_straight_flush(n_simulations);

    // Give the result out to the user.
    cout << "The percentage of straigt flush was: " << percentage_straight_flush << "." <<  endl;

    return 0;
}