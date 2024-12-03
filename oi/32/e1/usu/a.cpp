#include <cstdio>
#include <iostream>
using namespace std;

typedef unsigned long long ll;

ll smart(ll a, ll b) {

  ll len = b - a + 1;

  ll stage = len % 4;
  ll out;
  if (stage == 1) {
    out = len - 1;
  } else if (stage == 2) {
    out = len - 2;
  } else if (stage == 3) {
    out = len - 1;
  } else if (stage == 0) {
    out = len;
  }
  return out;
}

int main(void) {
  ll a, b;
  cin >> a >> b;

  ll out = smart(a, b);
  cout << out << endl;

  return 0;
}
