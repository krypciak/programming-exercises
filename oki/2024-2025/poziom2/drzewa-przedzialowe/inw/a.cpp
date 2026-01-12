#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  vector<int> t;
  int n;

  Seg(int n) : n(n) {
    t = vector<int>(n*2, 0);
  }

  int at(int i) {
    return t[i+n];
  }

  void set(int i, int v) {
    for (t[i+=n] = v; i > 1; i>>=1) t[i>>1] = t[i] + t[i^1];
  }

  int query(int l, int r) {
    int res = 0;
    for (l+=n, r+=n; r > l; l>>=1, r>>=1) {
      if (l&1) res += t[l++];
      if (r&1) res += t[--r];
    }
    return res;
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<pair<int, int>> V(n);
  for (int i = 0; i< n; i++) {
    int v;
    cin >> v;
    V[i] = {v, i};
  }

  sort(begin(V), end(V));
  for (auto [v, _] : V) cout << v << ' ';
  cout << '\n';

  ll res = 0;
  Seg seg(n);
  for (auto [v, i] : V) {
    res += seg.query(i+1, n);
    seg.set(i, 1);
  }
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
