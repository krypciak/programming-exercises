#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

typedef long long ll;

string run(istream &cin = std::cin) {
  int n;
  cin >> n;

  string out = "";
  string line;
  assert(getline(cin, line));
  for (int i = 0; i < n; i++) {
    assert(getline(cin, line));
    out = out + line[0];
  }

  return out;
}

void test() {
  int testId = 0;
  auto sub = [&testId](string in, string out) {
    stringstream ss(in);
    string res = run(ss);
    transform(begin(res), end(res), begin(res),
              [](char c) { return c == '\n' ? ' ' : c; });
    transform(begin(in), end(in), begin(in),
              [](char c) { return c == '\n' ? ' ' : c; });

    if (res != out) {
      printf("test %d fail: '%s' expected '%s', got '", testId, in.c_str(),
             out.c_str());
      cout << res << "'" << endl;
    } else {
      printf("test %d success\n", testId);
    }
    testId++;
  };
  sub(R"(4
Mistrz
Programowania
runda
pierwsza)",
      "MPrp");
  sub(R"(1
qwerty)",
      "q");
}

int main() {
#ifdef TEST
  test();
#else
  cout << run() << endl;
#endif
  return 0;
}
