#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Seg {
public:
  vector<ll> t;
  int n;

  ll comb(ll a, ll b) {
    return (a * b) % 12345;
  }

  Seg(const vector<int> &v) {
    n = v.size();
    t = vector<ll>(n*2);

    for (int i = n; i < n*2; i++) t[i] = v[i-n];
    for (int i = n - 1; i > 0; i--) t[i] = comb(t[i<<1], t[i<<1|1]);
  };

  void set(int i, ll v) {
    for (t[i+=n] = v; i > 1; i >>= 1) t[i>>1] = comb(t[i], t[i^1]);
  }

  ll query(int l, int r) {
    ll res = 1;
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
  vector<int> nums(n);
  for (int i = 0; i < n; i++)
    cin >> nums[i];

  Seg seg(nums);

  while (m--) {
    int t, a;
    ll b;
    cin >> t >> a >> b;
    if (t == 1) {
      seg.set(a-1, b);
    } else if (t == 2) {
      ll res = seg.query(a-1, b);
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
