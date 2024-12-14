#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
using namespace std;

typedef unsigned char uc;

typedef unsigned long long ll;

const int MAX_DIGIT = 2000000;
const int ARR_SIZE = MAX_DIGIT * 2;
uc digits[ARR_SIZE];
uc digits1[ARR_SIZE];

int main(void) {
#ifdef DEBUG
  ifstream cin("tests/input1/zam0.in");
  signal(SIGINT, [](int signum) { exit(signum); });
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int end1 = 1;
  while (true) {
    int c = getchar();
    if (c == EOF || c == '\n')
      break;

    uc digit = c - '0';
    assert(digit >= 0 && digit < 10);
    digits[end1] = digit;
    digits1[end1] = digit;

    end1++;
  }

  auto optimal = [&]() {
    int start = 1;
    int end = 1;

    int digitsToAdd = 0;
    for (; end < end1; end++) {
      uc digit = digits[end];

      if (digit != 9) {
        digitsToAdd++;
      }
    }
    end--;

    int steps = 0;
    int addCount = 0;

    auto add = [&](int am) {
      int res = digits[end] + am;
      if (res < 10) {
        digits[end] = res;
        addCount++;
      } else {

        int addI = end;
        int carry = am;

        auto changeTo = [&](int i, int val) {
          if (val != digits[i]) {
            addCount++;
          }
          digits[i] = val;
        };

        while (true) {
          if (addI == start - 1) {
            start--;
            changeTo(start, carry);
            break;
          }
          int res = digits[addI] + carry;
          if (res < 10) {
            changeTo(addI, res);
            break;
          }

          changeTo(addI, res % 10);
          carry = res / 10;

          addI--;
        }
      }
      steps += am;
      // cout << "add: " << am << endl;
    };

    auto swap = [&]() {
      uc last = digits[start];
      start++;
      int removed = 0;
      while (digits[start] == 0 && start <= end) {
        start++;
        removed++;
      }
      end++;
      digits[end] = last;
      steps++;

      // cout << "swap" << endl;
      return removed;
    };

    auto isDone = [&]() { return (end - start) == 0 && digits[start] == 1; };

    if (start - end == 0 && digits[end] == 0)
      return 1llu;

    int bkpstart = start;
    int bkpend = end;
    int bkpdigitsToAdd = digitsToAdd;

    auto regSolve = [&]() {
      int swapsTmp = 0;
      while (!isDone()) {

        uc first = digits[end];
        if (first == 0) {
          addCount += swap();
          swapsTmp++;
        } else if (first == 9) {
          if (digitsToAdd == addCount) {
            add(1);
            swap();
            assert(isDone());
            continue;
          }
          addCount += swap();
          swapsTmp++;
        } else {
          uc toAdd = 9 - first;
          // cout << "swap " << swapsTmp << endl;
          swapsTmp = 0;
          // cout << "add " << (int)toAdd << endl;
          add(toAdd);
        }
      }
      return steps;
    };

    ll regSolveRes = regSolve();

    steps = 0;
    addCount = 0;
    start = bkpstart;
    end = bkpend;
    digitsToAdd = bkpdigitsToAdd;
    memcpy(digits, digits1, ARR_SIZE * sizeof(uc));

    auto rawSolve = [&]() {
      if (end - start > 7) {
        int lrdi = -1;
        for (int i = end; i >= end - 7; i--) {
          if (digits[i] != 9 && digits[i - 1] == 9 && digits[i - 2] == 9 &&
              digits[i - 3] == 9 && digits[i - 4] == 9 && digits[i - 5] == 9) {
            lrdi = i;
            break;
          }
        }
        if (lrdi != -1) {
          int luw = -1;
          for (int i = lrdi - 1; i >= start; i--) {
            if (digits[i] != 9) {
              luw = i;
              break;
            }
          }

          signed long long rc =
              (lrdi - start) - ((luw == -1 ? start : luw) - start);
          signed long long rawRc = 0;
          signed long long pow = 1;

          // if (digits[end] == 9) {
          //   rc++;
          // }

          bool wasPrevAll0 = true;
          bool wasPrevAll9 = true;
          for (int j = end; j >= lrdi; j--) {
            if (digits[j] == 0) {
              if (!wasPrevAll0)
                rc++;
            } else {
              wasPrevAll0 = false;
            }
            if (digits[j] == 9) {
              if (!wasPrevAll9)
                rc++;
            } else {
              wasPrevAll9 = false;
            }

            if (digits[j] != 0 && digits[j] != 9) {
              rc += 9 - digits[j] + 1;
            }
            rawRc += digits[j] * pow;
            pow *= 10;
          }
          // if (wasPrevAll0) {
          //   rc++;
          // }

          rawRc = pow - rawRc - 1;
          if (rawRc > 10000000) {
            return 10000000;
          }
          rc += 100;
          // printf("rawRc: %llu, rc: %llu\n", rawRc, rc);
          if (rawRc < rc) {
            add(rawRc);
          } else
            return 10000000;
        } else
          return 10000000;
      } else
        return 10000000;
      return regSolve();
    };

    ll rawSolveRes = rawSolve();

    return min(rawSolveRes, regSolveRes);
  };

  ll res = optimal();
  cout << res << endl;
  return 0;
}
