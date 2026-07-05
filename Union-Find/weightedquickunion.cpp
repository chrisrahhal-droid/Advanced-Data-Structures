#include <iostream>
#include <vector>
using namespace std;

class WUnionFind
{
private:
    vector<int> id; // id[i] = parent of i (a forest of trees)
    vector<int> sz; // sz[i] = size of tree rooted at i (only valid at roots)
public:
    WUnionFind(int N)
    {
        id.resize(N);
        sz.resize(N);
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
            sz[i] = 1;
        } // each object: own root, size 1
    }

    int root(int i)
    {
        while (i != id[i])
        {
            id[i] = id[id[i]]; // path compression: point i at its grandparent
            i = id[i];
        }
        return i; // O(log N) thanks to weighting
    }

    bool connected(int a, int b)
    {
        return root(a) == root(b);
    }

    void unite(int a, int b)
    {
        int ra = root(a), rb = root(b);
        if (ra == rb)
            return; // already same tree
        if (sz[ra] < sz[rb])
        { // hang the smaller tree under the larger root
            id[ra] = rb;
            sz[rb] += sz[ra];
        }
        else
        {
            id[rb] = ra;
            sz[ra] += sz[rb];
        }
    }

    void print()
    {
        cout << "id: ";
        for (int x : id)
            cout << x << ' ';
        cout << '\n';
    }
};
int main()
{
    int N = 10;
    WUnionFind uf = WUnionFind(N);
    uf.print();

    uf.unite(4, 3);
    cout << "after union(4,3): ";
    uf.print();
    uf.unite(3, 8);
    cout << "after union(3,8): ";
    uf.print();
    uf.unite(6, 5);
    cout << "after union(6,5): ";
    uf.print();
    uf.unite(9, 4);
    cout << "after union(9,4): ";
    uf.print();

    cout << "connected(8,9)? " << (uf.connected(8, 9) ? "yes" : "no") << '\n';
    cout << "connected(0,7)? " << (uf.connected(0, 7) ? "yes" : "no") << '\n';
    return 0;
}
