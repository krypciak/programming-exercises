#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> G(n+1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  ll out = 0;
  vector<bool> visited(n+1, false);
  visited[0] = true;
  vector<int> TV{0};
  for (int dist = 1; TV.size(); dist++) {
    vector<int> nTV;
    for (int v : TV) {
      for (int u : G[v]) {
        if (visited[u]) continue;
        visited[u] = true;
        nTV.push_back(u);
        out += dist*2;
      }
    }
    TV = nTV;
  }
  cout << out << '\n';

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
  return 0;
}
#endif
