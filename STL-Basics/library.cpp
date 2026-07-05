#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

typedef pair<int, string> is;

// the data is sorted by name (.second), so EVERY search must use this same rule
auto byName = [](const is &a, const is &b)
{ return a.second < b.second; };

int main()
{
  vector<is> v;
  ifstream fin("textfiles/in_ex02.txt");
  is p;
  while (fin >> p.first >> p.second)
    v.push_back(p);

  sort(v.begin(), v.end(), byName);

  // the key must be the SAME type as the elements; only .second matters for searching
  is key = {0, "grace"};

  // first element whose name >= "grace"
  auto it = lower_bound(v.begin(), v.end(), key, byName);
  if (it != v.end() && it->second == key.second)
    cout << "found " << it->second << " with score " << it->first << '\n';
  else
    cout << key.second << " not found\n";

  // first element whose name > "grace"
  auto hi = upper_bound(v.begin(), v.end(), key, byName);

  bool exists = binary_search(v.begin(), v.end(), key, byName);
  cout << "binary_search: " << (exists ? "yes" : "no") << '\n';

  auto [lo, up] = equal_range(v.begin(), v.end(), key, byName);
  cout << "equal_range count: " << distance(lo, up) << '\n';

  cout << "index of lower_bound result: " << distance(v.begin(), it) << '\n';

  cout << "is_sorted (by name): " << is_sorted(v.begin(), v.end(), byName) << '\n';

  // find/count need a full element match (both score AND name), or a predicate
  long c = count_if(v.begin(), v.end(),
                    [&](const is &e)
                    { return e.second == key.second; });
  cout << "count of name '" << key.second << "': " << c << '\n';

  // min/max here compare by score (.first) because that's pair's default order
  auto min_it = min_element(v.begin(), v.end());
  auto max_it = max_element(v.begin(), v.end());
  cout << "lowest score:  " << min_it->second << " (" << min_it->first << ")\n";
  cout << "highest score: " << max_it->second << " (" << max_it->first << ")\n";

  return 0;
}
