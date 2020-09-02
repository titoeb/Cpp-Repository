#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Fracts
{

public:
    static string convertFrac(vector<vector<unsigned long long>> &lst);
};

string Fracts::convertFrac(vector<vector<unsigned long long>> &lst)
{
    long long gcd = gcd_vec(lst);
}

template <class T>
T gcd(T a, T b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        if (b > a)
        {
            return gcd(b, a);
        }
        else
        {
            gcd(b, a % b);
        }
    }
}

template <class T>
T gcd_vec(vector<T> input)
{
}