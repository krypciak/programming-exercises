#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int Z;
  cin >> Z;
  while (Z--) {
    int n, m, q;
    cin >> n >> m >> q;
    
    vector<int> colors(n);
    for (int i = 0; i < n; i++) cin >> colors[i];

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
      int a, b;
      cin >> a >> b;
      queries[i] = {a, b};
    }

    vector<vector<int>> colorPos(m+1);
    for (int i = 0; i < n; i++) colorPos[colors[i]].push_back(i);

    vector<vector<ll>> colorPS(m+1), colorPE(m+1);
    for (int c = 1; c <= m; c++) {
      auto &ps = colorPS[c];
      auto &pe = colorPE[c];
      const int count = colorPos[c].size();
      ps.assign(count+1, 0);
      pe.assign(count+1, 0);
      for (int j = 0; j < count; j++) ps[j+1] = ps[j] + colorPos[c][j];
      for (int j = count-1; j >= 0; j--) 
        pe[j] = pe[j+1] + n-colorPos[c][j]-1;
    }

    unordered_map<ll, ll> cache;

    const int sqrtN = sqrt(n);
    
    for (auto [ca, cb] : queries) {
      if (colorPos[ca].size() > colorPos[cb].size() or (colorPos[ca].size() == colorPos[cb].size() and ca > cb)) swap(ca, cb);

      auto &ps = colorPS[cb];
      auto &pe = colorPE[cb];
      const int colorPosASize = colorPos[ca].size();
      const int colorPosBSize = colorPos[cb].size();
      auto &cpa = colorPos[ca];
      auto &cpb = colorPos[cb];

      ll hash;
      bool isBig = colorPosASize > sqrtN;
      if (isBig) {
        hash = (ll)ca+cb*(m+1);
        if (cache[hash]) {
          cout << cache[hash] << '\n';
          continue;
        }
      }

      int cbi = lower_bound(cpb.begin(), cpb.end(), cpa[0]) - 1 - cpb.begin();
      if (cbi < 0 or cbi == colorPosBSize) cbi = 0;
      // println("ca: {}, cb: {}, cbi: {}", ca, cb, cbi);

      const ll peFirst = pe[0];
      const ll psLast = ps[ps.size()-1];
      const int cpbFirst = cpb[cbi];

      ll sum = 0;
      int cai = 0;

      const ll psFirstCbi = ps[cbi];
      const ll diffFirst = colorPosBSize-cbi;
      for (; cai < colorPosASize; cai++) {
        const int ai = cpa[cai];
        if (cpbFirst < ai) break;

        const ll right = psLast - psFirstCbi - ai*diffFirst;
        sum += right;
      }

      for (; cai < colorPosASize; cai++) {
        const int ai = cpa[cai];
        {
          int step = 1;
          while (true) {
            const int newCbi = cbi+step;
            if (newCbi < colorPosBSize and cpb[newCbi] < ai) {
              cbi = newCbi;
              step <<= 1;
            } else break;
          }
          step >>= 1;
          for (; step > 0; step >>= 1) {
            const int newCbi = cbi+step;
            if (newCbi < colorPosBSize and cpb[newCbi] < ai) {
              cbi = newCbi;
            }
          }
        }
        
        const int rcbi = cbi+1;
        const ll left = peFirst - pe[rcbi] - (n-1-ai)*rcbi;
        sum += left;

        if (rcbi >= colorPosBSize) { cai++; break; }
        const ll right = psLast - ps[rcbi] - ai*(colorPosBSize-rcbi);
        sum += right;
      }

      const int lastRcbi = cbi+1;
      const ll peLastCbi = pe[lastRcbi];
      for (; cai < colorPosASize; cai++) {
        const int ai = cpa[cai];
        
        const ll left = peFirst - peLastCbi - (n-1-ai)*lastRcbi;
        sum += left;
      }
      if (isBig) cache[hash] = sum;
      cout << sum << '\n';
    }
  }
  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
  test("kol0a");
  test("kol0b");
  test("kol0c");
  return 0;
}
#endif
