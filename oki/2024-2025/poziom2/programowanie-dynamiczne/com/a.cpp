#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  string a, b;
  cin >> a >> b;

  const int n = a.size();
  const int m = b.size();

  vector<vector<int>> dp(n+1, vector<int>(m+1));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i-1] == b[j-1]) {
        dp[i][j] = dp[i-1][j-1]+1;
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }
  cout << dp[n][m] << '\n';


  string str;
  int i = n, j = m;
  while (i > 0 and m > 0) {
    if (a[i-1] == b[j-1]) {
      str.push_back(a[i-1]);
      i--, j--;
    } else if (dp[i-1][j] >= dp[i][j-1]) i--;
    else j--;
  }
  reverse(str.begin(), str.end());
  cout << str << '\n';

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
  test("ex1");
  test("ex0");
  return 0;
}
#endif
