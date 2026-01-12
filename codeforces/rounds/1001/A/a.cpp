#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int q;
  cin >> q;
  while (q--) {
    string seq;
    cin >> seq;

    int sum = 0;
    for (char c : seq)
      if (c == '1')
        sum++;
    cout << sum << '\n';
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
