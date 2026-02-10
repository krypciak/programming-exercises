#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;

#pragma GCC optimize("O3,unroll-loops")


struct Entry {
  uint a, b, c;
};

// all this custom writing business is unnecessary, this is just for fun
#ifndef TEST
char out[1<<22];
char *ptr = out;

void write_uint(uint x) {
  char buf[10];
  uint n = 0;
  do {
    buf[n++] = '0' + x % 10;
    x /= 10;
  } while (x);
  while (n--) *ptr++ = buf[n];
};
#endif

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  uint p, q, n;
  cin >> p >> q >> n;

  if (p > q) swap(p, q);

  vector<char> arr(n+p+q+1);

  array<Entry, 500'000> moves;
  uint moveI = 0;

  for (uint i = 1; i <= n; i++) {
    if (arr[i]) continue;

    uint b = i+p;
    const uint c = b+q;
    arr[c] = true;

    if (arr[b]) b = i+q;
    arr[b] = true;
    moves[moveI++] = {i, b, c};
  }


  #ifndef TEST
  write_uint(moveI);
  *ptr++ = '\n';
  for (uint i = 0; i < moveI; i++) {
    const Entry &m = moves[i];
    write_uint(m.a); *ptr++ = ' ';
    write_uint(m.b); *ptr++ = ' ';
    write_uint(m.c); *ptr++ = '\n';
  }
  fwrite(out, 1, ptr - out, stdout);
  #else
  cout << moveI << '\n';
  for (uint i = 0; i < moveI; i++) cout << moves[i].a << ' ' << moves[i].b << ' ' << moves[i].c << '\n';
  #endif

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex0");
  return 0;
}
#endif
