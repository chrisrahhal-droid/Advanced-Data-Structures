#include <iostream>
#include <vector>
using namespace std;

class QuickFind
{
private:
    vector<int> id;

public:
    QuickFind(int N)
    {
        id.resize(N);
        for (int i = 0; i < N; i++)
            id[i] = i; // each object is its own group
    }

    bool connected(int a, int b)
    {
        return id[a] == id[b]; // same label => connected. O(1)
    }

    void unite(int a, int b)
    {
        int oldId = id[a], newId = id[b];
        if (oldId == newId)
            return;                         // already same group
        for (int i = 0; i < id.size(); i++) // O(N): relabel the whole group
            if (id[i] == oldId)
                id[i] = newId;
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
    QuickFind qf = QuickFind(N);
    qf.print();

    qf.unite(4, 3);
    cout << "after union(4,3): ";
    qf.print();
    qf.unite(3, 8);
    cout << "after union(3,8): ";
    qf.print();
    qf.unite(6, 5);
    cout << "after union(6,5): ";
    qf.print();
    qf.unite(9, 4);
    cout << "after union(9,4): ";
    qf.print();

    cout << "connected(8,9)? " << (qf.connected(8, 9) ? "yes" : "no") << '\n';
    cout << "connected(0,7)? " << (qf.connected(0, 7) ? "yes" : "no") << '\n';
    return 0;
}
