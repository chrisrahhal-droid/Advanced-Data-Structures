#include <iostream>
#include <vector>
using namespace std;

int N = 8;                                // number of leaves (the real array size)
vector<int> a = {5, 3, 7, 2, 0, 4, 0, 8}; // the actual data (positions 0..7)
vector<int> tree;                         // each node = sum of a range of 'a'

// Build the whole tree once. node covers a[lo..hi].
void build(int node, int lo, int hi)
{
    if (lo == hi)
    { // a leaf: covers exactly one element
        tree[node] = a[lo];
        return;
    }
    int mid = (lo + hi) / 2;
    build(2 * node, lo, mid);                         // left child covers left half
    build(2 * node + 1, mid + 1, hi);                 // right child covers right half
    tree[node] = tree[2 * node] + tree[2 * node + 1]; // parent = sum of children
}

// Sum of a[l..r]. node currently covers a[lo..hi].
int query(int node, int lo, int hi, int l, int r)
{
    if (r < lo || hi < l)
        return 0; // this node is fully outside [l..r]
    if (l <= lo && hi <= r)
        return tree[node];   // this node is fully inside  [l..r]
    int mid = (lo + hi) / 2; // partial overlap: ask both children
    return query(2 * node, lo, mid, l, r) + query(2 * node + 1, mid + 1, hi, l, r);
}

// Set a[pos] = val. node currently covers a[lo..hi].
void update(int node, int lo, int hi, int pos, int val)
{
    if (lo == hi)
    { // reached the leaf for 'pos'
        tree[node] = val;
        a[pos] = val;
        return;
    }
    int mid = (lo + hi) / 2;
    if (pos <= mid)
        update(2 * node, lo, mid, pos, val); // go left
    else
        update(2 * node + 1, mid + 1, hi, pos, val);  // go right
    tree[node] = tree[2 * node] + tree[2 * node + 1]; // fix the parent on the way back
}

int main()
{
    tree.assign(4 * N, 0); // 4*N slots is always enough
    build(1, 0, N - 1);    // root is node 1, covers a[0..7]

    cout << "sum [0..7] = " << query(1, 0, N - 1, 0, 7) << '\n'; // 29
    cout << "sum [2..5] = " << query(1, 0, N - 1, 2, 5) << '\n'; // 7+2+0+4 = 13

    update(1, 0, N - 1, 2, 17);                                                 // set a[2] = 17 (was 7, +10)
    cout << "after a[2]=17, sum [2..5] = " << query(1, 0, N - 1, 2, 5) << '\n'; // 23
    return 0;
}
