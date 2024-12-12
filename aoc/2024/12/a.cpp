#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

typedef unsigned long long ll;

struct Vec2 {
  int x, y;

  bool operator==(const Vec2 &v) const { return x == v.x && y == v.y; }
  struct Hash {
    size_t operator()(const Vec2 &vec) const { return vec.x + vec.y * 100000; }
  };
};

ll solve1(string fileName) {
  fstream cin(fileName);

  vector<string> lines;
  string line;
  while (getline(cin, line)) {
    lines.push_back(line);
  }
  int w = lines[0].size();
  int h = lines.size();

  ll sum = 0;

  vector<vector<bool>> bfs(h, vector<bool>(w, false));

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if (bfs[y][x])
        continue;

      char c = lines[y][x];
      vector<Vec2> toVisit;
      toVisit.push_back({x, y});
      bfs[y][x] = true;

      int area = 0;
      int per = 0;
      while (toVisit.size() > 0) {
        vector<Vec2> nextToVisit;

        auto check = [&](int x, int y) {
          if (x < 0 || x >= w || y < 0 || y >= h) {
            per++;
            return;
          }

          if (lines[y][x] != c) {
            per++;
            return;
          }
          if (bfs[y][x])
            return;

          nextToVisit.push_back({x, y});
          bfs[y][x] = true;
        };

        for (Vec2 pos : toVisit) {
          area++;
          check(pos.x + 1, pos.y);
          check(pos.x - 1, pos.y);
          check(pos.x, pos.y + 1);
          check(pos.x, pos.y - 1);
        }

        toVisit = nextToVisit;
      }
      // printf("char: %c area: %d * per: %d = %d\n", c, area, per, area * per);
      sum += area * per;
    }
  }

  return sum;
}

ll solve2(string fileName) {
  fstream cin(fileName);

  vector<string> lines;
  string line;
  while (getline(cin, line)) {
    lines.push_back(line);
  }
  int w = lines[0].size();
  int h = lines.size();

  ll sum = 0;

  vector<vector<bool>> bfs(h, vector<bool>(w, false));

  for (int findY = 0; findY < h; findY++) {
    for (int findX = 0; findX < w; findX++) {
      if (bfs[findY][findX])
        continue;

      char c = lines[findY][findX];
      vector<Vec2> toVisit;
      toVisit.push_back({findX, findY});
      bfs[findY][findX] = true;

      vector<Vec2> borders;
      vector<vector<bool>> bg(h + 2, vector<bool>(w + 2, false));
      vector<vector<bool>> lb(h + 2, vector<bool>(w + 2, false));
      lb[findY + 1][findX + 1] = true;

      int area = 0;
      while (toVisit.size() > 0) {
        vector<Vec2> nextToVisit;

        auto check = [&](int x, int y, Vec2 orig) {
          if (x < 0 || x >= w || y < 0 || y >= h || lines[y][x] != c) {
            if (!bg[orig.y + 1][orig.x + 1]) {
              bg[orig.y + 1][orig.x + 1] = true;
              borders.push_back({orig.x + 1, orig.y + 1});
            }
            return;
          }

          if (bfs[y][x])
            return;

          nextToVisit.push_back({x, y});
          bfs[y][x] = true;
          lb[y + 1][x + 1] = true;
        };

        for (Vec2 pos : toVisit) {
          area++;
          check(pos.x + 1, pos.y, pos);
          check(pos.x - 1, pos.y, pos);
          check(pos.x, pos.y + 1, pos);
          check(pos.x, pos.y - 1, pos);
        }

        toVisit = nextToVisit;
      }
      // printf("char: %c area: %d * per: %d = %d\n", c, area, per, area * per);

      int borderCount = 0;

      unordered_set<Vec2, Vec2::Hash> dots;

      for (auto [x, y] : borders) {
        // se
        if (!((lb[y + 1][x + 1] && lb[y][x + 1] && lb[y + 1][x]) ||
              (lb[y][x + 1] && !lb[y + 1][x] && !lb[y + 1][x + 1]) ||
              (lb[y + 1][x] && !lb[y][x + 1] && !lb[y + 1][x + 1]))) {
          if (lb[y + 1][x + 1] && !lb[y + 1][x] && !lb[y][x + 1]) {
            borderCount++;
          }
          dots.insert({x + 1, y + 1});
        }

        // sw
        if (!((lb[y][x - 1] && lb[y + 1][x] && lb[y + 1][x - 1]) ||
              (lb[y][x - 1] && !lb[y + 1][x] && !lb[y + 1][x - 1]) ||
              (lb[y + 1][x] && !lb[y][x - 1] && !lb[y + 1][x - 1]))) {
          if (lb[y + 1][x - 1] && !lb[y + 1][x] && !lb[y][x - 1]) {
            borderCount++;
          }
          dots.insert({x, y + 1});
        }

        // ne
        if (!((lb[y - 1][x] && lb[y - 1][x + 1] && lb[y][x + 1]) ||
              (lb[y - 1][x] && !lb[y][x + 1] && !lb[y - 1][x + 1]) ||
              (lb[y][x + 1] && !lb[y - 1][x] && !lb[y - 1][x + 1]))) {
          dots.insert({x + 1, y});
        }

        // nw
        if (!((lb[y - 1][x] && lb[y - 1][x - 1] && lb[y][x - 1]) ||
              (lb[y - 1][x] && !lb[y][x - 1] && !lb[y - 1][x - 1]) ||
              (lb[y][x - 1] && !lb[y - 1][x] && !lb[y - 1][x - 1]))) {
          dots.insert({x, y});
        }
      }
      borderCount += dots.size();

      // printf("char: %c, area: %d * borderCount: %d\n", c, area, borderCount);
      sum += area * borderCount;
    }
  }

  return sum;
}

int main() {
  // printf("solve1 ex0 (1930 expected): %llu\n", solve1("ex0"));
  // printf("solve1 in0 (1363682 expected): %llu\n", solve1("in0"));
  printf("solve2 ex1 (80 expected): %llu\n", solve2("ex1"));
  printf("solve2 ex2 (436 expected): %llu\n", solve2("ex2"));
  printf("solve2 ex3 (368 expected): %llu\n", solve2("ex3"));
  printf("solve2 ex0 (1206 expected): %llu\n", solve2("ex0"));
  printf("solve2 ex4 (236 expected): %llu\n", solve2("ex4"));
  printf("solve2 in0 (787680 expected): %llu\n", solve2("in0"));
  // printf("solve1 bigboy.txt ( expected): %llu\n",
  // solve1("bigboy.txt")); printf("solve2 bigboy.txt ( expected): %llu\n",
  // solve2("bigboy.txt"));
  return 0;
}
