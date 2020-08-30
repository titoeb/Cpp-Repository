#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> deleteNth(vector<int> arr, int n)
{
    vector<int> output;
    unordered_map<int, int> umap;

    for (auto elem : arr)
    {
        if (umap.find(elem) == umap.end())
        {
            umap[elem] = 1;
        }
        else
        {
            umap[elem] += 1;
        }

        if (umap[elem] <= n)
            output.push_back(elem);
    }

    // Revert vector
    reverse(output.begin(), output.end());
    return output;
}

int main()
{
    return 0;
}