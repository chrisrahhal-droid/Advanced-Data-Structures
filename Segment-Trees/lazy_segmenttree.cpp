#include <iostream>
#include <vector>
using namespace std;

// Segment tree with LAZY PROPAGATION.
// Supports BOTH operations in O(log n):
//   - range update: add 'val' to every element in [l..r]
//   - range query : sum of every element in [l..r]
//
// tree[node] = sum of node's segment, INCLUDING any add already applied to it.
// lazy[node] = a pending add that node has applied to its own sum, but has NOT
//              yet pushed down to its children. "Everyone below me owes this."

int N = 8;
vector<long long> a = {5, 3, 7, 2, 0, 4, 0, 8};
vector<long long> tree;
vector<long long> lazy;

void build(int node, int lo, int hi)
{
    if (lo == hi)
    {
        tree[node] = a[lo];
        return;
    }
    int mid = (lo + hi) / 2;
    build(2 * node, lo, mid);
    build(2 * node + 1, mid + 1, hi);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Apply "+val to every element" to a node covering [lo..hi].
// Sum grows by val for EACH of the (hi-lo+1) elements; tag accumulates.
void apply(int node, int lo, int hi, long long val)
{
    tree[node] += (long long)(hi - lo + 1) * val;
    lazy[node] += val;
}

// Hand this node's pending add down to its two children, then clear it.
void pushDown(int node, int lo, int hi)
{
    if (lazy[node] != 0)
    {
        int mid = (lo + hi) / 2;
        apply(2 * node, lo, mid, lazy[node]);
        apply(2 * node + 1, mid + 1, hi, lazy[node]);
        lazy[node] = 0;
    }
}

// Add 'val' to every element in [l..r]. node currently covers [lo..hi].
void update(int node, int lo, int hi, int l, int r, long long val)
{
    if (r < lo || hi < l)
        return; // fully outside: nothing to do
    if (l <= lo && hi <= r)
    {                            // fully inside: update + park a lazy tag,
        apply(node, lo, hi, val); // and DON'T recurse into children
        return;
    }
    pushDown(node, lo, hi);      // partial overlap: settle debts before splitting
    int mid = (lo + hi) / 2;
    update(2 * node, lo, mid, l, r, val);
    update(2 * node + 1, mid + 1, hi, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1]; // rebuild from fixed children
}

// Sum of a[l..r]. node currently covers [lo..hi].
long long query(int node, int lo, int hi, int l, int r)
{
    if (r < lo || hi < l)
        return 0; // fully outside
    if (l <= lo && hi <= r)
        return tree[node]; // fully inside: answer already correct
    pushDown(node, lo, hi); // partial: push pending add before descending
    int mid = (lo + hi) / 2;
    return query(2 * node, lo, mid, l, r) + query(2 * node + 1, mid + 1, hi, l, r);
}

int main()
{
    tree.assign(4 * N, 0);
    lazy.assign(4 * N, 0);
    build(1, 0, N - 1);

    cout << "sum [0..7] = " << query(1, 0, N - 1, 0, 7) << '\n'; // 29
    cout << "sum [2..5] = " << query(1, 0, N - 1, 2, 5) << '\n'; // 13

    update(1, 0, N - 1, 2, 5, 10); // add +10 to every element in [2..5]
    cout << "\nafter range-add +10 on [2..5]:\n";
    cout << "sum [2..5] = " << query(1, 0, N - 1, 2, 5) << '\n'; // 13 + 4*10 = 53
    cout << "sum [0..7] = " << query(1, 0, N - 1, 0, 7) << '\n'; // 29 + 40   = 69
    cout << "sum [4..4] = " << query(1, 0, N - 1, 4, 4) << '\n'; // 0  + 10   = 10
    cout << "sum [0..1] = " << query(1, 0, N - 1, 0, 1) << '\n'; // untouched = 8
    return 0;
}
