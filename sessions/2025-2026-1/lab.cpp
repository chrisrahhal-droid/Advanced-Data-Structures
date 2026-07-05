#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct WUnionFind
{
private:
    vector<int> id;
    vector<int> sz;
    vector<int> v;

public:
    WUnionFind(const vector<int> &v, int n) : v(v)
    {
        id.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++)
        {
            id[i] = i;
        }
    }
    int find(int i)
    {
        while (i != id[i])
        {
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }
    bool connected(int a, int b)
    {
        return find(a) == find(b);
    }
    void unite(int a, int b)
    {
        int ra = find(a), rb = find(b);
        if (ra == rb)
            return;
        if (sz[ra] <= sz[rb])
        {
            id[ra] = rb;
            sz[rb] += sz[ra];
        }
        else
        {
            id[rb] = ra;
            sz[ra] += sz[rb];
        }
    }
    void uniteif(int m, int K)
    {
        for (int k = 0; k < m; k++)
        {
            int i = rand() % v.size();
            int j = rand() % v.size();
            if (i == j)
                continue;
            if (abs(v[i] - v[j]) <= K)
            {
                unite(i, j);
            }
        }
    }
    int getValue(int i)
    {
        return v[i];
    }
};

int main()
{
    srand(time(0));
    int m, n, K;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    WUnionFind wuf = WUnionFind(v, n);

    cin >> m;
    cin >> K;
    wuf.uniteif(m, K);
    unordered_map<int, vector<int>>
        groups;

    for (int i = 0; i < n; i++)
    {
        groups[wuf.find(i)].push_back(wuf.getValue(i));
    }

    for (auto &g : groups)
    {
        cout << "root->" << g.first << endl;
        for (auto m : g.second)
        {
            cout << m << " ";
        }
        cout << endl;
    }
    return 0;
}

// complexity: O(n+m)