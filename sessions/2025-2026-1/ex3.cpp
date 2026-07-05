#include <iostream>
#include <vector>
using namespace std;
void f(const vector<int> &v, int W)
{
    int total = 0;
    for (auto x : v)
    {
        total += x;
    }
    vector<bool> dp(total + 1, false);
    dp[0] = true;
    for (int x : v)
    {
        for (int s = total; s >= x; s--)
        {
            if (dp[s - x])
            {
                dp[s] = true;
            }
            // dp[s] = dp[s] | dp[s - x];
        }
    }
    for (int s = W; s <= total; s++)
    {
        if (dp[s])
        {
            cout << s << endl;
            break;
        }
    }
}
int main()
{
    vector<int> v = {2, 4, 3, 0};
    f(v, 3);
    return 0;
}

// complexity: O(n X total)
