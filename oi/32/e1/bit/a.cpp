#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ll;

int n, m, k;
int N, M;

struct Ve {
  int to;
};
vector<Ve> *bitEdge;
vector<Ve> *bajEdge;

void constructTree() {
  N = n - 1;
  bitEdge = new vector<Ve>[n];
  for (int i = 0; i < N; i++) {
    int from, to;
    cin >> from >> to;
    from--;
    to--;
    bitEdge[from].push_back({to});
    bitEdge[to].push_back({from});
  }

  cout << endl;
  M = m - 1;
  bajEdge = new vector<Ve>[m];
  for (int i = 0; i < M; i++) {
    int from, to;
    cin >> from >> to;
    from--;
    to--;
    bajEdge[from].push_back({to});
    bajEdge[to].push_back({from});
  }
}

ll dfs(int fromBit, int toBit, int fromBaj, int toBaj) {
  ll sum = 0;

  if (bajEdge[toBaj].size() < bitEdge[toBit].size())
    return 0;

  for (Ve neigh : bajEdge[toBaj]) {
  }

  return sum;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m >> k;
  constructTree();

  ll sum = 0;
  for (int i = 0; i < m; i++) {
    ll res = dfs(-1, i, -1, 0);
    sum = (sum + (res % k)) % k;
  }

  cout << sum << endl;
  return 0;
}
