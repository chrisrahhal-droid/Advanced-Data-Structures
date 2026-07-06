#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> f(const vector<int> &v, int W)
{
    int n = v.size();
    vector<vector<int>>
        dp(n + 1, vector<int>(W + 1, 0));
    for (int r = 1; r <= n; r++)
    {
        for (int c = 0; c <= W; c++)
        {
            if (v[r - 1] <= c)
            {
                dp[r][c] = max(dp[r - 1][c], dp[r - 1][c - v[r - 1]] + v[r - 1]);
            }
            else
            {
                dp[r][c] = dp[r - 1][c];
            }
        }
    }
    vector<int> chosen;
    int c = W;
    for (int r = n; r >= 1; r--)
    {
        if (dp[r][c] != dp[r - 1][c])
        {
            chosen.push_back(r - 1);
            c -= v[r - 1];
        }
    }
    return chosen;
}

int main()
{
    vector<int> rods = {45, 25, 20, 20, 20, 35};
    vector<int> chosen = f(rods, 89);
    for (int x : chosen)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}