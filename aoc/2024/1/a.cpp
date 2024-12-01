#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <vector>
using namespace std;

typedef unsigned long long ll;

ll solve1(string inputFile) {
  ifstream cin(inputFile);

  vector<int> v1;
  vector<int> v2;
  while (true) {
    int n1, n2;
    if (!(cin >> n1 >> n2)) {
      break;
    };
    v1.push_back(n1);
    v2.push_back(n2);
  }

  sort(begin(v1), end(v1));
  sort(begin(v2), end(v2));

  ll sum = 0;
  for (size_t i = 0; i < v1.size(); i++) {
    sum += abs(v1[i] - v2[i]);
  }

  return sum;
}

ll solve2(string inputFile) {
  ifstream cin(inputFile);

  vector<int> v1;
  multiset<int> v2;
  while (true) {
    int n1, n2;
    if (!(cin >> n1 >> n2)) {
      break;
    };
    v1.push_back(n1);
    v2.insert(n2);
  }

  ll sum = 0;
  for (ll num : v1) {
    int c2 = v2.count(num);

    sum += num * c2;
  }

  return sum;
}

void test(string inputFile, int expected, function<ll(string)> func) {
  int res = func("ex0");
  if (res != expected) {
    printf("ex0 fail! expected %d, got %d\n", expected, res);
  }
}
int main() {
  test("ex0", 11, solve1);
  printf("solve1, %lld\n", solve1("in0"));
  test("ex0", 31, solve2);
  printf("solve2, %lld\n", solve2("in0"));
  return 0;
}
