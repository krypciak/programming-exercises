#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

using namespace std;

vector<vector<int>> G;
vector<int> result;

void dfs(int upo, int p, bool even) {
  if (even)
    result.push_back(upo);

  for (int u : G[upo]) {
    if (u != p) dfs(u, upo, !even);
  }
  if (!even)
    result.push_back(upo);
}

int run(istream &cin, ostream &cout) {
  int n;
  cin >> n;

  G.assign(n + 1, {});
  result.clear();
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  int root = 1;
  dfs(root, 0, true);
  for (int x : result) {
    cout << x << '\n';
  }

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex0");
  test("ex1");
  test("ex2");
  return 0;
}
#endif
