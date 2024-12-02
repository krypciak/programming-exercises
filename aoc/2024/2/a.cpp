#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <vector>
using namespace std;

typedef unsigned long long ll;

ll solve1(string inputFile) {
  ifstream cin(inputFile);

  ll sum = 0;
  while (true) {
    string line;
    if (!getline(cin, line))
      break;

    vector<int> list;
    int val;
    stringstream ss(line);
    while (ss >> val) {
      list.push_back(val);
    }

    function<bool(int, int)> cmp =
        (list[0] > list[1])
            ? ([](int a, int b) { return a > b && a - b <= 3; })
            : ([](int a, int b) { return a < b && b - a <= 3; });

    bool ok = true;
    for (size_t i = 1; i < list.size(); i++) {
      if (!cmp(list[i - 1], list[i])) {
        ok = false;
        break;
      }
    }
    sum += ok;
  }
  return sum;
}

ll solve2(string inputFile) {
  ifstream cin(inputFile);

  ll sum = 0;
  while (true) {
    string line;
    if (!getline(cin, line))
      break;

    vector<int> list;
    int val;
    stringstream ss(line);
    while (ss >> val) {
      list.push_back(val);
    }

    auto checkAll = [&list]() {
      auto check = [](vector<int> list, int remove) {
        if (remove >= 0) {
          list.erase(begin(list) + remove);
        }

        function<bool(int, int)> cmp =
            (list[0] > list[list.size() - 1])
                ? ([](int a, int b) { return a > b && a - b <= 3; })
                : ([](int a, int b) { return a < b && b - a <= 3; });

        for (int i = 1; i < (int)list.size(); i++) {
          if (!cmp(list[i - 1], list[i])) {
            return false;
          }
        }
        return true;
      };

      for (int remove = -1; remove < (int)list.size(); remove++) {
        if (check(list, remove)) {
          return true;
        }
      }
      return false;
    };

    sum += checkAll();
  }
  return sum;
}

void test(string inputFile, int expected, function<ll(string)> func) {
  int res = func(inputFile);
  if (res != expected) {
    printf("%s fail! expected %d, got %d\n", inputFile.c_str(), expected, res);
  }
}
int main() {
  test("ex0", 2, solve1);
  printf("solve1, %lld\n", solve1("in0"));
  test("ex0", 4, solve2);
  printf("solve2, %lld\n", solve2("in0"));
  return 0;
}
