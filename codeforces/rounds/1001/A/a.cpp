#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);
  typedef long long ll;

  int q;
  cin >> q;
  while (q--) {
    string seq;
    cin >> seq;

    int sum = 0;
    for (char c : seq)
      if (c == '1')
        sum++;
    cout << sum << '\n';
  }

  return 0;
}
#ifdef TEST
string rtrim(string s) {
  auto end = s.find_last_not_of(" \t\r\v\f\n");
  return end == string::npos ? s : s.substr(0, end + 1);
}
void printT(string name, string outS, string expS) {
  if (outS == expS) {
    printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n",
           name.c_str());
  } else {
    printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: "
           "\n'%s'\n---got: \n'%s'\n\n",
           name.c_str(), expS.c_str(), outS.c_str());
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
