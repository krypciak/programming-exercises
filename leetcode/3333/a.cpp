#include <bits/stdc++.h>
using namespace std;

typedef __int128 uint128;
class Solution {
public:
  char kthCharacter(long long k, vector<int>& operations) {
    int offset = 0;
    for (int i = 63 - __builtin_clzll((unsigned long long)k); i >= 0; i--) {
      long long half = (long long) 1 << i;
      if (k > half) {
        k -= half;
        if (operations[i]) offset++;
      }
    }

    return 'a' + (offset % 26);
  }
};

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  long long k;
  cin >> k;

  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  Solution sol;
  cout << sol.kthCharacter(k, v) << endl;

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
  test("ex1");
  test("ex2");
  return 0;
}
#endif
