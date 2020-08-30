#include <string>
#include <vector>
#include <sstream>
using namespace std;
string decomp(int n)
{
    vector<int> all_factors(n + 1, 0);
    for (int num = 2; num <= n; ++num)
    {
        int this_num = num;
        int fac = 2;
        while (this_num > 1)
        {
            if (this_num % fac == 0)
            {
                all_factors[fac] += 1;
                this_num = this_num / fac;
            }
            else
            {
                fac += 1;
            }
        }
    }

    stringstream ss;
    for (int prime_fac = 2; prime_fac <= n; prime_fac++)
    {
        if (all_factors[prime_fac] == 1)
        {
            ss << " * " << prime_fac;
        }
        else
        {
            if (all_factors[prime_fac] > 1)
            {
                ss << " * " << prime_fac << "^" << all_factors[prime_fac];
            }
        }
    }
    return ss.str().erase(0, 3);
}
