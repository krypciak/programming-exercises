#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
  ll value;
  int lastChanged;

  auto operator<=>(const Node &a) const {
    return lastChanged <=> a.lastChanged;
  }
};

struct Seg {
  vector<Node> t;
  int n;
  int changedCounter;

  Seg(vector<ll> &initial) {
    n = initial.size();
    t = vector<Node>(n*2);
    for (int i = n; i <n*2; i++) {
      t[i] = {initial[i-n], 0};
    }
    changedCounter = 1;
  }

  void set(int l, int r, ll v) {
    for (l += n, r += n; r > l; r >>= 1, l >>= 1) {
      if (l&1) t[l++] = {v, changedCounter};
      if (r&1) t[--r] = {v, changedCounter};
    }
    changedCounter++;
  }

  ll query(int p) {
    Node latest = {0, -1};
    for (p += n; p > 0; p >>= 1) {
      latest = max(latest, t[p]);
    }
    return latest.value;
  }

};

#ifdef TEST
int run(ifstream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<ll> initial(n);
  for (int i = 0; i < n; i++) cin >> initial[i];

  Seg seg(initial);

  while(m--) {
    int t;
    cin >> t;
    if (t == 1) {
      int i;
      cin >> i;
      i--;
      ll res = seg.query(i);
      cout << res << '\n';
    } else if (t == 2) {
      int l, r;
      cin >> l >> r;
      l--;
      ll v;
      cin >> v;
      seg.set(l, r, v);
    }
  }

  return 0;
}

#ifdef TEST
string rtrim(string s) {
  auto end = s.find_last_not_of(" \t\r\n\v\f");
  return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string expS, string outS) {
  if (expS == outS) {
    printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
  } else {
    printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n------got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
  }
}
void test(string name) {
  ifstream in(name+".in");
  ostringstream out;
  run(in, out);
  string outS = rtrim(out.str());

  ifstream exp(name+".out");
  string expS(istreambuf_iterator<char>{exp}, {});
  expS = rtrim(expS);

  printT(name, expS, outS);
}
int main() {
  test("ex0");
  test("ex1");
  return 0;
}
#endif
