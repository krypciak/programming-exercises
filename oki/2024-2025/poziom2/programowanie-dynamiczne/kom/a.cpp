#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> g(n, vector<int>(m));
  for (int y = 0; y < n; y++) for (int x = 0; x < m; x++) cin >> g[y][x];

  auto canReachEnd = [&](int M) {
    using tp = tuple<int, int>;
    vector<tp> toVisit;
    toVisit.push_back({0, 0});
    vector<vector<int>> maxEnergyGrid(n, vector<int>(m, INT_MIN));
    maxEnergyGrid[0][0] = k;
    while (!toVisit.empty()) {
      vector<tp> nextToVisit;
      nextToVisit.reserve(toVisit.size()*2);
      for (auto [x, y] : toVisit) {
        if (x == m-1 and y == n-1) return true;
        int e = maxEnergyGrid[y][x];
        int v = g[y][x];
        for (auto [nx, ny] : {pair<int, int>{x+1, y}, {x, y+1}}) {
          if (nx >= m or ny >= n) continue;
          int nv = g[ny][nx];
          if (nv == -1) continue;
          int hdiff = nv-v;
          if (hdiff > M) continue;
          int ne = nv == 0 ? k : e-(hdiff>0);
          if (ne < 0) continue;

          if (maxEnergyGrid[ny][nx] == INT_MIN) nextToVisit.push_back({nx, ny});
          maxEnergyGrid[ny][nx] = max(maxEnergyGrid[ny][nx], ne);
        }
      }
      toVisit = nextToVisit;
    }
    return false;
  };

  int maxK = 1e4;
  int lm = 0, rm = maxK;
  while (lm < rm) {
    int mm = (lm+rm)/2;
    // print("lm: {}, rm: {}, mm: {}\n", lm, rm, mm);
    if (canReachEnd(mm)) {
      rm = mm;
    } else {
      lm = mm+1;
    }
  }
  if (lm == maxK) cout << "NIE" << '\n';
  else cout << lm << '\n';
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
