#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int s, k, m;
    cin >> s >> k >> m;

    int sand = s;
    auto calc = [&]() {
      int times = floor((double)m/k);
      sand = s <= k or !(times&1) ? s : k;
      m %= k;
      return max(0, sand-m);
    };
    int res = calc();
    cout << res << '\n';
  }
  return 0;
}
#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex0");
  return 0;
}
#endif
