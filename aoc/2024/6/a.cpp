#include <bits/stdc++.h>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <functional>
#include <vector>
using namespace std;

#define byte uint8_t

struct Vec2 {
  int x, y;
};

int solve1(string file) {
  ifstream cin(file);

  vector<string> lines;
  string line;
  Vec2 pos;
  int dir = -1;
  for (int y = 0; getline(cin, line); y++) {
    lines.push_back(line);

    if (dir == -1) {
      int x = line.find('^');
      if (x != (int)string::npos) {
        pos = {x, y};
        char c = line[x];
        dir = c == '^' ? 0 : c == '>' ? 1 : c == 'v' ? 2 : c == '<' ? 3 : -1;
      }
    }
  }
  assert(dir != -1);
  int w = lines[0].size();
  int h = lines.size();

  lines[pos.y][pos.x] = '.';

  function<void(int)> move = [&pos, &dir](int amount) {
    if (dir == 0)
      pos.y -= amount;
    else if (dir == 1)
      pos.x += amount;
    else if (dir == 2)
      pos.y += amount;
    else if (dir == 3)
      pos.x -= amount;
  };
  function<bool()> isOutside = [&pos, w, h, &lines]() {
    return pos.x < 0 || pos.x >= w || pos.y < 0 || pos.y >= h;
  };

  function<void()> print = [&]() {
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (pos.x == x && pos.y == y) {
          cout << (dir == 0   ? '^'
                   : dir == 1 ? '>'
                   : dir == 2 ? 'v'
                   : dir == 3 ? '<'
                              : '?');
        } else {
          cout << lines[y][x];
        }
      }
      cout << endl;
    }
    cout << endl;
  };

  int sum = 0;
  while (true) {
    // print();
    move(1);
    if (isOutside()) {
      break;
    }
    if (lines[pos.y][pos.x] == '#') {
      move(-1);
      dir = (dir + 1) % 4;
    }

    if (lines[pos.y][pos.x] == '.') {
      lines[pos.y][pos.x] = 'X';
      sum++;
    }
  }

  return sum;
}

int solve2(string file) {
  ifstream cin(file);

  vector<string> startLines;
  string line;
  Vec2 startPos;
  int startDir = -1;
  for (int y = 0; getline(cin, line); y++) {
    startLines.push_back(line);

    if (startDir == -1) {
      int x = line.find('^');
      if (x != (int)string::npos) {
        startPos = {x, y};
        char c = line[x];
        startDir = c == '^'   ? 0
                   : c == '>' ? 1
                   : c == 'v' ? 2
                   : c == '<' ? 3
                              : -1;
      }
    }
  }
  assert(startDir != -1);
  int w = startLines[0].size();
  int h = startLines.size();

  startLines[startPos.y][startPos.x] = '.';

  vector<Vec2> walkHist;

  auto walk = [&](bool firstTime, vector<string> lines, string id) {
    Vec2 pos = startPos;
    int dir = startDir;

    function<void(int)> move = [&pos, &dir](int amount) {
      if (dir == 0)
        pos.y -= amount;
      else if (dir == 1)
        pos.x += amount;
      else if (dir == 2)
        pos.y += amount;
      else if (dir == 3)
        pos.x -= amount;
    };
    function<bool()> isOutside = [&pos, w, h, &lines]() {
      return pos.x < 0 || pos.x >= w || pos.y < 0 || pos.y >= h;
    };

    function<void()> print = [&]() {
      cout << "-------- " << id << endl;
      for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
          if (pos.x == x && pos.y == y) {
            cout << (dir == 0   ? '^'
                     : dir == 1 ? '>'
                     : dir == 2 ? 'v'
                     : dir == 3 ? '<'
                                : '?');
          } else {
            cout << lines[y][x];
          }
        }
        cout << endl;
      }
      cout << endl;
    };

    vector<vector<vector<bool>>> wasInPos(
        h, vector<vector<bool>>(w, vector<bool>(4, false)));

    while (true) {
      // print();
      move(1);
      if (isOutside()) {
        return true;
      }

      if (lines[pos.y][pos.x] == '#') {
        move(-1);
        dir = (dir + 1) % 4;
      }

      if (!firstTime) {
        if (wasInPos[pos.y][pos.x][dir]) {
          return false;
        }
        // printf("adding %d, %d to wasInPos\n", pos.x, pos.y);
        wasInPos[pos.y][pos.x][dir] = true;
      }

      if (lines[pos.y][pos.x] == '.') {
        lines[pos.y][pos.x] = 'X';
        if (firstTime) {
          walkHist.push_back({pos.x, pos.y});
        }
      }
    }
  };

  assert(walk(true, startLines, "first"));

  int sum = 0;
  int ite = 0;
  for (Vec2 pos : walkHist) {
    vector<string> newLines = startLines;
    newLines[pos.y][pos.x] = '#';
    if (!walk(false, newLines, to_string(ite))) {
      sum++;
    }

    ite++;
  }

  return sum;
}

int main() {
  printf("solve1 ex0 (41 expected): %d\n", solve1("ex0"));
  printf("solve1 in0 (5067 expected): %d\n", solve1("in0"));
  printf("solve2 ex0 (6 expected): %d\n", solve2("ex0"));
  printf("solve2 in0 (1793 expected): %d\n", solve2("in0"));
  // printf("solve1 bigboy ( expected): %d\n", solve1("bigboy.txt"));
  // printf("solve2 bigboy ( expected): %d\n", solve2("bigboy.txt"));
  return 0;
}
