#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);
    
  int n, m;
  cin >> n >> m;
  vector<vector<int>> graph(n);
  
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  auto bfs = [&](int start) -> pair<int, int> {
    vector<int> dist(n, -1);

    vector<int> toVisit{start};
    dist[start] = 0;
    int farthest = start;
    for (int depth = 1; !toVisit.empty(); depth++) {
      vector<int> nextToVisit;
      nextToVisit.reserve(toVisit.size());
      for (int v : toVisit) {
        for (int u : graph[v]) {
          if (dist[u] != -1) continue;
          dist[u] = depth;
          nextToVisit.push_back(u);
        }
      }
      if (!nextToVisit.empty()) farthest = nextToVisit[0];
      toVisit = move(nextToVisit);
    }
    return {farthest, dist[farthest]};
  };
  
  auto [farthestNode, _] = bfs(0);
  auto [__, diameter] = bfs(farthestNode);
  
  int res = min(n, (min(diameter, m) + m)/2 + 1);
  cout << res << '\n';
  
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
