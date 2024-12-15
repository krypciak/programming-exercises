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

  string line;
  vector<string> map;
  Vec2 initialPos;
  for (int y = 0;; y++) {
    getline(cin, line);

    if (line == "")
      break;

    map.push_back(line);

    size_t robotX = line.find('@');
    if (robotX != string::npos) {
      initialPos = {(int)robotX, y};
    }
  }
  map[initialPos.y][initialPos.x] = '.';

  const int w = map[0].size();
  const int h = map.size();

  vector<Dir> moves;
  while (getline(cin, line)) {
    for (char c : line) {
      moves.push_back(c == '^'   ? Up
                      : c == '>' ? Right
                      : c == 'v' ? Down
                                 : Left);
    }
  }

  Vec2 pos = initialPos;

  auto printMap = [&]() {
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (x == pos.x && y == pos.y) {
          assert(map[y][x] == '.');
          cout << '@';
        } else {
          cout << map[y][x];
        }
      }
      cout << '\n';
    }
    cout << endl;
  };

  for (Dir move : moves) {
    // printMap();
    Vec2 v = dirToVec[move];
    Vec2 newPos = {pos.x + v.x, pos.y + v.y};
    char c = map[newPos.y][newPos.x];
    if (c == '.') {
      pos = newPos;
    } else if (c == '#') {
      // nothing
    } else if (c == 'O') {
      Vec2 tmp = newPos;
      bool canMove = true;
      while (true) {
        tmp = {tmp.x + v.x, tmp.y + v.y};
        char c = map[tmp.y][tmp.x];
        if (c == '#') {
          canMove = false;
          break;
        }
        if (c == '.') {
          canMove = true;
          break;
        }
      }

      if (canMove) {
        map[tmp.y][tmp.x] = 'O';
        map[newPos.y][newPos.x] = '.';
        pos = newPos;
      }
    }
  }

  ll sum = 0;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if (map[y][x] == 'O') {
        sum += y * 100 + x;
      }
    }
  }

  return sum;
}

ll solve2(string fileName) {
  fstream cin(fileName);

  string line;
  vector<string> rawMap;
  Vec2 initialPos;
  for (int y = 0;; y++) {
    getline(cin, line);

    if (line == "")
      break;

    rawMap.push_back(line);

    size_t robotX = line.find('@');
    if (robotX != string::npos) {
      initialPos = {(int)robotX, y};
    }
  }
  rawMap[initialPos.y][initialPos.x] = '.';

  initialPos.x *= 2;

  const int w = rawMap[0].size() * 2;
  const int h = rawMap.size();
  vector<vector<char>> map(h, vector<char>(w));
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w / 2; x++) {
      char c = rawMap[y][x];
      if (c == 'O') {
        map[y][x * 2] = '[';
        map[y][x * 2 + 1] = ']';
      } else {
        map[y][x * 2] = map[y][x * 2 + 1] = c;
      }
    }
  }

  vector<Dir> moves;
  while (getline(cin, line)) {
    for (char c : line) {
      moves.push_back(c == '^'   ? Up
                      : c == '>' ? Right
                      : c == 'v' ? Down
                                 : Left);
    }
  }

  Vec2 pos = initialPos;

  auto printMap = [&](Dir dir) {
    printf("move: %d\n", dir);
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (x == pos.x && y == pos.y) {
          assert(map[y][x] == '.');
          cout << '@';
        } else {
          cout << map[y][x];
        }
      }
      cout << '\n';
    }
    cout << endl;
  };

  for (Dir move : moves) {
    // printMap();
    Vec2 v = dirToVec[move];
    Vec2 newPos = {pos.x + v.x, pos.y + v.y};
    char c = map[newPos.y][newPos.x];
    if (c == '.') {
      pos = newPos;
    } else if (c == '#') {
      // nothing
    } else if (c == '[' || c == ']') {
      if (move == Left || move == Right) {
        Vec2 tmp = newPos;
        bool canMove = true;

        while (true) {
          tmp = {tmp.x + v.x, tmp.y + v.y};
          char c = map[tmp.y][tmp.x];
          if (c == '#') {
            canMove = false;
            break;
          }
          if (c == '.') {
            canMove = true;
            break;
          }
        }

        if (canMove) {
          map[newPos.y][newPos.x] = '.';
          if (move == Left) {
            char lb = false;
            for (int x = newPos.x - 1; x >= tmp.x; x--) {
              map[newPos.y][x] = lb ? '[' : ']';
              lb = !lb;
            }
          } else {
            char lb = true;
            for (int x = newPos.x + 1; x <= tmp.x; x++) {
              map[newPos.y][x] = lb ? '[' : ']';
              lb = !lb;
            }
          }
          pos = newPos;
        }
      } else {
        vector<Vec2> hist;

        set<Vec2> checkNext;
        if (c == '[') {
          checkNext.insert(newPos);
          hist.push_back(newPos);
          checkNext.insert({newPos.x + 1, newPos.y});
          hist.push_back({newPos.x + 1, newPos.y});
        } else {
          checkNext.insert({newPos.x - 1, newPos.y});
          hist.push_back({newPos.x - 1, newPos.y});
          checkNext.insert(newPos);
          hist.push_back(newPos);
        }

        bool canMove = true;
        while (checkNext.size() > 0) {
          set<Vec2> nextCheckNext;
          for (Vec2 checkPos : checkNext) {
            Vec2 np = {checkPos.x, checkPos.y + v.y};
            char c = map[np.y][np.x];
            if (c == '.')
              continue;
            if (c == '#') {
              canMove = false;
              goto whileExit;
            }

            if (c == '[') {
              if (nextCheckNext.insert(np).second) {
                hist.push_back(np);
              }
              if (nextCheckNext.insert({np.x + 1, np.y}).second) {
                hist.push_back({np.x + 1, np.y});
              }
            } else {
              assert(c == ']');
              if (nextCheckNext.insert({np.x - 1, np.y}).second) {
                hist.push_back({np.x - 1, np.y});
              };
              if (nextCheckNext.insert(np).second) {
                hist.push_back(np);
              }
            }
          }
          checkNext = nextCheckNext;
        }

      whileExit:
        if (canMove) {
          for (auto it = rbegin(hist); it != rend(hist); it++) {
            Vec2 pos = *it;
            Vec2 np = {pos.x, pos.y + v.y};
            map[np.y][np.x] = map[pos.y][pos.x];
            map[pos.y][pos.x] = '.';
          }
          pos = newPos;
        }
      }
    }
  }

  ll sum = 0;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if (map[y][x] == '[') {
        sum += y * 100 + x;
      }
    }
  }

  return sum;
}

int main() {
  // printf("solve1 ex0 (2028 expected): %llu\n", solve1("ex0"));
  // printf("solve1 ex1 (10092 expected): %llu\n", solve1("ex1"));
  // printf("solve1 in0 (1436690 expected): %llu\n", solve1("in0"));
  printf("solve2 ex1 (9021 expected): %llu\n", solve2("ex1"));
  printf("solve2 in0 ( expected): %llu\n", solve2("in0"));
  return 0;
}
