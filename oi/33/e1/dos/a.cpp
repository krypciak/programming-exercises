#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
  int n;
  vector<int> d;
  vector<int> l;

  Seg(int n) : n(n), d(n*2), l(n) {}

private:
  void apply(int p, int v) {
    d[p] += v;
    if (n > p) l[p] += v;
  }

  void push(int p0) {
    int h = sizeof(p0)*8 - countl_zero((unsigned int)p0);
    for (int i = h-1; i >= 1; i--) {
      int p = p0 >> i;
      if (l[p] != 0) {
        apply(p<<1, l[p]);
        apply(p<<1|1, l[p]);
        l[p] = 0;
      }
    }
  }

  void build(int p) {
    while (p > 1) {
      p >>= 1;
      d[p] = max(d[p<<1], d[p<<1|1]) + l[p];
    }
  }

  void incRange(int l, int r, int v) {
    l += n, r += n;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) apply(l++, v);
      if (r&1) apply(--r, v);
    }
    build(l0);
    build(r0-1);
  }

public:

  void incToEnd(int p, int v) {
    incRange(0, p+1, v);
  }

  void inc(int p, int v) {
    p += n;
    push(p);
    d[p] += v;
    build(p);
  }

  int maxOnWhole() {
    return d[1];
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, q;
  cin >> n >> q;

  vector<vector<char>> map(n+2, vector<char>(n+2));
  for (int y = 1; y <= n; y++) for (int x = 1; x <= n; x++) cin >> map[y][x];
  for (int i = 0; i < n+2; i++) map[i][0] = map[i][n+1] = map[0][i] = map[n+1][i] = '#';

  vector<vector<int>> distMap(n+2, vector<int>(n+2, 0));
  vector<vector<int>> fortMap(n+2, vector<int>(n+2, {-1}));

  vector<int> fortCounts(n*n, 0);
  Seg seg(n*n);
  auto insertFort = [&](int x, int y) {
      int dist = distMap[y][x];
      fortMap[y][x] = dist;

      if (fortCounts[dist]++ == 0) {
        seg.inc(dist, dist);
        seg.incToEnd(dist-1, 1);
      } else {
        seg.incToEnd(dist, 1);
      }
  };
  auto deleteFort = [&](int x, int y) {
      int dist = fortMap[y][x];
      fortMap[y][x] = {-1};

      seg.incToEnd(dist, -1);
      if (--fortCounts[dist] == 0) {
        seg.inc(dist, -dist+1);
      }
  };

  {
    vector<pair<int, int>> toVisit{{1, 1}};
    vector<vector<char>> visited(n+2, vector<char>(n+2, false));
    for (int dist = 0; toVisit.size(); dist++) {
      vector<pair<int, int>> nextToVisit;
      nextToVisit.reserve(toVisit.size()*4);
      for (auto [x, y] : toVisit) {
        for (auto [ax, ay] : {pair<int,int>{0, 1}, {0, -1}, {1, 0}, {-1, 0}}) {
          int nx = x + ax;
          int ny = y + ay;
          if (visited[ny][nx]) continue;
          visited[ny][nx] = true;

          char c = map[ny][nx];
          if (c == '#') continue;
          distMap[ny][nx] = dist+1;

          if (c == 'F') insertFort(nx, ny);

          nextToVisit.push_back({nx, ny});
        }
      }
      toVisit = nextToVisit;
    }
  }

  q++;
  while(q--) {
    int cost = seg.maxOnWhole();
    cout << cost << '\n';

    if (q == 0) continue;
    int x, y;
    cin >> y >> x;
    if (fortMap[y][x] == -1) {
      insertFort(x, y);
    } else {
      deleteFort(x, y);
    }
  }

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
  test("ex0");
  test("dos0a");
  test("dos0b");
  test("dos0c");
  // for (int i = 1; i <= 20; i++) test(format("net0/bardzo_male/{}", i), i % 1000 == 0);

  #ifdef ALLTESTS
  for (int i = 1; i <= 8000; i++) test(format("net0/bardzo_male/{}", i), i % 1000 == 0);
  for (int i = 1; i <= 4000; i++) test(format("net0/male/{}", i), i % 1000 == 0);
  for (int i = 1; i <= 1000; i++) test(format("net0/podzadanie2/{}", i), i % 200 == 0);
  for (int i = 1; i <= 1000; i++) test(format("net0/duze/{}", i), i % 200 == 0);
  for (int i = 1; i <= 1000; i++) test(format("net0/duze/{}", i), i % 200 == 0);
  for (int i = 1; i <= 303; i++) test(format("net0/max/{}", i), i % 50 == 0);
  #endif
  return 0;
}
#endif
