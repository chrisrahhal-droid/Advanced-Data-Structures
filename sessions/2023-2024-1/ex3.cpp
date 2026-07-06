#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int M;
    cin >> M;
    int L, R;
    vector<pair<int, int>> segs;
    while (cin >> L >> R && !(L == 0 && R == 0))
    {
        segs.push_back({L, R});
    }
    int covered = 0;
    vector<pair<int, int>> chosen;
    while (covered < M)
    {
        int bestR = covered;
        int bestIdx = -1;
        for (int i = 0; i < segs.size(); i++)
        {
            if (segs[i].first <= covered && segs[i].second > bestR)
            {
                bestR = segs[i].second;
                bestIdx = i;
            }
        }
        if (bestR == covered)
        {
            cout << "No solution" << endl;
            break;
        }
        covered = bestR;
        chosen.push_back(segs[bestIdx]);
    }
    cout << chosen.size() << endl;
    for (auto x : chosen)
    {
        cout << x.first << " " << x.second << endl;
    }
    return 0;
}
