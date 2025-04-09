#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int z;
  cin >> z;
  while (z--) {
    int n;
    cin >> n;
    struct Mine {
      ll x;
      ll rad;
    };
    vector<Mine> M(n);
    for (int i = 0; i < n; i++) {
      ll x, rad;
      cin >> x >> rad;
      ;
      M[i] = {x, rad};
    }
    struct Ca {
      ll l, r;
      int li, ri;
    };
    vector<Ca> c(n);
    for (int i = 0; i < n; i++) {
      auto [x, rad] = M[i];
      c[i] = {x - rad, x + rad, i - 1, i + 1};
    }

    // print("pass\n");
    for (int i = 0; i < n; i++) {
      auto [Ol, Or, mli, mri] = c[i];
      int nli, nri;
      ll l, r;
      bool modified = true;
      while (modified) {
        modified = false;
        nli = i - 1;
        nri = i + 1;
        l = Ol;
        r = Or;
        for (int li = i - 1; li >= 0 && M[li].x >= Ol; li--) {
          r = max(r, c[li].r);
          l = min(l, c[li].l);
          nri = max(nri, c[li].ri);
          nli = min({nli, li, c[li].li});
        }
        for (int ri = i + 1; ri < n && M[ri].x <= Or; ri++) {
          r = max(r, c[ri].r);
          l = min(l, c[ri].l);
          nri = max({nri, ri, c[ri].ri});
          nli = min(nli, c[ri].li);
        }
        if (l != Ol || r != Or) modified = true;
        Ol = l;
        Or = r;
      }
      c[i] = {l, r, nli, nri};
    }
    // print("ranges:\n");
    // for (int i = 0; i < n; i++) {
    //   print("{}: [{}, {}], from i: [{}, {}]\n", i, c[i].l, c[i].r, c[i].li,
    //   c[i].ri);
    // }
    for (int i = 0; i < n; i++)
      cout << (c[i].ri - c[i].li - 1) << ' ';
    cout << '\n';
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
    printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n",
           name.c_str());
  else
    printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: "
           "\n'%s'\n-----got: \n'%s'\n\n",
           name.c_str(), expS.c_str(), outS.c_str());
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
  test("ex3");
  test("ex1");
  test("ex2");
  return 0;
}
#endif
