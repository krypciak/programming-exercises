#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  vector<int> t;
  int n;

  int comb(int a, int b) {
    return min(a, b);
  }

  Seg(const vector<int> &v) {
    n = v.size();
    t = vector<int>(n*2);

    for (int i = n; i < n*2; i++) t[i] = v[i-n];
    for (int i = n-1; i > 0; i--) t[i] = comb(t[i<<1], t[i<<1|1]);
  }

  void set(int i, int v) {
    for (t[i+=n] = v; i > 1; i >>= 1) t[i>>1] = comb(t[i], t[i^1]);
  }

  int query(int l, int r) {
    int res = +1e9;
    for (l+=n, r+=n; r > l; l>>=1, r>>=1) {
      if (l&1) res = comb(res, t[l++]);
      if (r&1) res = comb(res, t[--r]);
    }
    return res;
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  Seg seg(v);

  while (m--) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 1) {
      seg.set(a-1, b);
    } else {
      int res = seg.query(a-1, b);
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
  test("ex1");
  return 0;
}
#endif
