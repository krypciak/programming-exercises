#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  vector<ll> t;
  int n;

  Seg(int n) : n(n) {
    t = vector<ll>(n*2);
  }

  void add(int l, int r, ll v) {
    for (l += n, r += n; r > l; l >>= 1, r >>= 1) {
      if (l&1) t[l++] += v;
      if (r&1) t[--r] += v;
    }
  }

  ll query(int p) {
    ll res = 0;
    for (p += n; p > 0; p >>= 1) res += t[p];
    return res;
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;

  Seg seg(n);

  while (m--) {
    int t;
    cin >> t;
    if (t == 1) {
      // malowanie
      int l, r;
      cin >> l >> r;
      l--;
      int v = 1;
      seg.add(l, r, v);
    } else if (t == 2) {
      // liczenie warstw
      int i;
      cin >> i;
      i--;
      ll res = seg.query(i);
      cout << res << '\n';
    }
  }

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
