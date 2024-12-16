#include <bits/stdc++.h>
#include <csignal>
using namespace std;

typedef long long ll;

struct Vec2 {
  int x, y;

  bool operator==(const Vec2 &a) const { return x == a.x && y == a.y; };

  bool operator<(const Vec2 &a) const {
    if (y == a.y)
      return x < a.x;
    return y < a.y;
  }
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

ll solve1(string fileName) {
  fstream cin(fileName);

  Vec2 start;
  Vec2 end;

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

  const int w = lines[0].size();
  const int h = lines.size();

  vector<vector<int>> visited(h, vector<int>(w, 1000000000));

  struct Entry {
    int cost;
    Vec2 pos;
    Dir dir;

    bool operator<(const Entry &a) const {
      return cost < a.cost;
    }
  };
  multiset<Entry> toVisit;

  auto draw = [&]() {
    cout<<endl;
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (visited[y][x]) {
          bool was = false;
          // for (Entry e : toVisit) {
          //   if (e.pos.x == x && e.pos.y == y) {
          //     was = true;
          //     break;
          //   }
          // }
          if (was) {
            cout << '%';
          } else {
            cout << '+';
          }
        } else {
          cout << lines[y][x];
        }
      }
      cout << endl;
    }

  };

  int das = 0;
  toVisit.insert({0, start, Right});
  visited[start.y][start.x] = true;
  while(toVisit.size() > 0) {
    // das++;
    // if (das % 1000 == 0) {
    //   draw();
    // }
    auto first = begin(toVisit);
    auto [cost, pos, dir] = *first;
    if (lines[pos.y][pos.x] == 'E') return cost;
    toVisit.erase(first);

    auto check = [&](Dir d) {
      int x = pos.x + dirToVec[d].x;
      int y = pos.y + dirToVec[d].y;
      char c = lines[y][x];
      if (c == '#') return;

      int newCost = cost + 1 + (dir == d ? 0 : 1000);
      if (visited[y][x] <= newCost) return;

      visited[y][x] = newCost;

      toVisit.insert({newCost, {x, y}, d});
    };
    if (dir != Down) check(Up);
    if (dir != Left) check(Right);
    if (dir != Up) check(Down);
    if (dir != Right) check(Left);
  }

  return 1;
}

int main() {
  printf("solve1 ex0 (7036 expected): %llu\n", solve1("ex0"));
  printf("solve1 ex1 (11048 expected): %llu\n", solve1("ex1"));
  printf("solve1 in0 ( expected): %llu\n", solve1("in0"));

  // printf("solve2 ex1 (9021 expected): %llu\n", solve2("ex1"));
  // printf("solve2 in0 ( expected): %llu\n", solve2("in0"));
  return 0;
}
