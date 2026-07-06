#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void f(const vector<int> &S, int W, int n)
{
    int size = S.size();
    vector<vector<int>> subsets;
    for (int i = 0; i < (1 << size); i++)
    {
        vector<int> subset;
        int sum = 0;
        for (int j = 0; j < size; j++)
        {
            if (i & (1 << j))
            {
                subset.push_back(S[j]);
                sum += S[j];
            }
        }
        if (sum <= W && subset.size() == n)
        {
            subsets.push_back(subset);
        }
    }
}
//complexity: O(2^(n). n)