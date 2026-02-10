#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int s, k, n;
  cin >> s >> k >> n;
  vector<int> canPayArr(n);
  for (int &x : canPayArr) cin >> x;

  sort(canPayArr.begin(), canPayArr.end());

  ll maxProfit = 0;
  
  for (int i = n-1, j = 1; i >= 0 and j <= s; i--, j++) {
    ll canPay = canPayArr[i];
    if (canPay <= k) break;
    ll newProfit = (ll)j*(canPay - k);
    // println("canPay: {}, newProfit: {}", canPay, newProfit);

    maxProfit = max(maxProfit, newProfit);
  }
  cout << maxProfit << '\n';

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
