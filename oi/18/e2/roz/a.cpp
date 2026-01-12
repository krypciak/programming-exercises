#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cti(char c) { return c - 'a'; }

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  string str;

  cin >> n;
  cin >> str;

  const int al = 'z' - 'a' + 1;
  vector<vector<int>> locc(al);
  for (int i = 0; i < n; i++) {
    locc[cti(str[i])].push_back(i);
  }

  int out = 0;
  for (int k = 0; k < al; k++) {
    for (int l = 0; l < al; l++) {
      if (k == l)
        continue;

      int mi = INT_MAX, sum = 0, res = 0, sum_pop = 0;
      int ki = 0, li = 0;
      while (true) {
        bool kDone = ki >= (int)locc[k].size();
        bool lDone = li >= (int)locc[l].size();
        if (kDone and lDone)
          break;
        while (!kDone and (lDone or locc[k][ki] < locc[l][li])) {
          sum++;
          res = max(res, sum - mi);

          ki++;
          kDone = ki >= (int)locc[k].size();
        }
        while (!lDone and (kDone or locc[l][li] < locc[k][ki])) {
          sum--;
          mi = min(mi, sum_pop);
          sum_pop = sum;
          res = max(res, sum - mi);

          li++;
          lDone = li >= (int)locc[l].size();
        }
      }
      out = max(out, res);
    }
  }
  cout << out << '\n';

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
