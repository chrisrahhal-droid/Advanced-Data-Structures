#include <iostream>
#include <vector>
using namespace std;

// RMQ segment tree (chapter 2 version).
// KEY IDEA: every node stores the INDEX of the minimum element in its range,
// not the value. Compare values (A[..]) to decide, but store/return indices.

typedef vector<int> vi;

class SegmentTree
{
private:
    vi st, A; // st = the tree (heap-style array), A = a local copy of the data
    int n;

    int left(int p) { return 2 * p; }      // children of node p, heap indexing
    int right(int p) { return 2 * p + 1; } // (root is node 1, not 0)

    // Build node p, which covers A[L..R]. O(n).
    void build(int p, int L, int R)
    {
        if (L == R)
        {
            st[p] = L; // a leaf covers one element: the min is at index L
            return;
        }
        int mid = (L + R) / 2;
        build(left(p), L, mid);      // left child covers [L, mid]
        build(right(p), mid + 1, R); // right child covers [mid+1, R]
        int p1 = st[left(p)], p2 = st[right(p)];
        st[p] = (A[p1] <= A[p2]) ? p1 : p2; // store index of the smaller value
    }

    // Index of the min over A[i..j]. node p currently covers A[L..R]. O(log n).
    int rmq(int p, int L, int R, int i, int j)
    {
        if (i > R || j < L)
            return -1; // case 1: this node is fully OUTSIDE [i..j]
        if (L >= i && R <= j)
            return st[p]; // case 2: this node is fully INSIDE  [i..j]
        // case 3: partial overlap -> ask both children
        int mid = (L + R) / 2;
        int p1 = rmq(left(p), L, mid, i, j);
        int p2 = rmq(right(p), mid + 1, R, i, j);
        if (p1 == -1)
            return p2; // left side had nothing in range
        if (p2 == -1)
            return p1; // right side had nothing in range
        return (A[p1] <= A[p2]) ? p1 : p2; // combine, same rule as build
    }

    // Set A[idx] = val and fix the path back up to the root. O(log n).
    void update(int p, int L, int R, int idx, int val)
    {
        if (idx > R || idx < L)
            return; // idx not in this node's range
        if (L == R)
        {              // reached the leaf for idx
            A[idx] = val;
            return;
        }
        int mid = (L + R) / 2;
        update(left(p), L, mid, idx, val);
        update(right(p), mid + 1, R, idx, val);
        int p1 = st[left(p)], p2 = st[right(p)];
        st[p] = (A[p1] <= A[p2]) ? p1 : p2; // recompute this node on the way up
    }

public:
    SegmentTree(const vi &_A)
    {
        A = _A;
        n = (int)A.size();
        st.assign(4 * n, 0); // 4*n slots is always enough
        build(1, 0, n - 1);  // root is node 1, covers A[0..n-1]
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); } // index of min in [i..j]
    void update(int idx, int val) { update(1, 0, n - 1, idx, val); }
    int valueAt(int idx) { return A[idx]; }
};

int main()
{
    vi A = {18, 17, 13, 19, 15, 11, 20};
    SegmentTree st(A);

    int idx = st.rmq(1, 3);
    cout << "RMQ(1,3) -> index " << idx << ", value " << st.valueAt(idx) << '\n'; // index 2, value 13

    idx = st.rmq(4, 6);
    cout << "RMQ(4,6) -> index " << idx << ", value " << st.valueAt(idx) << '\n'; // index 5, value 11

    idx = st.rmq(0, 6);
    cout << "RMQ(0,6) -> index " << idx << ", value " << st.valueAt(idx) << '\n'; // index 5, value 11

    st.update(5, 99); // A[5] = 11 -> 99, so the old global min disappears
    idx = st.rmq(0, 6);
    cout << "after A[5]=99, RMQ(0,6) -> index " << idx
         << ", value " << st.valueAt(idx) << '\n'; // index 2, value 13
    return 0;
}
