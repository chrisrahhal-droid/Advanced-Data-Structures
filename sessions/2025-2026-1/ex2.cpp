#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

void f(const vector<int> &v, int K, int x)
{
    int n = v.size();
    vector<int> bestSub;
    int bestDiff = INT_MAX;
    for (int i = 0; i < (1 << n); i++)
    {
        vector<int> subset;
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                subset.push_back(v[j]);
                sum += v[j];
            }
        }
        if (subset.size() == K && abs(sum - x) <= bestDiff)
        {
            bestSub = subset;
            bestDiff = abs(sum - x);
        }
    }
    cout << "{";
    for (int i = 0; i < bestSub.size(); i++)
    {
        cout << bestSub[i] << " ";
    }
    cout << "}" << endl;
}

int main()
{
    vector<int> v = {0, 1, 2};
    f(v, 2, 3);
    return 0;
}

// complexity: O(2^(n) . n)