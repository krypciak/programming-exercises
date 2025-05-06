#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
vector<int> kinds;
map<int, int> fr;

int getKind(int k) {
  if (fr.count(k) > 0) return fr[k];
  return k;
}

bool isOutOfRange(int l, int r, int k) {
  for (int i = 0; i < l; i++) 
    if (getKind(kinds[i]) == k) return true;
  for (int i = r+1; i < n; i++) 
    if (getKind(kinds[i]) == k) return true;
  return false;
}

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  cin >> n >> k;

  kinds = vector<int>(n);
  for (int i = 0; i < n; i++) cin >> kinds[i];

  fr = map<int, int>();

  vector<int> lastSeen(k+1, -1);
  for (int i = 0; i < n; i++) {
    int ck = getKind(kinds[i]);
    int lsi = lastSeen[ck];
    if (lsi == -1 || lsi == i-1) {
      lastSeen[ck] = i;
    } else {
      for (int j = lsi+1; j < i; j++) {
        int sk = getKind(kinds[j]);
        if (sk != ck && isOutOfRange(lsi, i, sk)) {
          // no matter how you slice it, it is entangled
          fr[sk] = ck;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    std::cout << getKind(kinds[i]) << " ";
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
    printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
  else
    printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: " "\n'%s'\n-----got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
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
