#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

typedef unsigned long long ll;

struct Vec2 {
  int x, y;
};

ll solve1(string fileName, bool part2) {
  fstream cin(fileName);

  vector<ll> origNums;
  ll num;
  while (cin >> num) {
    origNums.push_back(num);
  }

  auto numLen = [](ll a) {
    double manLog = log10(a);
    return ceil(manLog) + (((int)manLog == manLog) ? 1 : 0);
  };

  const int iteCount = part2 ? 76 : 26;

  const int memRepSize = 100;
  const int repSize = memRepSize + 1;
  auto fast = [iteCount, repSize, origNums, numLen]() {
    vector<vector<vector<int>>> repeat(
        repSize, vector<vector<int>>(repSize, vector<int>(iteCount, 0)));

    vector<vector<ll>> nums(repSize);
    for (int i = 0; i < memRepSize; i++) {
      nums[i].push_back(i);
    }

    nums[memRepSize] = origNums;

    vector<vector<ll>> hist(repSize, vector<ll>(iteCount));
    for (int i = 0; i < iteCount; i++) {
      for (int k = 0; k < repSize; k++) {
        hist[k][i] = nums[k].size();
        vector<ll> numsNext;

        for (ll num : nums[k]) {
          if (num < memRepSize && i != 0) {
            repeat[k][num][i]++;
            hist[k][i]--;
            continue;
          }
          vector<ll> newNums;
          if (num == 0) {
            numsNext.push_back(1);
          } else {
            int len = numLen(num);
            if (len % 2 == 0) {
              ll power = pow(10, len / 2);
              numsNext.push_back(num / power);
              numsNext.push_back(num % power);
            } else {
              numsNext.push_back(num * 2024);
            }
          }
        }
        nums[k] = numsNext;
      }
    }

    for (int i = 1; i < iteCount; i++) {
      for (int k = 0; k < repSize; k++) {
        ll sum = 0;

        for (int u = 0; u < repSize; u++) {
          for (int j = 1; j <= i; j++) {
            int rep = repeat[k][u][j];
            if (rep == 0)
              continue;

            sum += rep * hist[u][i - j];
          }
        }

        hist[k][i] += sum;
      }
    }
    return hist[memRepSize][iteCount - 1];
  };

  return fast();
}

int main() {
  printf("solve1 ex0 (55312 expected): %llu\n", solve1("ex0", false));
  printf("solve1 in0 (194557 expected): %llu\n", solve1("in0", false));
  printf("solve2 ex0 (65601038650482 expected): %llu\n", solve1("ex0", true));
  printf("solve2 in0 (231532558973909 expected): %llu\n", solve1("in0", true));
  // printf("solve1 bigboy.txt ( expected): %llu\n", solve1("bigboy.txt"));
  // printf("solve2 bigboy.txt ( expected): %llu\n", solve2("bigboy.txt"));
  return 0;
}
