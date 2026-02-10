#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  string a, b;
  cin >> a >> b;

  int aBlackCount = 0;
  for (int i = 0; i < n; i++) aBlackCount += a[i] == 'C';

  if (aBlackCount <= n/2) swap(a, b);

  vector<int> abpos;
  vector<int> bcpos;
  for (int i = 0; i < n; i++) {
    if (a[i] == 'B') abpos.push_back(i);
    if (b[i] == 'C') bcpos.push_back(i);
  }
  assert(abpos.size() == bcpos.size());

  ll cost = 0;
  for (int i = 0; i < (int)abpos.size(); i++) {
    int ai = abpos[i];
    int bi = bcpos[i];
    int minDist = abs(ai-bi);

    cost += minDist + 1;
  }

  cout << cost << '\n';
  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex0");
  test("ex1");
  test("ex2");
  // test("net/kul0d");
  // test("net/kul0e");
  // for (char i = 'a'; i <= 'h'; i++) test(format("net/kul1{}", i), false);
  // for (char i = 'a'; i <= 't'; i++) test(format("net/kul2{}", i), false);
  // for (char i = 'a'; i <= 'f'; i++) test(format("net/kul3{}", i), false);
  // for (char i = 'a'; i <= 'j'; i++) test(format("net/kul4{}", i), false);
  // for (char i = 'a'; i <= 'm'; i++) test(format("net/kul5{}", i), false);
  // for (char i = 'a'; i <= 'j'; i++) test(format("net/kul6{}", i), false);
  // for (char i = 'a'; i <= 'k'; i++) test(format("net/kul7{}", i), false);
  // for (char i = 'a'; i <= 'n'; i++) test(format("net/kul8{}", i), false);
  // for (char i = 'a'; i <= 'e'; i++) test(format("net/kul9{}", i), false);
  // for (char i = 'a'; i <= 'e'; i++) test(format("net/kul10{}", i), false);
  // for (char i = 'a'; i <= 'j'; i++) test(format("net/kul11{}", i), false);
  
  return 0;
}
#endif
