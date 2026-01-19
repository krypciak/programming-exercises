#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; i++) cin >> nums[i];
  sort(nums.begin(), nums.end());

  int score = nums[0];
  for (int i = 0; i < n; i++) {
    score = max(score, nums[i]-score);
  }
  cout << score << '\n';
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
