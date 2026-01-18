#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;

  ll lastOpen = 0;
  ll lastClose = 0;
  for (int i = 0; i < n; i++) {
    ll v;
    cin >> v;
    ll open = lastClose + v;
    ll close = lastOpen;
    lastOpen = open;
    lastClose = max(lastClose, close);
  }

  cout << max(lastOpen, lastClose) << '\n';

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
