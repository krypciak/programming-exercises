#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  int n;
  vector<pair<int, int>> t;

  Seg(int n) : n(n) {
    t.assign(n*2, {0, 0});
  }

  pair<int, int> query(int l, int r) {
    l += n, r += n;
    pair<int, int> res = max(t[l], t[r-1]);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) res = max(res, t[l++]);
      if (r&1) res = max(res, t[--r]);
    }
    return res;
  }

  void set(int p, pair<int,int> v) {
    for (p += n; p; p >>= 1) {
      if(t[p].first < v.first) t[p] = v;
    }
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n+1);
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<pair<int, int>> toProcess;
  toProcess.reserve(n);
  for (int i = 1; i <= n; i++) {
    if (i-a[i] >= 0) toProcess.push_back({i-a[i], a[i]});
  }
  sort(toProcess.begin(), toProcess.end());

  pair<int, int> ans;
  vector<int> p(n+1);
  Seg seg(n+1);

  for (auto [diff, ai] : toProcess) {
    int i = diff + ai;

    auto [maxScore, j] = seg.query(1, ai);
    maxScore++;
    p[i] = j;
    seg.set(ai, {maxScore, i});

    ans = max(ans, {maxScore, i});
  }

  int i = ans.second;
  cout << i - a[i] << '\n';
  vector<int> toDelete;
  while (i) {
    int j = p[i];
    for (int h = 0; h < i-j-a[i]+a[j]; h++) {
      toDelete.push_back(j+h+1);
    }
    i = j;
  }
  reverse(toDelete.begin(), toDelete.end());
  for (auto v : toDelete) cout << v << ' ';

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
