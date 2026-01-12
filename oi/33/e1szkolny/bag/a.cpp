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

int run(istream &cin, ostream &cout) {
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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
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
