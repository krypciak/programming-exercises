#include <bits/stdc++.h>
#include <climits>
using namespace std;

typedef long long ll;
typedef array<int, 3> BoxA;

struct Box {
  BoxA sizes;
  array<BoxA, 6> vars;

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

int rec(const int n, const vector<Box> &boxes, int at, const BoxA &minBox) {
  ll maxV = 0;
  auto box = boxes[at];
  for (int j = 0; j < 6; j++) {
    BoxA newMinBox = {
        min(box.vars[j][0], minBox[0]),
        min(box.vars[j][1], minBox[1]),
        min(box.vars[j][2], minBox[2]),
    };
    if (at == n - 1) {
      ll v = newMinBox[0] * newMinBox[1] * newMinBox[2];
      // print("{} = {} x {} x {}\n", v, newMinBox[0], newMinBox[1],
      // newMinBox[2]);
      maxV = max(maxV, v);
    } else {
      ll v = rec(n, boxes, at + 1, std::move(newMinBox));
      maxV = max(maxV, v);
    }
  }
  return maxV;
}

int brute(const int n, const vector<Box> &boxes) {
  return rec(n, boxes, 0, {INT_MAX, INT_MAX, INT_MAX});
}

void genTest(ostream &cout, ostream &outCout) {
  int n = 10;
  int MAX = 100;
  cout << n << '\n';

  vector<Box> boxes(n);

  for (int i = 0; i < n; i++) {
    int a = (rand() % MAX) + 1;
    int b = (rand() % MAX) + 1;
    int c = (rand() % MAX) + 1;
    boxes[i].init(a, b, c);
    cout << a << ' ' << b << ' ' << c << '\n';
  }

  int bruteRes = brute(n, boxes);
  outCout << bruteRes << '\n';
}
int main() {
  for (int i = 0; i < 10000; i++) {
    ofstream inp(format("gen/{}.in", i));
    ofstream out(format("gen/{}.out", i));
    genTest(inp, out);
    inp.close();
    out.close();
  }
  return 0;
}
