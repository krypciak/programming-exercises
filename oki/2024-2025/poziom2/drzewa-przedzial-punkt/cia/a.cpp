#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
  ll a;
  ll b;
  int nl;

  ll calc(int l) {
    return a * (l-nl) + b;
  }

  void merge(int l, ll na, ll nb) {
    ll naDiff = (nl - l) * na;
    b += nb + naDiff;
    a += na;
  }
};

struct Seg {
  int n;
  vector<Node> t;

  Seg(vector<ll> &initial) : n(initial.size()), t(n*2) {
    for (int i = 0; i < n; i++) t[i+n] = {0, initial[i], i-n};
    
    for (int i = n-1; i > 0; i--) t[i] = {0, 0, t[i<<1].nl};
    
  }

  void add(int lo, int ro, ll a, ll b) {
    for (int l = lo+n, r = ro+n; r > l; r >>= 1, l >>= 1) {
      if (l&1) t[l++].merge(lo, a, b);
      if (r&1) t[--r].merge(lo, a, b);
    }
  }

  ll query(int i) {
    ll sum = 0;
    for (int p = n+i; p > 0; p >>= 1) 
      sum += t[p].calc(i);
    
    return sum;
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
      ll b, a;
      cin >> b >> a;
      seg.add(l, r, a, b);
    } else assert(false);
  }

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
  test("ex3");
  test("ex2");
  test("ex0");
  test("ex1");
  return 0;
}
#endif
