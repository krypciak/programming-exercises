#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);

  while (true) {
    int n, m;
    cin >> n >> m;
    if (n == 0 and m == 0)
      break;
    int N = n + 1;

    vector<vector<int>> G(N);
    vector<vector<int>> RG(N);
    for (int i = 0; i < m; i++) {
      int f, t;
      cin >> f >> t;
      G[f].push_back(t);
      RG[t].push_back(f);
    }
    queue<int> zeros;
    vector<int> deg(N, 0);
    for (int i = 1; i < N; i++) {
      deg[i] = RG[i].size();
      if (deg[i] == 0)
        zeros.push(i);
    }

    while (zeros.size()) {
      int v = zeros.front();
      zeros.pop();
      cout << v << ' ';
      for (auto u : G[v])
        if (--deg[u] == 0)
          zeros.push(u);
    }
    cout << endl;
  }

  return 0;
}
