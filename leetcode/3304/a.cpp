#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  char kthCharacter(int k) {
    int sum = 0;
    for (k--; k > 0; k >>= 2)
      sum += ((k&3)+1) >> 1;
  
    return sum % ('z' - 'a') + 'a';
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int k;
  cin >> k;

  Solution sol;
  cout << sol.kthCharacter(k) << endl;

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../tester.h"
int main() {
  test("ex2");
  test("ex3");
  test("ex4");
  test("ex5");
  test("ex0");
  test("ex1");
  return 0;
}
#endif
