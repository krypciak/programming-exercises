#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<ll> k(n), u(m);
  for (int i = 0; i < n; i++) cin >> k[i];
  for (int i = 0; i < m; i++) cin >> u[i];

  sort(k.begin(), k.end());
  multiset<int> us(u.begin(), u.end());

  ll sum = 0;
  int matchless = 0;
  for (int ki = n-1; ki >= 0; ki--) {
    ll kv = k[ki];

    auto ui = us.upper_bound(kv);
    if (ui == us.end()) {
      matchless++;
      continue;
    }
    ll uv = *ui;
    us.erase(ui);
    ll diff = uv-kv;
    #ifdef TEST
    assert(uv > kv);
    assert(diff > 0);
    #endif
    sum += diff;
    // println("kv: {}, uv: {}, diff: {}", kv, uv, diff);
  }
  if (matchless) {
    cout << "NIE" << '\n';
    cout << matchless << '\n';
  } else {
    cout << "TAK" << '\n';
    cout << sum << '\n';
  }
  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
  test("ex0");
  test("ex1");
  test("ex2");
  test("ex3");
  test("ex4");
  test("ex5");
  // test("net/abr1a");
  // test("net/abr1b");
  // test("net/abr1c");
  // test("net/abr1c");
  // test("net/abr1d");
  // test("net/abr1e");
  // test("net/abr2a");
  // test("net/abr2b");
  // test("net/abr2c");
  // test("net/abr2d");
  // test("net/abr3a");
  // test("net/abr3b");
  // test("net/abr3c");
  // test("net/abr3d");
  // test("net/abr3e");
  return 0;
}
#endif
