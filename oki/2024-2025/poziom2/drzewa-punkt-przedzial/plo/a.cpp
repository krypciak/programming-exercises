#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  vector<int> t;
  int n;

  int comb(int a, int b) {
    return a +  b;
  }

  Seg(int n) : n(n) {
    t = vector<int>(n*2, 0);
  }

  void set(int i, int v) {
    for (t[i+=n] = v; i > 1; i >>= 1) t[i>>1] = comb(t[i], t[i^1]);
  }

  int query(int l, int r) {
    int res = 0;
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

  Seg seg(n);

  while (m--) {
    int t;
    cin >> t;
    if (t == 1) {
      int i;
      cin >> i;
      i--;
      seg.set(i, seg.t[i+n]+1);
    } else if (t == 2) {
      int l, r;
      cin >> l >> r;
      int res = seg.query(l-1, r);
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
  return 0;
}
#endif
