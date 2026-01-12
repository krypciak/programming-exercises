#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
  ll value;
  int lastChanged;

  auto operator<=>(const Node &a) const {
    return lastChanged <=> a.lastChanged;
  }
};

struct Seg {
  vector<Node> t;
  int n;
  int changedCounter;

  Seg(vector<ll> &initial) {
    n = initial.size();
    t = vector<Node>(n*2);
    for (int i = n; i <n*2; i++) {
      t[i] = {initial[i-n], 0};
    }
    changedCounter = 1;
  }

  void set(int l, int r, ll v) {
    for (l += n, r += n; r > l; r >>= 1, l >>= 1) {
      if (l&1) t[l++] = {v, changedCounter};
      if (r&1) t[--r] = {v, changedCounter};
    }
    changedCounter++;
  }

  ll query(int p) {
    Node latest = {0, -1};
    for (p += n; p > 0; p >>= 1) {
      latest = max(latest, t[p]);
    }
    return latest.value;
  }

};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<ll> initial(n);
  for (int i = 0; i < n; i++) cin >> initial[i];

  Seg seg(initial);

  while(m--) {
    int t;
    cin >> t;
    if (t == 1) {
      int i;
      cin >> i;
      i--;
      ll res = seg.query(i);
      cout << res << '\n';
    } else if (t == 2) {
      int l, r;
      cin >> l >> r;
      l--;
      ll v;
      cin >> v;
      seg.set(l, r, v);
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
