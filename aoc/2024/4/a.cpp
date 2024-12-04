#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Vec2 {
  int x, y;
};
struct Entry {
  Vec2 dir;
  Vec2 pos;
};

int solve1(string fileName) {
  ifstream cin(fileName);

  string line;
  vector<vector<char>> arr;
  while (getline(cin, line)) {
    vector<char> lineArr;
    lineArr.reserve(line.size());
    for (char c : line) {
      lineArr.push_back(c);
    }
    arr.push_back(lineArr);
  }

  const vector<Vec2> dirs = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1},
  };
  const string xmas = "XMAS";

  int sum = 0;

  int width = arr[0].size();
  int height = arr.size();
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (arr[y][x] != 'X')
        continue;

      vector<Entry> toVisit(dirs.size());
      transform(dirs.begin(), dirs.end(), toVisit.begin(),
                [x, y](Vec2 dir) { return (Entry){dir, {x, y}}; });

      vector<Entry> nextToVisit;
      int letter = 1;
      for (; toVisit.size() > 0 && letter < (int)xmas.size(); letter++) {
        for (Entry e : toVisit) {
          e.pos.x += e.dir.x;
          e.pos.y += e.dir.y;
          if (e.pos.x >= width || e.pos.x < 0 || e.pos.y >= height ||
              e.pos.y < 0)
            continue;

          if (arr[e.pos.y][e.pos.x] != xmas[letter])
            continue;

          nextToVisit.push_back(e);
        }
        toVisit = nextToVisit;
        nextToVisit.clear();
      }

      if (letter == (int)xmas.size()) {
        sum += toVisit.size();
      }
    }
  }

  return sum;
}

int solve2(string fileName) {
  ifstream cin(fileName);

  string line;
  vector<vector<char>> arr;
  while (getline(cin, line)) {
    vector<char> lineArr;
    lineArr.reserve(line.size());
    for (char c : line) {
      lineArr.push_back(c);
    }
    arr.push_back(lineArr);
  }

  int sum = 0;

  int width = arr[0].size();
  int height = arr.size();
  for (int y = 1; y < height - 1; y++) {
    for (int x = 1; x < width - 1; x++) {
      if (arr[y][x] != 'A')
        continue;

      if (((arr[y - 1][x - 1] == 'S' && arr[y + 1][x + 1] == 'M') ||
           (arr[y - 1][x - 1] == 'M' && arr[y + 1][x + 1] == 'S')) &&
          ((arr[y - 1][x + 1] == 'S' && arr[y + 1][x - 1] == 'M') ||
           (arr[y - 1][x + 1] == 'M' && arr[y + 1][x - 1] == 'S'))) {
        sum++;
      }
    }
  }

  return sum;
}

int main() { cout << solve1("bigboy.txt") << endl; }
