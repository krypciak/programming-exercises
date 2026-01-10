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

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
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
#ifdef TEST
string rtrim(string s) {
  auto end = s.find_last_not_of(" \t\r\v\f\n");
  return end == string::npos ? s : s.substr(0, end + 1);
}
bool isTestOk(string inpS, string expS, string outS) {
  if (inpS.size()) {}
  return expS == outS;
}
bool printT(string name, string expS, string outS, string inpS, bool passPrint) {
  if (isTestOk(inpS, expS, outS)) {
    if (passPrint) {
      printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
    }
    return true;
  } else {
    int limit = 200;
    printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n-----got: \n'%s'\n\n",
           name.c_str(), expS.substr(0, limit).c_str(), outS.substr(0, limit).c_str());
    return false;
  }
}
bool testStrs(string &name, string inS, string expS, bool passPrint = true) {
  stringstream in(inS);
  ostringstream out;

  run(in, out);
  string outS = rtrim(out.str());

  expS = rtrim(expS);

  return printT(name, expS, outS, inS, passPrint);
}
void test(string name, bool passPrint = true) {
  ifstream in(name + ".in");
  ifstream exp(name + ".out");

  string inS(istreambuf_iterator<char>{in}, {});
  string expS(istreambuf_iterator<char>{exp}, {});
  testStrs(name, inS, expS, passPrint);
}
int main() {
  test("ex1");
  test("ex3");
  test("ex0");
  test("ex2");
  
  // for (int i = 0; i < 1000; i++) test(format("gen/{}", i), i%100==0);
}
#endif
