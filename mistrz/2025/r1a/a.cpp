#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

typedef long long ll;

ll run(istream &cin) {
  ll a;
  cin >> a;
  return a * 60;
}

void test() {
  int testId = 0;
  auto sub = [&testId](string in, ll out) {
    stringstream ss(in);
    ll res = run(ss);
    if (res != out) {
      printf("test %d fail: '%s' expected '%llu', got '%llu'\n", testId,
             in.c_str(), out, res);
    } else {
      printf("test %d success\n", testId);
    }
    testId++;
  };
  sub("3", 180);
  sub("0", 0);
}

int main() {
#ifdef DEBUG
  test();
#else
  cout << run(cin) << endl;
#endif
  return 0;
}
