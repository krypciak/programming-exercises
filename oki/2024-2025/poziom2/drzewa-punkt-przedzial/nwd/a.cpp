#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  vector<int> t;
  int n;

  int comb(int a, int b) {
    if (a == -1) return b;
    return gcd(a, b);
  }

  Seg(const vector<int> &v) {
    n = v.size();
    t = vector<int>(n*2);

    for (int i = n; i < n*2; i++) t[i] = v[i-n];
    for (int i = n-1; i > 0; i--) t[i] = comb(t[i<<1], t[i<<1|1]);
  }

  void set(int i, int v) {
    for (t[i+=n] = v; i > 1; i >>= 1) t[i>>1] = comb(t[i], t[i^1]);
  }

  int query(int l, int r) {
    int res = -1;
    for (l+=n, r+=n; r > l; l>>=1, r>>=1) {
      if (l&1) res = comb(res, t[l++]);
      if (r&1) res = comb(res, t[--r]);
    }
    return res;
  }
};

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  Seg seg(v);

  while (m--) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 1) {
      seg.set(a-1, b);
    } else {
      int res = seg.query(a-1, b);
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
void printT(string name, string expS, string outS) {
  if (expS == outS)
    printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
  else
    printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: " "\n'%s'\n-----got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
}
void test(string name) {
  ifstream in(name + ".in");
  ostringstream out;
  run(in, out);
  string outS = rtrim(out.str());

  ifstream exp(name + ".out");
  string expS(istreambuf_iterator<char>{exp}, {});
  expS = rtrim(expS);

  printT(name, expS, outS);
}
int main() {
  test("ex0");
  test("ex1");
  return 0;
}
#endif
