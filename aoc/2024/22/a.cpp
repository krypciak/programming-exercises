#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

struct Vec2 {
  int x, y;

  bool operator==(const Vec2 &a) const { return x == a.x && y == a.y; }
};

typedef unsigned long long ll;

ll solve1(string inputFile) {
  ifstream cin(inputFile);

  vector<string> inp;
  string line;
  while (getline(cin, line)) {
    inp.push_back(line);
  }

  auto nextNum = [](ll v) {
    v = (v << 6) xor v;
    v = v & ((1 << 24) - 1);

    v = (v >> 5) xor v;
    v = v & ((1 << 24) - 1);

    v = (v << 11) xor v;
    v = v & ((1 << 24) - 1);

    return v;
  };

  ll sum = 0;
  for (string line : inp) {
    ll val = stol(line);
    for (int i = 0; i < 2000; i++) {
      val = nextNum(val);
    }

    sum += val;
  }

  return sum;
}

ll solve2(string inputFile) {
  ifstream cin(inputFile);

  vector<string> inp;
  string line;
  while (getline(cin, line)) {
    inp.push_back(line);
  }

  auto nextNum = [](ll v) {
    v = (v << 6) xor v;
    v = v & ((1 << 24) - 1);

    v = (v >> 5) xor v;
    v = v & ((1 << 24) - 1);

    v = (v << 11) xor v;
    v = v & ((1 << 24) - 1);

    return v;
  };

  vector<unordered_map<int, int>> hashToBanana(inp.size());

  unordered_set<int> hashesToCheck;

  for (int j = 0; j < (int)inp.size(); j++) {
    string line = inp[j];
    ll origVal = stol(line);
    ll val = origVal;

    const int add = 9;
    const int bitSpace = 5;
    const int bitSpaceMod = 1 << bitSpace;
    int hash =
        (add << bitSpace * 3) + (add << bitSpace * 2) + (add << bitSpace) + add;

    int lastNum = (to_string(origVal)[to_string(origVal).size() - 1] - '0');
    for (int i = 0; i < 2000; i++) {
      val = nextNum(val);
      string str = to_string(val);
      int num = str[str.size() - 1] - '0';
      assert(num >= 0 && num <= 9);

      int diff = num - lastNum;
      assert(diff >= -9 && diff <= 9);
      lastNum = num;
      // print("num: {}, diff: {}\n", num, diff);

      if (i >= 0 && i <= 2) {
        hash = hash << bitSpace;
        hash += diff + add;
      } else {
        hash = hash << bitSpace;
        hash = hash & ((1 << bitSpace * 4) - 1);
        hash += diff + add;

        if (hashToBanana[j].count(hash) == 0) {
          hashToBanana[j].insert({hash, num});
          hashesToCheck.insert(hash);
        }
        int d1 = (hash >> bitSpace * 3) % bitSpaceMod - add;
        int d2 = (hash >> bitSpace * 2) % bitSpaceMod - add;
        int d3 = (hash >> bitSpace) % bitSpaceMod - add;
        int d4 = hash % bitSpaceMod - add;
        // print("seq: {} {} {} {}\n", d1, d2, d3, d4);
        assert(d1 >= -9 && d1 <= 9);
        assert(d2 >= -9 && d2 <= 9);
        assert(d3 >= -9 && d3 <= 9);
        assert(d4 >= -9 && d4 <= 9);
      }
    }
  }

  ll mostBananas = 0;
  // print("hashesToCheck: {}, inp size: {}\n", hashesToCheck.size(),
  // inp.size());
  for (int hash : hashesToCheck) {
    ll bananas = 0;

    for (int j = 0; j < (int)inp.size(); j++) {
      if (hashToBanana[j].count(hash) == 0) {
        continue;
      }
      bananas += hashToBanana[j][hash];
    }

    if (bananas > mostBananas) {
      mostBananas = bananas;
    }
  }

  return mostBananas;
}
int main() {
  // clang-format off
  printf("solve1 ex0 (37327623 expected): %llu\n", solve1("ex0"));
  printf("solve1 in0 (17612566393 expected): %llu\n", solve1("in0"));

  printf("solve2 ex1 (23 expected): %llu\n", solve2("ex1"));
  printf("solve2 in0 (1968 expected): %llu\n", solve2("in0"));
  // clang-format on
  return 0;
}
