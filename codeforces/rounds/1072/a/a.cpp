#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int res;
    if (n <= 3) {
      res = n;
    } else if (n % 2 == 0) {
      res = 0;
    } else {
      res = 1;
    }
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
  test("ex1");
  return 0;
}
#endif
