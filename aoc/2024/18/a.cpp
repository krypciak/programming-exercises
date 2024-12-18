#include <bits/stdc++.h>
#include <csignal>
using namespace std;

struct Vec2 {
  int x, y;
};

typedef unsigned long long ll;

string solve1(string fileName, bool part2 = false, int s = 71,
              int bytesFallen = 1024) {
  ifstream cin(fileName);

  vector<Vec2> fall;
  string line;
  while (getline(cin, line)) {
    transform(begin(line), end(line), begin(line),
              [](char c) { return c >= '0' && c <= '9' ? c : ' '; });

    stringstream ss(line);
    int x, y;
    ss >> x >> y;
    fall.push_back({x + 1, y + 1});
  }

  const int bs = s + 2;
  vector<vector<char>> origGrid(bs, vector<char>(bs, '.'));
  for (int y = 0; y < bs; y++) {
    origGrid[y][0] = origGrid[y][bs - 1] = '#';
  }
  for (int x = 0; x < bs; x++) {
    origGrid[0][x] = origGrid[bs - 1][x] = '#';
  }

  auto find = [origGrid, &fall, bs](int bytesFallen) {
    vector<vector<bool>> visited(bs, vector<bool>(bs, false));
    auto grid = origGrid;

    for (int i = 0; i < min((int)fall.size(), bytesFallen); i++) {
      auto [x, y] = fall[i];
      grid[y][x] = '#';
    }

    vector<Vec2> toVisit;
    toVisit.push_back({1, 1});
    for (int dist = 0; (int)toVisit.size() > 0; dist++) {
      vector<Vec2> nextToVisit;
      for (auto [x, y] : toVisit) {
        auto check = [&](int x1, int y1) {
          if (grid[y1][x1] == '#')
            return;
          if (visited[y1][x1])
            return;

          visited[y1][x1] = true;
          nextToVisit.push_back({x1, y1});
        };
        check(x, y + 1);
        check(x, y - 1);
        check(x + 1, y);
        check(x - 1, y);

        if (x == bs - 2 && y == bs - 2) {
          return dist;
        }
      }
      toVisit = nextToVisit;
    }
    return 0;
  };

  if (!part2)
    return to_string(find(bytesFallen));

  bytesFallen = 0;
  for (; bytesFallen < (int)fall.size(); bytesFallen++) {
    if (find(bytesFallen) == 0) {
      Vec2 pos = fall[bytesFallen - 1];
      pos.x--;
      pos.y--;
      return format("{},{}", pos.x, pos.y);
    }
  }

  return "fail";
}

int main() {
  // clang-format off
  printf("solve1 ex0 (22 expected): %s\n", solve1("ex0", false, 7, 12).c_str());
  printf("solve1 in0 (384 expected): %s\n", solve1("in0").c_str());

  printf("solve2 ex0 ( expected): %s\n", solve1("ex0", true, 7).c_str());
  printf("solve2 in0 ( expected): %s\n", solve1("in0", true).c_str());
  // clang-format on

  return 0;
}
