#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> G(n+1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  vector<bool> visited(n+1, false);
  visited[1] = true;
  vector<int> TV{1};
  vector<int> dists(n+1, -1);
  dists[1] = 0;
  for (int dist = 1; TV.size(); dist++) {
    vector<int> nTV;
    for (int v : TV) {
      for (int u : G[v]) {
        if (visited[u]) continue;
        visited[u] = true;
        nTV.push_back(u);
        dists[u] = dist;
      }
    }
    TV = nTV;
  }
  for (int i = 1; i <= n; i++) cout << dists[i] << " ";

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
