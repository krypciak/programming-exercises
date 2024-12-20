#include <bits/stdc++.h>
#include <csignal>
#include <stdexcept>
using namespace std;

struct Vec2 {
  int x, y;

  bool operator==(const Vec2 &a) const { return x == a.x && y == a.y; }
};

typedef unsigned long long ll;

ll solve1(string inputFile) {
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

  auto calcNormalDist = [&]() {
    vector<vector<bool>> visited(h, vector<bool>(w, false));
    vector<Vec2> toVisit;
    toVisit.push_back(start);
    visited[start.y][start.x] = true;

    for (int dist = 0; toVisit.size() > 0; dist++) {
      vector<Vec2> nextToVisit;
      for (Vec2 pos : toVisit) {
        if (pos == end) {
          return dist;
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
      }
      toVisit = nextToVisit;
    }
    throw invalid_argument("Normal solution not found!");
  };
  int normalDist = calcNormalDist();

  vector<vector<bool>> visited(h, vector<bool>(w, false));
  vector<Vec2> toVisit;
  toVisit.push_back(start);
  visited[start.y][start.x] = true;

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
      auto checkClip = [&](int x1, int y1, int x2, int y2, int x3, int y3) {
        if (isOutOfBounds(x3, y3) || visited[y3][x3] || lines[y1][x1] != '#' ||
            ((x2 != -1 && y2 != -1) && lines[y2][x2] != '#') ||
            lines[y3][x3] == '#')
          return;

        auto hackBfs = [w, h, &visited, end, &lines, &isOutOfBounds, y3, x3, x1,
                        y1, normalDist](Vec2 start, int startDist) {
          vector<vector<bool>> hackVisited(h, vector<bool>(w, false));
          vector<Vec2> toVisit;
          toVisit.push_back(start);
          hackVisited[start.y][start.x] = true;

          for (int dist = startDist; toVisit.size() > 0; dist++) {
            vector<Vec2> nextToVisit;
            for (Vec2 pos : toVisit) {
              if (pos == end) {
                return dist;
              }
              auto checkNormal = [&](int x, int y) {
                assert(!isOutOfBounds(x, y));
                if (lines[y][x] == '#')
                  return;
                if (visited[y][x] || hackVisited[y][x])
                  return;

                hackVisited[y][x] = true;
                nextToVisit.push_back({x, y});
              };

              checkNormal(pos.x + 1, pos.y);
              checkNormal(pos.x - 1, pos.y);
              checkNormal(pos.x, pos.y + 1);
              checkNormal(pos.x, pos.y - 1);
            }
            toVisit = nextToVisit;
          }
          return -1;
        };

        int newDist = hackBfs({x3, y3}, dist + 2);
        int diff = normalDist - newDist;

        if (newDist != -1) {
          if (diff >= 100) {
            sum++;
          }
        }
      };

      checkClip(pos.x, pos.y - 1, -1, -1, pos.x, pos.y - 2);
      checkClip(pos.x + 1, pos.y, -1, -1, pos.x + 2, pos.y);
      checkClip(pos.x, pos.y + 1, -1, -1, pos.x, pos.y + 2);
      checkClip(pos.x - 1, pos.y, -1, -1, pos.x - 2, pos.y);
    }
    toVisit = nextToVisit;
  }

ret:
  return sum;
}

int main() {
  // clang-format off
  // printf("solve1 ex0 (0 expected): %llu\n", solve1("ex0"));
  // printf("solve1 in0 (1289 expected): %llu\n", solve1("in0"));

  // printf("solve2 ex0 (0 expected): %llu\n", solve2("ex0"));
  // printf("solve1 in0 (642535800868438 expected): %llu\n", solve1("in0", true));
  // clang-format on

  return 0;
}
