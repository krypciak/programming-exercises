#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

typedef long long ll;

string run(istream &cin = std::cin) {
  int n;
  cin >> n;

  string line;
  getline(cin, line);
  getline(cin, line);

  const int s = line.size();
  for (int i = 0; i < (s + 1) / 2; i++) {
    if ((line[i] == '6' && line[s - i - 1] == '9') ||
        (line[i] == '9' && line[s - i - 1] == '6'))
      continue;

    if (line[i] != line[s - i - 1] || line[i] == '4' || line[i] == '7')
      return "NIE";
  }

  return "TAK";
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
  sub(R"(2
22)",
      "TAK");

  sub(R"(3
343)",
      "NIE");

  sub(R"(3
012)",
      "NIE");

  sub(R"(3
515)",
      "TAK");

  sub(R"(3
639)",
      "TAK");
}

int main() {
#ifdef DEBUG
  test();
#else
  cout << run() << endl;
#endif
  return 0;
}
