#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, x;
  cin >> n >> x;

  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  ll buyMax = LLONG_MIN;
  ll sellMax = 0;
  for (int i = 0; i < n; i++) {
    int v = a[i];
    buyMax = max(buyMax, sellMax - x - v);
    sellMax = max(sellMax, buyMax + v);
  }

  cout << sellMax << '\n';

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
