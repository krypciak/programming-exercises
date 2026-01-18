#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<vector<int>> positions(n+1);
  for (int i = 0; i < n; i++) positions[a[i]].push_back(i);

  int distMin = INT_MAX;
  int distMax = INT_MIN;
  for (int v = 1; v <= n; v++) {
    const int len = (int)positions[v].size();
    if (len >= 2) distMax = max(distMax, positions[v][len-1] - positions[v][0]);
    for (int i = 1; i < len; i++) {
      distMin = min(distMin, positions[v][i]-positions[v][i-1]);
    }
  }
  if (distMin == INT_MAX) distMin = 0;
  if (distMax == INT_MIN) distMax = 0;
  cout << distMin << ' ' << distMax << '\n';
  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
  test("ex0");
  return 0;
}
#endif
