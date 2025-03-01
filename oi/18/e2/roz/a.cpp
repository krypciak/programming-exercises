#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cti(char c) { return c - 'a'; }

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  string str;

  cin >> n;
  cin >> str;

  const int al = 'z' - 'a' + 1;
  vector<vector<int>> locc(al);
  for (int i = 0; i < n; i++) {
    locc[cti(str[i])].push_back(i);
  }

  int out = 0;
  for (int k = 0; k < al; k++) {
    for (int l = 0; l < al; l++) {
      if (k == l)
        continue;

      int mi = INT_MAX, sum = 0, res = 0, sum_pop = 0;
      int ki = 0, li = 0;
      while (true) {
        bool kDone = ki >= (int)locc[k].size();
        bool lDone = li >= (int)locc[l].size();
        if (kDone and lDone)
          break;
        while (!kDone and (lDone or locc[k][ki] < locc[l][li])) {
          sum++;
          res = max(res, sum - mi);

          ki++;
          kDone = ki >= (int)locc[k].size();
        }
        while (!lDone and (kDone or locc[l][li] < locc[k][ki])) {
          sum--;
          mi = min(mi, sum_pop);
          sum_pop = sum;
          res = max(res, sum - mi);

          li++;
          lDone = li >= (int)locc[l].size();
        }
      }
      out = max(out, res);
    }
  }
  cout << out << '\n';

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
  return 0;
}
#endif
