#include <vector>
#include <iostream>
using namespace std;

int find_even_index(const vector<int> numbers)
{
    int sum_left = 0;
    int sum_right = 0;

    for (auto elem : numbers)
        sum_right += elem;

    for (int idx = 0; idx < numbers.size(); idx++)
    {
        sum_right -= numbers[idx];
        cout << "idx: " << idx << " sum_left: " << sum_left << " sum_right: " << sum_right << endl;

        if (sum_left == sum_right)
            return idx;

        sum_left += numbers[idx];
    }

    return -1;
}

int main()
{
    cout << find_even_index({1, 2, 3, 4, 3, 2, 1}) << endl;
}