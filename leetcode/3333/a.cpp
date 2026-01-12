#include <bits/stdc++.h>
using namespace std;

typedef __int128 uint128;
class Solution {
public:
  char kthCharacter(long long k, vector<int>& operations) {
    int offset = 0;
    for (int i = 63 - __builtin_clzll((unsigned long long)k); i >= 0; i--) {
      long long half = (long long) 1 << i;
      if (k > half) {
        k -= half;
        if (operations[i]) offset++;
      }
    }

    return 'a' + (offset % 26);
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  long long k;
  cin >> k;

  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  Solution sol;
  cout << sol.kthCharacter(k, v) << endl;

  return 0;
}
#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../tester.h"
int main() {
  test("ex0");
  test("ex1");
  test("ex2");
  return 0;
}
#endif
