#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

typedef long long ll;

const inline bool doesMulOverflow(ll a, ll b, ll c) { return a > c / b; }

ll solve(string file, bool part2) {
  ifstream cin(file);

  ll sum = 0;

  string line;
  while (getline(cin, line)) {
    line[line.find(':')] = ' ';
    stringstream ss(line);

    ll finalEq;
    ss >> finalEq;

    vector<ll> nums;
    ll next;
    while (ss >> next) {
      nums.push_back(next);
    }

    function<ll(ll, ll)> concLongs = [](ll a, ll b) {
      double manLog = log10(b);
      int lag = ceil(manLog) + (((int)manLog == manLog) ? 1 : 0);

      return a * pow(10, lag) + b;
    };

    auto check = [&]() {
      vector<ll> toVisit;
      toVisit.push_back(nums[0] + nums[1]);
      toVisit.push_back(nums[0] * nums[1]);
      if (part2)
        toVisit.push_back(concLongs(nums[0], nums[1]));

      for (size_t pos = 2; pos < nums.size(); pos++) {
        vector<ll> nextToVisit;
        for (ll sum : toVisit) {
          ll add = sum + nums[pos];
          assert(add > 0);
          if (add <= finalEq) {
            nextToVisit.push_back(add);
          }

          ll mul = sum * nums[pos];
          assert(!doesMulOverflow(sum, nums[pos], mul));
          assert(mul > 0);
          if (mul <= finalEq) {
            nextToVisit.push_back(mul);
          }

          if (part2) {
            ll conc = concLongs(sum, nums[pos]);
            assert(conc > 0);

            if (conc <= finalEq) {
              nextToVisit.push_back(conc);
            }
          }
        }
        toVisit = nextToVisit;
      }

      auto found = find(begin(toVisit), end(toVisit), finalEq);
      return found == end(toVisit) ? 0 : *found;
    };

    sum += check();
  }
  return sum;
}

int main() {
  printf("solve1 ex0 (3749 expected): %lld\n", solve("ex0", false));
  printf("solve1 in0 (20281182715321 expected): %lld\n", solve("in0", false));
  printf("solve2 ex0 (11387 expected): %lld\n", solve("ex0", true));
  printf("solve2 in0 (159490400628354 expected): %lld\n", solve("in0", true));
  return 0;
}
