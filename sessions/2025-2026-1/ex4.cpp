#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

string f(string t)
{
    int n = t.size();
    unordered_map<string, int> subs;
    string longest = "";
    for (int len = 1; len <= n; len++)
    {
        for (int i = 0; i + len <= n; i++)
        {
            string sub = t.substr(i, len);
            if (++subs[sub] == 2)
            {
                longest = sub;
            };
        }
    }
    return longest;
}

int main()
{
    cout << f("banana") << endl;
    return 0;
}
// complexity: O(n^(3))