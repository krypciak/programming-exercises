#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int K = 10;
struct Table {
private:
  int n;
  vector<int> t[K];

  int comb(int a, int b) { return abs(a - b); }

public:
  Table(const vector<int> &arr) {
    n = arr.size();

    t[0] = arr;
    for (int i = 1; i < K; i++) {
      const int jumpSize = 1<<(i-1);
      const int newSize = t[i-1].size()-jumpSize;
      if (newSize <= 0) break;
      t[i].assign(newSize, 0);
      for (int j = 0; j < newSize; j++) {
        t[i][j] = comb(t[i-1][j], t[i-1][j+jumpSize]);
      }
    }
  }


  int query(int l, int k) {
    // println("query: l: {}, k: {}", l, k);
    if (k < K) {
      return t[k][l];
    } else {
      const int to = l+(1<<k);
      const int initialSize = (to-l)>>(K-1);
      // println("l: {}, k: {}, K: {}, initialSize: {}", l, k, K, initialSize);
      const int jumpSize = 1<<(K-1);

      vector<int> values(initialSize);
      for (int i = 0; i < initialSize; i++) values[i] = t[K-1][l+i*jumpSize];
      int size = initialSize;
      while (values.size() > 1) {
        size >>= 1;
        vector<int> nextValues(size);
        for (int i = 0; i < size; i++) {
           nextValues[i] = comb(values[i<<1], values[i<<1|1]);
        }
        values = nextValues;
      }
      #ifdef TEST
      assert(values.size() == 1);
      #endif
      return values[0];
    }
    return 0;
  }
  
  void set(int p, int v) {
    // println("set p: {}, v: {}", p, v);
    t[0][p] = v;
    int l = p;
    for (int i = 1; i < K; i++) {
      const int jumpSize = 1<<(i-1);
      l = max(0, l-jumpSize);
      for (int j = l; j < min((int)t[i].size(), p+1); j++) {
        t[i][j] = comb(t[i-1][j], t[i-1][j+jumpSize]);
      }
    }
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  vector<tuple<int, int, int>> queries(q);
  for (int i = 0; i < q; i++) {
    int t, b, c;
    cin >> t >> b >> c;
    queries[i] = {t, b, c};
  }

  Table table(a);

  for (int i = 0; i < q; i++) {
    auto [t, l, r] = queries[i];
    if (t == 1) {
      table.set(l-1, r);
    } else {
      int res = table.query(l-1, r);
      cout << res << '\n';
    }
  }

  return 0;
}

#ifndef TEST
int main() { return run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
  test("ex1");
  test("ex3");
  test("ex0");
  test("ex2");
  
  // for (int i = 0; i < 1000; i++) test(format("gen/{}", i), i%100==0);
}
#endif
