#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(ll n) {
  for (int i = 0; n > 0 && i < 8; i++) {
    if (n % 8 == 0) {
      break;
    }
    n -= 3;
  }

  return n % 8 == 0;
}

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  ll n;
  cin >> n;

  if (check(n)) {
    cout << "TAK" << '\n';
  } else {
    cout << "NIE" << '\n';
  }

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
  return 0;
}
#endif
