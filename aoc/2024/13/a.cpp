#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
using namespace std;

typedef long long ll;

ll solve1(string fileName, bool part2) {
  fstream cin(fileName);

  struct Game {
    ll ax, ay;
    ll bx, by;
    ll px, py;
  };
  string line;

  vector<Game> games;
  while (true) {
    vector<pair<ll, ll>> nums;
    for (int i = 0; i < 3; i++) {

      getline(cin, line);
      transform(begin(line), end(line), begin(line),
                [](char c) { return c >= '0' && c <= '9' ? c : ' '; });
      stringstream ss(line);

      ll a, b;
      ss >> a >> b;
      nums.push_back({a, b});
    }

    if (part2) {
      nums[2].first += 10000000000000;
      nums[2].second += 10000000000000;
    }

    games.push_back({nums[0].first, nums[0].second, nums[1].first,
                     nums[1].second, nums[2].first, nums[2].second});

    if (!getline(cin, line))
      break;
  }

  ll sum = 0;

  for (auto [ax, ay, bx, by, px, py] : games) {
    ll blhs = px * ay - py * ax;
    ll brhs = bx * ay - by * ax;
    if (blhs % brhs != 0)
      continue;
    ll b = blhs / (brhs);

    ll alhs = px - b * bx;
    ll arhs = ax;
    if (alhs % arhs != 0)
      continue;
    ll a = alhs / arhs;

    sum += b + a * 3;
  }

  return sum;
}

int main() {
  printf("solve1 ex0 (480 expected): %llu\n", solve1("ex0", false));
  printf("solve1 in0 (26599 expected): %llu\n", solve1("in0", false));
  printf("solve2 ex0 (875318608908 expected): %llu\n", solve1("ex0", true));
  printf("solve2 in0 (106228669504887 expected): %llu\n", solve1("in0", true));
  return 0;
}
