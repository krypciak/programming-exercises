#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
  ll a;
  ll b;
  int nl;

  ll calc(int l) {
    return a * (l-nl) + b;
  }

  void merge(int l, ll na, ll nb) {
    ll naDiff = (nl - l) * na;
    b += nb + naDiff;
    a += na;
  }
};

struct Seg {
  int n;
  vector<Node> t;

  Seg(vector<ll> &initial) : n(initial.size()), t(n*2) {
    for (int i = 0; i < n; i++) t[i+n] = {0, initial[i], i-n};
    
    for (int i = n-1; i > 0; i--) t[i] = {0, 0, t[i<<1].nl};
    
  }

  void add(int lo, int ro, ll a, ll b) {
    for (int l = lo+n, r = ro+n; r > l; r >>= 1, l >>= 1) {
      if (l&1) t[l++].merge(lo, a, b);
      if (r&1) t[--r].merge(lo, a, b);
    }
  }

  ll query(int i) {
    ll sum = 0;
    for (int p = n+i; p > 0; p >>= 1) 
      sum += t[p].calc(i);
    
    return sum;
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
      ll b, a;
      cin >> b >> a;
      seg.add(l, r, a, b);
    } else assert(false);
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
  test("ex3");
  test("ex2");
  test("ex0");
  test("ex1");
  return 0;
}
#endif
