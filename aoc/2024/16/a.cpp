#include <bits/stdc++.h>
#include <csignal>
#include <queue>
using namespace std;

typedef long long ll;

struct Vec2 {
  int x, y;
};

enum Dir {
  Up = 0,
  Right = 1,
  Down = 2,
  Left = 3,
};

vector<Vec2> dirToVec = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0},
};

ll solve1(string fileName, bool part2) {
  fstream cin(fileName);

  Vec2 start = {-1, -1};
  Vec2 end = {-1, -1};

  string line;
  vector<string> lines;
  for (int y = 0; getline(cin, line); y++) {
    lines.push_back(line);
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

  const int w = lines[0].size();
  const int h = lines.size();

  const int DEFAULT_VALUE = 1000000000;
  vector<vector<vector<int>>> dist(
      h, vector<vector<int>>(w, vector<int>(4, DEFAULT_VALUE)));

  struct Entry {
    int cost;
    Vec2 pos;
    Dir dir;

    bool operator<(const Entry &a) const { return cost < a.cost; }
    bool operator>(const Entry &a) const { return cost > a.cost; }
  };
  priority_queue<Entry, vector<Entry>, greater<Entry>> toVisit;

  toVisit.push({0, start, Right});
  dist[start.y][start.x][Right] = 0;
  while (toVisit.size() > 0) {
    // draw();

    auto [cost, pos, dir] = toVisit.top();
    toVisit.pop();

    if (dist[pos.y][pos.x][dir] < cost)
      continue;

    auto check = [&](Dir d) {
      int x = pos.x + dirToVec[d].x;
      int y = pos.y + dirToVec[d].y;
      if (lines[y][x] == '#')
        return;

      int oldCost = dist[y][x][d];
      int newCost = cost + (dir == d ? 1 : 1001);

      if (newCost < oldCost) {
        dist[y][x][d] = newCost;
        toVisit.push({newCost, {x, y}, d});
      }
    };

    if (dir != Down)
      check(Up);
    if (dir != Left)
      check(Right);
    if (dir != Up)
      check(Down);
    if (dir != Right)
      check(Left);
  }

  int minDist = min({dist[end.y][end.x][Left], dist[end.y][end.x][Right],
                     dist[end.y][end.x][Up], dist[end.y][end.x][Down]});

  if (!part2)
    return minDist;

  {
    vector<vector<bool>> occu(h, vector<bool>(w, false));
    vector<Entry> toVisit;
    toVisit.push_back({minDist, end, Up});
    toVisit.push_back({minDist, end, Down});
    toVisit.push_back({minDist, end, Right});
    toVisit.push_back({minDist, end, Left});

    int sum = 1;
    auto print = [&]() {
      cout << "sum: " << sum << endl;
      for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
          if (occu[y][x]) {
            cout << '+';
          } else {
            cout << lines[y][x];
          }
        }
        cout << endl;
      }

      cout << endl;
    };
    while (toVisit.size() > 0) {
      // print();
      vector<Entry> nextToVisit;
      for (auto [cost, pos, dir] : toVisit) {

        auto check = [&](Dir d) {
          int x = pos.x + dirToVec[d].x;
          int y = pos.y + dirToVec[d].y;
          if (lines[y][x] == '#')
            return;

          if (occu[y][x])
            return;

          int newCost = cost - (dir == d ? 1 : 1001);

          bool eq = false;
          for (int d1 = 0; d1 < 4; d1++) {
            if (newCost == dist[y][x][d1] || newCost - 1000 == dist[y][x][d1]) {
              eq = true;
              break;
            }
          }
          if (eq) {
            nextToVisit.push_back({newCost, {x, y}, d});
            occu[y][x] = true;
            sum++;
          }
        };

        if (dir != Down)
          check(Up);
        if (dir != Left)
          check(Right);
        if (dir != Up)
          check(Down);
        if (dir != Right)
          check(Left);
      }
      toVisit = nextToVisit;
    }
    return sum;
  }
}

int main() {
  printf("solve1 ex0 (7036 expected): %llu\n", solve1("ex0", false));
  printf("solve1 ex1 (11048 expected): %llu\n", solve1("ex1", false));
  printf("solve1 in0 (105496 expected): %llu\n", solve1("in0", false));

  printf("solve2 ex0 (45 expected): %llu\n", solve1("ex0", true));
  printf("solve2 ex1 (64 expected): %llu\n", solve1("ex1", true));
  printf("solve2 in0 (524 expected): %llu\n", solve1("in0", true));
  return 0;
}
