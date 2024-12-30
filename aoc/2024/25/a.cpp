#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

template <> struct std::formatter<vector<int>> {
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

  auto format(const vector<int> &v, format_context &ctx) const {
    for (int i = 0; i < (int)v.size(); i++) {
      format_to(ctx.out(), "{}", v[i]);
      if (i < (int)v.size() - 1) {
        format_to(ctx.out(), ",");
      }
    }
    return format_to(ctx.out(), "");
  }
};

ll solve1(string inputFile) {
  ifstream cin(inputFile);

  vector<vector<int>> locks;
  vector<vector<int>> keys;

  const int keyw = 5;
  const int keyh = 5;
  string line;
  while (getline(cin, line)) {
    bool isLock = line == string(keyw, '#');

    vector<int> heights(keyh, 0);
    for (int i = 0; i < keyh; i++) {
      getline(cin, line);
      assert(line.size() == keyw);
      for (int j = 0; j < keyw; j++) {
        if (line[j] == '#') {
          heights[j]++;
        }
      }
    }

    // print("isLock: {}\n", isLock);
    // print("{}\n", heights);

    if (isLock) {
      locks.push_back(std::move(heights));
    } else {
      keys.push_back(std::move(heights));
    }
    getline(cin, line);
    getline(cin, line);
    assert(line == "");
  }

  ll sum = locks.size() * keys.size();
  for (const vector<int> &lock : locks) {
    for (const vector<int> &key : keys) {
      for (int i = 0; i < keyw; i++) {
        if (lock[i] + key[i] > 5) {
          // print("does not fit in: lock: {}, key: {}, at {}\n", lock, key, i);
          sum--;
          break;
        }
      }
    }
  }

  return sum;
}

int main() {
  // clang-format off
  print("solve1 ex0 (3 expected): {}\n", solve1("ex0"));
  print("solve1 in0 ( expected): {}\n", solve1("in0"));
  // clang-format on
  return 0;
}
