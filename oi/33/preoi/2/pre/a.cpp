#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_BIT = 30;
struct Wavelet {
  array<vector<int>, MAX_BIT> num_lefts;

  Wavelet(vector<int> nums) {
    num_lefts.fill({0});
    for (int b = MAX_BIT-1; b >= 0; b--) {
      array<vector<int>, 2> bucket;
      for (int x : nums) {
        bucket[(x>>b)&1].push_back(x);
        num_lefts[b].push_back(bucket[0].size());
      }
      nums = move(bucket[0]);
      nums.insert(nums.end(), bucket[1].begin(), bucket[1].end());
    }
  }

  int kth(int l, int r, int k) {
    int ans = 0;
    for (int b = MAX_BIT-1; b >= 0; b--) {
      int pl = num_lefts[b][l];
      int pr = num_lefts[b][r];
      int diff = pr - pl;
      if (k < diff) {
        l = pl, r = pr;
        continue;
      }
      k -= diff;
      l += num_lefts[b].back() - pl;
      r += num_lefts[b].back() - pr;
      ans |= 1<<b;
    }
    return ans;
  }
};


int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  Wavelet vl(a);

  while (q--) {
    int l, r, m, k;
    cin >> l >> r >> m >> k;
    l--;

    auto solve = [&] {
      int p = l+k+m-2;
      if (p > r-1) {
        return vl.kth(l, r, k-1);
      } else {
        return min(a[p], vl.kth(l, p, k-1));
      }
    };
    cout << solve() << '\n';
  }

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
  test("pre0a");
  test("pre0b");
  test("pre0c");
  test("pre0d");
  test("pre0e");
  return 0;
}
#endif
