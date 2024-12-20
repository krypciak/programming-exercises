#include <bits/stdc++.h>
#include <csignal>
using namespace std;

struct Vec2 {
  int x, y;

  bool operator==(const Vec2 &a) const { return x == a.x && y == a.y; }
};

typedef unsigned long long ll;

ll solve(string inputFile, const int cheatSize) {
  ifstream cin(inputFile);

  vector<string> lines;
  string line;
  while (getline(cin, line)) {
    lines.push_back(line);
  }

  const int w = lines[0].size();
  const int h = lines.size();

  Vec2 start = {-1, -1};
  Vec2 end = {-1, -1};
  for (int y = 0; y < h; y++) {
    string line = lines[y];
    size_t startX = line.find('S');
    if (startX != string::npos) {
      start = {(int)startX, y};
    }

    size_t endX = line.find('E');
    if (endX != string::npos) {
      end = {(int)endX, y};
    }
  }
  assert(start.x != -1);
  assert(end.x != -1);

  vector<vector<int>> distGrid(h, vector<int>(w, -1));
  auto calcNormalDist = [&]() {
    vector<Vec2> toVisit;
    toVisit.push_back(start);
    distGrid[start.y][start.x] = 0;

    for (int dist = 0; toVisit.size() > 0; dist++) {
      vector<Vec2> nextToVisit;
      for (Vec2 pos : toVisit) {
        auto checkNormal = [&](int x, int y) {
          if (lines[y][x] == '#')
            return;
          if (distGrid[y][x] != -1)
            return;

          nextToVisit.push_back({x, y});
          distGrid[y][x] = dist + 1;
        };

        checkNormal(pos.x + 1, pos.y);
        checkNormal(pos.x - 1, pos.y);
        checkNormal(pos.x, pos.y + 1);
        checkNormal(pos.x, pos.y - 1);
      }
      toVisit = nextToVisit;
    }
  };
  calcNormalDist();
  int normalDist = distGrid[end.y][end.x];

  vector<vector<bool>> visited(h, vector<bool>(w, false));
  vector<Vec2> toVisit;
  toVisit.push_back(start);
  visited[start.y][start.x] = true;

  multiset<int> diffs;
  set<ll> hacks;

  ll sum = 0;
  for (int dist = 0; toVisit.size() > 0; dist++) {
    vector<Vec2> nextToVisit;
    for (Vec2 pos : toVisit) {
      if (pos == end) {
        goto ret;
      }
      auto checkNormal = [&](int x, int y) {
        if (lines[y][x] == '#')
          return;
        if (visited[y][x])
          return;

        visited[y][x] = true;
        nextToVisit.push_back({x, y});
      };

      checkNormal(pos.x + 1, pos.y);
      checkNormal(pos.x - 1, pos.y);
      checkNormal(pos.x, pos.y + 1);
      checkNormal(pos.x, pos.y - 1);

      auto isOutOfBounds = [w, h](int x, int y) {
        return x < 0 || x >= w || y < 0 || y >= h;
      };
      auto checkClip = [&](int fromX, int fromY, int toX, int toY) {
        if (isOutOfBounds(toX, toY) || visited[toY][toX] ||
            lines[toY][toX] == '#' || distGrid[toY][toX] == -1)
          return;

        int fromToToDist = abs(fromX - toX) + abs(fromY - toY);
        int newDist = dist + fromToToDist + (normalDist - distGrid[toY][toX]);
        int diff = normalDist - newDist;

        if (diff > 0) {
          ll en = toX + toY * w + fromX * w * w + fromY * w * w * w;
          assert(hacks.count(en) == 0);
          hacks.insert(en);

          diffs.insert(diff);
          if (diff >= 100) {
            sum++;
          }
        }
      };

      for (int oy1 = 0; oy1 < cheatSize + 1; oy1++) {
        for (int ox = cheatSize - oy1; ox < cheatSize + oy1 + 1; ox++) {
          if ((oy1 == cheatSize - 1 || oy1 == cheatSize ||
               oy1 == cheatSize + 1) &&
              (ox == cheatSize - 1 || ox == cheatSize || ox == cheatSize + 1)) {
            continue;
          }

          if (oy1 != cheatSize) {
            int oy2 = cheatSize * 2 - oy1;
            checkClip(pos.x, pos.y, pos.x + ox - cheatSize,
                      pos.y + oy2 - cheatSize);
          }
          checkClip(pos.x, pos.y, pos.x + ox - cheatSize,
                    pos.y + oy1 - cheatSize);
        }
      }
    }
    toVisit = nextToVisit;
  }

ret:
  // set<int> printedAlready;
  // for (int diff : diffs) {
  //   if (printedAlready.count(diff) > 0)
  //     continue;
  //   printedAlready.insert(diff);
  //
  //   print("times: {}, saved: {}\n", diffs.count(diff), diff);
  // }

  return sum;
}
int main() {
  // clang-format off
  printf("solve1 ex0 (0 expected): %llu\n", solve("ex0", 2));
  printf("solve1 in0 (1289 expected): %llu\n", solve("in0", 2));

  printf("solve2 ex0 (0 expected): %llu\n", solve("ex0", 20));
  printf("solve2 in0 (982425 expected): %llu\n", solve("in0", 20));
  // clang-format on

  return 0;
}
