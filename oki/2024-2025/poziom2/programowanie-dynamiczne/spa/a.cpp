#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, k;
  cin >> n >> k;

  const ll MOD = 1e9 + 7;
  vector<ll> dp(n+1);
  vector<ll> dpSum(n+2);
  dp[0] = 1;
  dp[1] = 1;
  dpSum[1] = 1;
  dpSum[2] = 2;

  for (int i = 2; i <= n; i++) {
    ll sum = (MOD + dpSum[i] - dpSum[i-min(i, k)]) % MOD;
    dp[i] = sum;
    dpSum[i+1] = (dpSum[i]+sum) % MOD;
  }
  cout << dp[n] << '\n';
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
  return 0;
}
#endif
