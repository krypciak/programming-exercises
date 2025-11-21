#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Box {
  array<int, 3> sizes;
  array<array<int, 3>, 6> vars;

  void init(int a, int b, int c) {
    sizes = {a, b, c};
    sort(sizes.begin(), sizes.end(), greater());
    a = sizes[0];
    b = sizes[1];
    c = sizes[2];

    vars[0] = {a, b, c};
    vars[1] = {a, c, b};
    vars[2] = {b, a, c};
    vars[3] = {b, c, a};
    vars[4] = {c, a, b};
    vars[5] = {c, b, a};
  }

  void printSizes() { print("[{}, {}, {}]\n", sizes[0], sizes[1], sizes[2]); }

  void printVars() {
    for (int i = 0; i < 6; i++) {
      print("[{}, {}, {}]\n", vars[i][0], vars[i][1], vars[i][2]);
    }
    print("\n");
  }
};

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<Box> boxes(n);
  for (int i = 0; i < n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    boxes[i].init(a, b, c);
    // boxes[i].printVars();
  }

  ll allbv = 0;
  for (int h = 0; h < 6; h++) {
    auto [ma, mb, mc] = boxes[0].vars[h];
    for (int i = 1; i < n; i++) {
      int ba = ma, bb = mb, bc = mc;
      int bv = 0;
      for (int j = 0; j < 6; j++) {
        auto [ca, cb, cc] = boxes[i].vars[j];
        auto [a, b, c] = array<int, 3>{min(ma, ca), min(mb, cb), min(mc, cc)};
        ll v = (ll)a * b * c;
        if (v > bv) {
          bv = v, ba = a, bb = b, bc = c;
        }
      }
      ma = ba, mb = bb, mc = bc;
    }
    ll v = (ll)ma * mb * mc;
    if (v > allbv) {
      allbv = v;
    }
  }
  cout << allbv << '\n';

  return 0;
}
#ifdef TEST
string rtrim(string s) {
  auto end = s.find_last_not_of(" \t\r\v\f\n");
  if (end != string::npos)
    s = s.substr(0, end + 1);
  erase(s, '\r');
  return s;
}
bool isTestOk(string inpS, string expS, string outS) {
  if (inpS.size()) {
  }
  return expS == outS;
}
bool printT(string name, string expS, string outS, string inpS,
            bool passPrint) {
  if (isTestOk(inpS, expS, outS)) {
    if (passPrint) {
      printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n",
             name.c_str());
    }
    return true;
  } else {
    int limit = 200;
    printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: "
           "\n'%s'\n-----got: \n'%s'\n\n",
           name.c_str(), expS.substr(0, limit).c_str(),
           outS.substr(0, limit).c_str());
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
  test("bag0a");
  test("bag0b");
  test("bag0c");
  test("bag0d");

  // for (int i = 0; i < 10000; i++) {
  //   test(format("gen/{}", i));
  // }
  return 0;
}
#endif
