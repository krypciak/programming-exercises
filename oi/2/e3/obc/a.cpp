#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

using namespace std;

vector<vector<int>> G;
vector<int> result;

void dfs(int upo, int p, bool even) {
  if (even)
    result.push_back(upo);

  for (int u : G[upo]) {
    if (u != p) dfs(u, upo, !even);
  }
  if (!even)
    result.push_back(upo);
}

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  int n;
  cin >> n;

  G.assign(n + 1, {});
  result.clear();
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  int root = 1;
  dfs(root, 0, true);
  for (int x : result) {
    cout << x << '\n';
  }

  return 0;
}
#ifdef TEST
string rtrim(string s) {
  auto end = s.find_last_not_of(" \n\r\t\f\v");
  return end == string::npos ? s : s.substr(0, end + 1);
}
void printT(string name, string outS, string expS) {
  if (outS == expS) {
    print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
  } else {
    print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: "
          "\n'{}'\n---got: \n'{}'\n\n",
          name, expS, outS);
  }
}
void test(string name) {
  ifstream in(name + ".in");
  ostringstream out;

  run(in, out);
  string outS = rtrim(out.str());

  ifstream exp(name + ".out");
  string expS(istreambuf_iterator<char>{exp}, {});
  expS = rtrim(expS);

  printT(name, outS, expS);
}
int main() {
  test("ex0");
  test("ex1");
  test("ex2");
  return 0;
}
#endif
