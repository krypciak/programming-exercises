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

  ll out = 0;
  vector<bool> visited(n+1, false);
  visited[0] = true;
  vector<int> TV{0};
  for (int dist = 1; TV.size(); dist++) {
    vector<int> nTV;
    for (int v : TV) {
      for (int u : G[v]) {
        if (visited[u]) continue;
        visited[u] = true;
        nTV.push_back(u);
        out += dist*2;
      }
    }
    TV = nTV;
  }
  cout << out << '\n';

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
