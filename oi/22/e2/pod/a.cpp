#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
vector<int> kinds;
map<int, int> fr;

int getKind(int k) {
  if (fr.count(k) > 0) return fr[k];
  return k;
}

bool isOutOfRange(int l, int r, int k) {
  for (int i = 0; i < l; i++) 
    if (getKind(kinds[i]) == k) return true;
  for (int i = r+1; i < n; i++) 
    if (getKind(kinds[i]) == k) return true;
  return false;
}

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  cin >> n >> k;

  kinds = vector<int>(n);
  for (int i = 0; i < n; i++) cin >> kinds[i];

  fr = map<int, int>();

  vector<int> lastSeen(k+1, -1);
  for (int i = 0; i < n; i++) {
    int ck = getKind(kinds[i]);
    int lsi = lastSeen[ck];
    if (lsi == -1 || lsi == i-1) {
      lastSeen[ck] = i;
    } else {
      for (int j = lsi+1; j < i; j++) {
        int sk = getKind(kinds[j]);
        if (sk != ck && isOutOfRange(lsi, i, sk)) {
          // no matter how you slice it, it is entangled
          fr[sk] = ck;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << getKind(kinds[i]) << " ";
  }

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
