#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define print

pair<map<int, int>, int> factors(int n) {
  int facCount = 0;
  int x = n;
  map<int, int> fac;
  int count = 0;
  while ((x & 1) == 0) {
    count++;
    x /= 2;
  }
  if (count > 0) {
    fac[2] = count;
    facCount += count;
  }

  for (int i = 3; x > 1; i += 2) {
    count = 0;
    while (x % i == 0) {
      count++;
      x /= i;
    }
    if (count > 0) {
      fac[i] = count;
      facCount += count;
    }
  }

  return {fac, facCount};
}

ll recMulCost(const int c, const vector<ll> &costs, map<int, int> nums,
              const int count, const int n) {
  ll minCost = -c;
  for (auto [v, count] : nums) {
    minCost += (costs[v] + c) * count;
  }

  if (count >= 3) {
    for (auto ite1 = nums.begin(); ite1 != nums.end(); ite1++) {
      auto [a, acount] = *ite1;
      if (acount <= 0)
        continue;

      auto ite2 = ite1;
      for (; ite2 != nums.end(); ite2++) {
        auto [b, bcount] = *ite2;
        if (a == b) {
          if (bcount <= 1)
            continue;
        } else {
          if (bcount <= 0)
            continue;
        }
        print("n = {}, {} * {}\n", n, a, b);
        auto newNums = nums;

        newNums[b]--;
        newNums[a]--;
        ll mul = a * b;
        assert(mul < n);
        newNums[mul]++;

        ll cost = recMulCost(c, costs, std::move(newNums), count - 1, n);
        minCost = min(minCost, cost);
      }
    }
  }

  return minCost;
}


int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, a, b, c;
  cin >> n >> a >> b >> c;

  vector<ll> costs(n + 1);
  costs[1] = a;
  cout << costs[1] << ' ';

  for (int k = 2; k <= n; k++) {
    print("n = {}\n", k);
    ll minCost = (ll)1 << 62;
    for (int l = k - 1, r = 1; l >= r; l--, r++) {
      ll cost = costs[l] + costs[r] + b;
      print("l: {}, r: {}, cost: {}\n", l, r, cost);
      minCost = min(minCost, cost);
    }

    auto [fac, facCount] = factors(k);
    // for (auto [v, count] : fac)
    //   print("{} x{}, ", v, count);
    // print("\n");

    if (facCount >= 2) {
      ll mulCost = recMulCost(c, costs, fac, facCount, k);
      minCost = min(minCost, mulCost);
    }
    print("\n");

    costs[k] = minCost;
    cout << minCost << ' ';
  }
  cout << '\n';

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("wyr0a");
  test("wyr0b");
  test("wyr0c");
  test("wyr0d");
  return 0;
}
#endif
