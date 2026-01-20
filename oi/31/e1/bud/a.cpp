#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Pr {
  bool flat;
  int x, y;
};

bool doesOverlap(int size, Pr &r1, Pr &r2) {
  if (r1.flat == r2.flat) {
    if (r1.flat) {
      return r1.y == r2.y && r1.x < r2.x + size && r1.x + size > r2.x;
    } else {
      return r1.x == r2.x && r1.y < r2.y + size && r1.y + size > r2.y;
    }
  } else {
    if (r1.flat) {
      return r2.x >= r1.x && r2.x < r1.x + size && r1.y >= r2.y && r1.y < r2.y + size;
    } else {
      return r1.x >= r2.x && r1.x < r2.x + size && r2.y >= r1.y && r2.y < r1.y + size;
    }
  }
}
bool doesFit(int size, vector<Pr> &prs) {
  const int len = prs.size();
  for (int r1i = 0; r1i < len; r1i++) {
    for (int r2i = 0; r2i < len; r2i++) {
      if (r1i == r2i) continue;
      if (!doesOverlap(size, prs[r1i], prs[r2i])) return true;
    }
  }
  return false;
}

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector<vector<char>> grid(n, vector<char>(n, false));
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < n; x++) {
      char c;
      cin >> c;
      grid[y][x] = c == 'X' ? true : false;
    }
  }

  // how does this solution even work??? i have no clue
  vector<vector<Pr>> prs(n);

  int noAddOffset = 0;
  const uint stopAfter = n * 2;
  const int checkEvery = 10;
  int checkI = 0;

  for (int y = 0; y < n; y++) {
    for (int x = n - 1; x >= 0; x--) {
      int prevX = x;
      for (; x >= 0; x--) {
        if (grid[y][x]) break;
        for (int tx = x; tx <= prevX - noAddOffset; tx++) {
          prs[prevX - tx].push_back({true, x, y});
        }

        checkI++;
        if (checkI > checkEvery) {
          checkI = 0;
          for (int i = noAddOffset; i < n; i++) {
            if (prs[i].size() >= stopAfter) {
              noAddOffset++;
            } else
              break;
          }
        }
      }
    }
  }

  for (int x = 0; x < n; x++) {
    for (int y = n - 1; y >= 0; y--) {
      int prevY = y;
      for (; y >= 0; y--) {
        if (grid[y][x]) break;
        for (int ty = y; ty < prevY - noAddOffset; ty++) {
          prs[prevY - ty].push_back({false, x, y});
        }

        checkI++;
        if (checkI > checkEvery) {
          checkI = 0;
          for (int i = noAddOffset; i < n; i++) {
            if (prs[i].size() >= stopAfter) {
              noAddOffset++;
            } else break;
          }
        }
      }
    }
  }

  auto solve = [&]() {
    if (m == 1) {
      for (int i = n - 1; i >= 0; i--) {
        if (prs[i].size() >= 1) return i+1;
      }
      return 0;
    }

    for (int i = n - 1; i >= 0; i--) {
      if (prs[i].size() >= 2 && doesFit(i + 1, prs[i])) return i+1;
    }
    return 0;
  };
  cout << solve() << '\n';

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex4");
  test("ex0");
  test("ex1");
  test("ex2");
  test("ex3");
  return 0;
}
#endif
