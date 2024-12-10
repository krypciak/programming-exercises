#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

struct Vec2 {
  int x, y;
};

ll solve1(string fileName, bool part2) {
  fstream cin(fileName);

  vector<string> lines;
  string line;
  while (getline(cin, line)) {
    lines.push_back(line);
  }

  int w = lines[0].size();
  int h = lines.size();

  vector<Vec2> zeros;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if (lines[y][x] == '0')
        zeros.push_back({x, y});
    }
  }

  ll sum = 0;

  for (Vec2 zero : zeros) {
    vector<vector<bool>> bfs(h, vector<bool>(w, false));

    vector<Vec2> toVisit;
    toVisit.push_back(zero);
    for (int dist = 1; dist <= 9; dist++) {
      vector<Vec2> nextToVisit;
      for (Vec2 pos : toVisit) {
        auto check = [&](int x, int y) {
          if (x < 0 || x >= w || y < 0 || y >= h)
            return;
          if (bfs[y][x])
            return;
          if (lines[y][x] != dist + '0')
            return;

          if (!part2 && dist == 9)
            bfs[y][x] = true;

          nextToVisit.push_back({x, y});
        };
        check(pos.x, pos.y - 1);
        check(pos.x, pos.y + 1);
        check(pos.x - 1, pos.y);
        check(pos.x + 1, pos.y);
      }
      toVisit = nextToVisit;
    }
    sum += toVisit.size();
  }
  return sum;
}

int main() {
  printf("solve1 ex0 (36 expected): %llu\n", solve1("ex0", false));
  printf("solve1 in0 (462 expected): %llu\n", solve1("in0", false));
  printf("solve2 ex0 (81 expected): %llu\n", solve1("ex0", true));
  printf("solve2 in0 (969 expected): %llu\n", solve1("in0", true));
  // printf("solve1 bigboy.txt ( expected): %llu\n", solve1("bigboy.txt"));
  // printf("solve2 bigboy.txt ( expected): %llu\n", solve2("bigboy.txt"));
  return 0;
}
