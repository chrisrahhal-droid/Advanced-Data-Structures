#include <iostream>
#include <vector>
using namespace std;

int N = 10;
vector<int> bit; // 1-indexed: we use slots 1..N

void init()
{
    bit.assign(N + 1, 0); // all zero
}

int lowbit(int i)
{
    return i & (-i); // the lowest set bit = size of i's chunk
}

// add 'delta' at position i (1-indexed). O(log N)
void update(int i, int delta)
{
    while (i <= N)
    {
        bit[i] += delta;
        i += lowbit(i); // jump to the next slot that covers i
    }
}

// prefix sum of positions 1..i. O(log N)
int query(int i)
{
    int sum = 0;
    while (i > 0)
    {
        sum += bit[i];
        i -= lowbit(i); // jump back to before this chunk
    }
    return sum;
}

// sum over the inclusive range [l, r]. O(log N)
int rangeQuery(int l, int r)
{
    return query(r) - query(l - 1);
}

void print()
{
    cout << "bit: ";
    for (int i = 1; i <= N; i++)
        cout << bit[i] << ' ';
    cout << '\n';
}

int main()
{
    init();
    print();

    update(1, 5);
    update(2, 3);
    update(3, 7);
    update(4, 2);
    update(6, 4);
    update(9, 8);
    cout << "after updates: ";
    print();

    cout << "prefix sum 1..4 = " << query(4) << '\n';         // 5+3+7+2 = 17
    cout << "prefix sum 1..10 = " << query(10) << '\n';       // 29
    cout << "range  [3..6]   = " << rangeQuery(3, 6) << '\n'; // 7+2+0+4 = 13

    update(3, 10);                                                              // add 10 at position 3
    cout << "after update(3,+10): range [3..6] = " << rangeQuery(3, 6) << '\n'; // 23
    return 0;
}
