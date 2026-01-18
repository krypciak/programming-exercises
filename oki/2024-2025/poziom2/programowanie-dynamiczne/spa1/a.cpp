#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; i++) cin >> nums[i];

  int sum = 0;
  for (int i = 0; i < n; i++) sum += nums[i];
  double halfSum = sum/2;

  vector<char> dp(halfSum+1, false);
  dp[0] = true;
  for (int i = 0; i < (int)nums.size(); i++) {
    int num = nums[i];
    for (int j = halfSum; j >= num; j--) {
      dp[j] |= dp[j - num];
    }
  }
  int i;
  for (i = dp.size()-1; i >= 0 and !dp[i]; i--) {}

  int n1 = i;
  int n2 = sum-i;
  if (n2 > n1) swap(n2, n1);
  cout << n1 << ' ' << n2 << '\n';

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
  test("ex0");
  test("ex1");
  return 0;
}
#endif
