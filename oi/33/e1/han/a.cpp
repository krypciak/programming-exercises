#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void printRow(ostream &cout, int from, int to) {
  cout << from+1 << ' ' << to+1 << '\n';
}

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> slots(m);
  vector<int> numberInitialSlots(n+1);
  for (int i = 0; i < m; i++) {
    int c;
    cin >> c;
    slots[i] = vector<int>(c);
    for (int j = c-1; j >= 0; j--) {
      int &v = slots[i][j];
      cin >> v;
      numberInitialSlots[v] = i;
    }
  }


  int initialFreeSlot = -1;
  for (int i = 0; i < m; i++) {
    if (slots[i].empty()) { initialFreeSlot = i; break; }
  }


  if (slots[numberInitialSlots[1]].back() + (int)slots[numberInitialSlots[1]].size() - 1 == slots[numberInitialSlots[1]].front()) {
    cout << n-slots[numberInitialSlots[1]].front() << '\n';
    for (int i = slots[numberInitialSlots[1]].front()+1; i <= n; i++) {
      printRow(cout, numberInitialSlots[i], numberInitialSlots[1]);
    }
  } else if (initialFreeSlot != -1) {
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
      printRow(cout, numberInitialSlots[i], initialFreeSlot);
    }
  } else {
    vector<pair<int, int>> frontNumsVec(m);
    for (int i = 0; i < m; i++) frontNumsVec[i] = {slots[i].empty() ? 1e9 : slots[i].front(), i};
    set<pair<int, int>> frontNumsSet(frontNumsVec.begin(), frontNumsVec.end());

    pair<int, int> canMakeFreeSlot = {-1, -1};
    for (int i = 0; i < m; i++) {
      if (canMakeFreeSlot.first != -1 and slots[i].size() > slots[canMakeFreeSlot.first].size()) continue;
      int iV = slots[i].back();

      auto bound = frontNumsSet.lower_bound({iV, 0});
      if (bound != frontNumsSet.begin()) {
        bound--;
        canMakeFreeSlot = {i, bound->second};
      }
    }

    if (canMakeFreeSlot.first != -1) {
      cout << slots[canMakeFreeSlot.first].size() + n << '\n';
      for (int i = slots[canMakeFreeSlot.first].size()-1; i >= 0; i--) {
        printRow(cout, canMakeFreeSlot.first, canMakeFreeSlot.second);
        numberInitialSlots[slots[canMakeFreeSlot.first][i]] = canMakeFreeSlot.second;
      }

      for (int i = 1; i <= n; i++) {
        printRow(cout, numberInitialSlots[i], canMakeFreeSlot.first);
      }
    } else {
      cout << -1 << '\n';
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
  stringstream exp(expS);
  stringstream out(outS);

  int expC;
  int outC;
  exp >> expC;
  out >> outC;
  return expC == outC;
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
  test("han0b");
  test("ex0");
  test("ex1");
  test("ex2");
  test("ex3");
  test("han0a");
  test("han0c");
  test("han0d");
  test("han0e");


  #ifdef ALLTESTS
  for (int i = 1; i <= 3000; i++) {
   test(format("net2/{}", i), i % 300 == 0);
  }
  for (int i = 1; i < 10000; i++) {
    test(format("net3/{}", i), i % 1000 == 0);
  }
  for (int i = 1; i < 1000; i++) {
    test(format("net0/han{}", i), i % 100 == 0);
  }
  for (int i = 1; i < 100; i++) {
    test(format("net1/m{}", i), i % 10 == 0);
  }
  return 0;
  #endif
}
#endif
