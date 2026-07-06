#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

pair<int, int> f(const vector<int> &v, int W)
{
    unordered_set<int> s;
    for (int x : v)
    {
        int needed = W - x;
        if (s.find(needed) == s.end())
        {
            s.insert(x);
        }
        else
        {
            return {x, needed};
        }
    }
    return {};
}

int main(){
    vector<int> v = {1, 5, 10};
    pair<int,int> res = f(v, 6);
    cout<<"{"<<res.first<<","<<res.second<<"}"<<endl;
    return 0;
}
// complexity: O(n)