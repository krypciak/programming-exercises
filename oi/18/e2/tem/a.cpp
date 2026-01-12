#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  vector<int> t;
  int n;

  int comb(const int &a, const int &b) { return max(a, b); }

  Seg(const vector<int> v) {
    n = v.size();
    t = vector<int>(n*2, -1e9);

    for (int i = n; i < n*2; i++) t[i] = v[i-n];
    for (int i = n - 1; i > 0; i--) {
      t[i] = comb(t[i<<1], t[i<<1|1]);
    }
  }
  int query(int l, int r) {
    int res = -1e9;
    for (l+=n, r+=n; r > l; r>>=1, l>>=1) {
      if (l&1) res = comb(res, t[l++]);
      if (r&1) res = comb(res, t[--r]);
    }
    return res;
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

  Seg seg(x);

  int out = 0;

  int frontI = 0;
  int cmin = -1e9;
  for (int i = 0; i < n; i++) {
    if (frontI != i) {
      while (frontI < i and cmin > y[i]) {
        frontI++;
        cmin = seg.query(frontI, i);
      }
      cmin = max(cmin, x[i]);
    } else {
      cmin = x[i];
    }

    out = max(out, i - frontI + 1);
  }
  cout << out << '\n';
  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex0");
  test("ex1");
  return 0;
}
#endif
