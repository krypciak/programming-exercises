#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;

#ifndef TEST
void readLong(ll &x) {
  x = 0;
  int c = getchar_unlocked();
  while (c >= '0' && c <= '9') {
      x = x * 10 + (c - '0');
      c = getchar_unlocked();
  }
}
#endif

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  ll totalDist, leftDist, n;
  #ifdef TEST
  cin >> totalDist >> leftDist >> n;
  #else
  readLong(totalDist), readLong(leftDist), readLong(n);
  #endif
  vector<ll> taxis(n);
  for (int i = 0; i < n; i++) {
    #ifdef TEST
    cin >> taxis[i];
    #else
    readLong(taxis[i]);
    #endif
  }

  sort(taxis.begin(), taxis.end());

  auto solve = [&]() -> int {
    ll rightDist = totalDist-leftDist;

    int rightMinTaxiI = distance(taxis.begin(), lower_bound(taxis.begin(), taxis.end(), rightDist));
    if (rightMinTaxiI == n) return 0;

    int taxisUsed = 0;
    ll at = 0;
    int i = n-1;
    for (; i >= 0 and at < leftDist; i--) {
      if (i == rightMinTaxiI) continue;
      ll fuel = taxis[i];
      fuel -= leftDist-at;
      if (fuel <= 0) break;
      at += fuel;
      taxisUsed++;
    }

    if (at >= totalDist) return taxisUsed;
    ll fuel = taxis[rightMinTaxiI];
    if (at < leftDist) {
      fuel -= 2*(leftDist-at);
      at = leftDist;
    }
    at += fuel;
    taxisUsed++;

    if (at >= totalDist) return taxisUsed;
    else return 0;
  };
  cout << solve() << '\n';

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex0");
  test("ex1");
  test("ex2");
  test("ex3");
  test("ex4");
  return 0;
}
#endif
