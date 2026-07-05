#include <iostream>
#include <vector>

using namespace std;

struct WUnionFind
{

private:
    vector<int> id;

public:
    WUnionFind(int N)
    {
        id.resize(N);
        for (int i = 0; i < N; i++)
            id[i] = i;
    }
    int root(int i)
    {
        while (i != id[i])
        {
            i = id[i];
        }
        return i;
    }
    void unite(int a, int b)
    {
        int ra = root(a), rb = root(b);
        if (ra == rb)
            return;
        id[ra] = rb;
    }
    bool connected(int a, int b)
    {
        return root(a) == root(b);
    }
    void print()
    {
        for (int i = 0; i < id.size(); i++)
        {
            cout << id[i] << " ";
        }
        cout << endl;
    }
};

int main()
{

    int N = 10;
    WUnionFind uf = WUnionFind(N);

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
