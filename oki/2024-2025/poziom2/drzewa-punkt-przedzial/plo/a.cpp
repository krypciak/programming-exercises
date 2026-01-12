#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  vector<int> t;
  int n;

  int comb(int a, int b) {
    return a +  b;
  }

  Seg(int n) : n(n) {
    t = vector<int>(n*2, 0);
  }

  void set(int i, int v) {
    for (t[i+=n] = v; i > 1; i >>= 1) t[i>>1] = comb(t[i], t[i^1]);
  }

  int query(int l, int r) {
    int res = 0;
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

  Seg seg(n);

  while (m--) {
    int t;
    cin >> t;
    if (t == 1) {
      int i;
      cin >> i;
      i--;
      seg.set(i, seg.t[i+n]+1);
    } else if (t == 2) {
      int l, r;
      cin >> l >> r;
      int res = seg.query(l-1, r);
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
