#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, k;
  cin >> n >> k;
  vector<vector<int>> grid(n, vector<int>(n+1));
  for (int y = 1; y < n; y++) {
    for (int x = y+1; x <= n; x++) {
      cin >> grid[y][x];
    }
  }

  vector<vector<int>> gridPs(n+1, vector<int>(n+2));
  for (int y = 1; y < n+1; y++) {
    for (int x = 1; x < n+2; x++) {
      gridPs[y][x] = grid[y-1][x-1] + gridPs[y-1][x] + gridPs[y][x-1] - gridPs[y-1][x-1];
    }
  }
  auto psQuery = [&](int x1, int y1, int x2, int y2) -> int {
    int a = gridPs[y2+1][x2+1];
    int b = gridPs[y1][x2+1];
    int c = gridPs[y2+1][x1];
    int d = gridPs[y1][x1];
    return a - b - c + d;
  };

  vector<vector<pair<int, int>>> maxOverArr(n+1, vector<pair<int, int>>(k, {-1, -1}));
  for (int a = 1; a < n; a++) {
    const int firstK = psQuery(a+1, 1, n, a);
    maxOverArr[a][0] = {firstK, -1};
    for (int b = 1; b < a; b++) {
      for (int c = 1; c < k; c++) {
        int maxOver = maxOverArr[b][c-1].first;
        if (maxOver == -1) continue;
        int newC = psQuery(a+1, b+1, n, a);
        int res = maxOver + newC;
        maxOverArr[a][c] = max(maxOverArr[a][c], {res, b});
      }
    }
  }

  pair<int, int> maxEntry = {-1, -1};
  for (int a = 1; a < n; a++) {
    auto [x, y] = maxOverArr[a][k-1];
    maxEntry = max(maxEntry, {x, a});
  }
  auto [globalMax, aMax] = maxEntry;
  vector<int> ans(k);
  ans[k-1] = aMax;
  for (int ik = k-2, a = aMax; ik >= 0; ik--) {
    a = maxOverArr[a][ik+1].second;
    ans[ik] = a;
  }
  for (int v : ans) cout << v << ' ';

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex0");
  return 0;
}
#endif
