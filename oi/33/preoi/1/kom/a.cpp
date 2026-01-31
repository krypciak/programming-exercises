#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  ull k;
  cin >> n >> m >> k;
  vector<array<int, 2>> graph(n+1);
  for (int i = 1; i <= n; i++) {
    int l, r;
    cin >> l >> r;
    graph[i] = {l, r};
  }
  vector<char> seq(m);
  for (int i = 0; i < m; i++) {
    char c;
    cin >> c;
    seq[i] = c == 'P';
  }

  const int MAX_LOG = 31;
  array<vector<int>, MAX_LOG> jp;
  jp.fill(vector<int>(n+1));
  for (int i = 1; i <= n; i++) {
    int at = i;
    for (char dir : seq) {
      at = graph[at][dir];
    }
    jp[0][i] = at;
  }

  int maxKLog = bit_width(k);
  for (int j = 1; j < maxKLog; j++) {
    for (int i = 1; i <= n; i++) {
      jp[j][i] = jp[j-1][jp[j-1][i]]; 
    }
  }
  int at = 1;
  for (int j = maxKLog; j >= 0; j--) {
    if ((k & (1 << j)) == 0) continue;
    at = jp[j][at];
  }
  cout << at << '\n';

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
  test("kom0a");
  test("kom0b");
  test("kom0c");
  test("kom0d");
  return 0;
}
#endif
