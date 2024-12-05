#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int solve1(string inFile) {
  ifstream cin(inFile);

  multimap<int, int> befRules;

  string line;
  while (getline(cin, line) && line != "") {
    transform(begin(line), end(line), begin(line),
              [](char c) { return c == '|' ? ' ' : c; });
    stringstream ss(line);

    int bef, aft;
    ss >> bef >> aft;

    befRules.insert({bef, aft});
  }

  int sum = 0;

  int ite = 0;
  while (getline(cin, line)) {
    transform(begin(line), end(line), begin(line),
              [](char c) { return c == ',' ? ' ' : c; });
    stringstream ss(line);

    function<int()> check = [&]() {
      set<int> used;
      vector<int> history;
      int num;
      while (ss >> num) {
        auto befRange = befRules.equal_range(num);
        for (auto it = befRange.first; it != befRange.second; it++) {
          int aft = it->second;
          if (used.count(aft) > 0)
            return 0;
        }

        used.insert(num);
        history.push_back(num);
      }

      return history[(history.size() - 1) / 2];
    };

    sum += check();

    ite++;
    cout << ite << endl;
  }

  return sum;
}

int solve2(string inFile) {
  ifstream cin(inFile);

  multimap<int, int> befRules;

  string line;
  while (getline(cin, line) && line != "") {
    transform(begin(line), end(line), begin(line),
              [](char c) { return c == '|' ? ' ' : c; });
    stringstream ss(line);

    int bef, aft;
    ss >> bef >> aft;

    befRules.insert({bef, aft});
  }

  int sum = 0;

  while (getline(cin, line)) {
    transform(begin(line), end(line), begin(line),
              [](char c) { return c == ',' ? ' ' : c; });
    stringstream ss(line);

    function<int()> check = [&]() {
      vector<int> nums;
      int num;
      while (ss >> num) {
        nums.push_back(num);
      }

      bool failedAtSomePoint = false;
      set<int> used;
      for (int i = 0; i < (int)nums.size(); i++) {
        num = nums[i];

        auto befRange = befRules.equal_range(num);
        for (auto it = befRange.first; it != befRange.second; it++) {
          int aft = it->second;
          if (used.count(aft) > 0) {
            failedAtSomePoint = true;
            nums.erase(begin(nums) + i);
            i--;

            for (; i >= 0; i--) {
              if (nums[i] == aft) {
                nums.insert(begin(nums) + i, num);
                break;
              }
            }
            i = -1;
            used.clear();
            goto cont;
          }
        }

        used.insert(num);

      cont:
        if (false) {
        }
      }

      if (!failedAtSomePoint)
        return 0;

      return nums[(nums.size() - 1) / 2];
    };

    sum += check();
  }

  return sum;
}

int main() {
  // printf("solve1 ex0 (143 expected): %d\n", solve1("ex0"));
  // printf("solve1 in0: %d\n", solve1("in0"));
  // printf("solve2 ex0 (123 expected): %d\n", solve2("ex0"));
  // printf("solve2 in0 (6319 expected): %d\n", solve2("in0"));
  cout << solve1("bigboy.txt") << endl;
  return 0;
}
