#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
  int end;
  int depth;
  vector<int> C;
};
int n;
vector<vector<int>> OG;
vector<Node> G;

struct Seg {
  vector<int> t;
  int n;

  Seg(int n) : n(n) { t = vector<int>(n * 2); }

  void add(int l, int r) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        t[l++] += 1;
      if (r & 1)
        t[--r] += 1;
    }
  }

  int query(int i) {
    int res = 0;
    for (i += n; i > 0; i >>= 1)
      res += t[i];
    return res;
  }
};

int newV;
vector<int> transTable;
int dfs(int v, int depth) {
  int nv = newV;
  int end = nv;
  transTable[v] = nv;
  for (int u : OG[v]) {
    int nu = ++newV;
    G[nv].C.push_back(newV);
    end = max({end, nu, dfs(u, depth + 1)});
  }
  G[nv].depth = depth;
  G[nv].end = end;
  return end;
}

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  cin >> n;
  OG = vector<vector<int>>(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    OG[a].push_back(b);
  }
  G = vector<Node>(n + 1);
  transTable = vector<int>(n + 1, -1);
  newV = 1;
  dfs(1, 0);

  Seg seg(n + 1);
  int m;
  cin >> m;
  m += n - 1;
  while (m--) {
    char t;
    cin >> t;
    if (t == 'A') {
      int a, b;
      cin >> a >> b;
      assert(b > a);
      a = transTable[a];
      b = transTable[b];

      int end = G[b].end;
      seg.add(b, end + 1);
      // cout << '\n';
    } else if (t == 'W') {
      int to;
      cin >> to;
      to = transTable[to];
      int res = G[to].depth - seg.query(to);
      cout << res << '\n';
    }
  }

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex1");
  test("ex0");
  return 0;
}
#endif
