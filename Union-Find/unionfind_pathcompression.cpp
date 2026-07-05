#include <iostream>
#include <vector>
using namespace std;

// Demo: how PATH COMPRESSION flattens a tree during find().
// We use PLAIN quick-union (no weighting) so we can build a deliberately
// tall chain and watch find() collapse it. Two flavors are shown.

int N = 7;
vector<int> id;

void init()
{
    id.resize(N);
    for (int i = 0; i < N; i++)
        id[i] = i;
}

// No compression: just walk to the root, change nothing.
int findPlain(int i)
{
    while (i != id[i])
        i = id[i];
    return i;
}

// Full (two-pass) path compression: every node on the path -> root.
int findFull(int i)
{
    int r = i;
    while (r != id[r]) // pass 1: locate the root
        r = id[r];
    while (i != r)
    { // pass 2: re-hang every node directly under r
        int next = id[i];
        id[i] = r;
        i = next;
    }
    return r;
}

// Path halving (one pass): every node -> its grandparent.
int findHalving(int i)
{
    while (i != id[i])
    {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

void print(const char *label)
{
    cout << label << " id: ";
    for (int i = 0; i < N; i++)
        cout << id[i] << ' ';
    cout << '\n';
}

// Build a worst-case chain by hand: 0<-1<-2<-3<-4<-5<-6
// (id[6]=5, id[5]=4, ... id[1]=0, id[0]=0). Root is 0, depth of 6 is 6.
void buildChain()
{
    init();
    for (int i = 1; i < N; i++)
        id[i] = i - 1;
}

int main()
{
    buildChain();
    print("chain        ");
    cout << "findPlain(6) = " << findPlain(6) << "  (root, tree unchanged)\n";
    print("after plain  ");
    cout << '\n';

    buildChain();
    print("chain        ");
    cout << "findHalving(6) = " << findHalving(6) << "\n";
    print("after halving"); // path roughly halved, not fully flat
    cout << '\n';

    buildChain();
    print("chain        ");
    cout << "findFull(6) = " << findFull(6) << "\n";
    print("after full   "); // every node now points straight at root 0
    return 0;
}
