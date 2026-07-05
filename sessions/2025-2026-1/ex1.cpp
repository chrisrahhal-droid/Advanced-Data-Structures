#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
void f(const vector<int> &v)
{
    unordered_map<int, int> freq;
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            freq[v[i] + v[j]]++;
        }
    }
    for (auto s : freq)
    {
        cout << s.first << ":" << s.second << endl;
    }
}
int main()
{
    vector<int> v = {1, 5, 10, 20};
    f(v);
    return 0;
}
// complexity: O(n^(2))