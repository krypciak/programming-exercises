#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<int> W(n), L(n);
  for (int i = 0; i < n; i++) cin >> W[i] >> L[i];
  int q;
  cin >> q;

  const int MAX_W = 10000 + 1;
  vector<char> dp(MAX_W, false);
  dp[0] = true;

  for (int i = 0; i < n; i++) {
    int w = W[i]; // wartosc
    int l = L[i]; // liczba

    vector<int> cnt(MAX_W);
    for (int s = w; s < MAX_W; s++) {
      if (!dp[s] and dp[s-w] and cnt[s-w] < l) {
        dp[s] = true;
        cnt[s] = cnt[s-w] + 1;
      }
    }
  }

  while (q--) {
    int x;
    cin >> x;
    cout << (dp[x] ? "TAK" : "NIE") << '\n';
  }

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
