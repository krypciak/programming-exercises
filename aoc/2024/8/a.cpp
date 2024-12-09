#include <bits/stdc++.h>
#include <cstdio>
#include <unistd.h>
using namespace std;

void nanosleep(unsigned long nsec) {
  struct timespec delay = {static_cast<__time_t>(nsec / 1000000000),
                           static_cast<__syscall_slong_t>(nsec % 1000000000)};
  pselect(0, NULL, NULL, NULL, &delay, NULL);
}

struct Vec2 {
  int x, y;
};

int solve1(string fileName, bool part2) {
  ifstream cin(fileName);

  vector<string> lines;
  string line;
  while (getline(cin, line)) {
    lines.push_back(line);
  }

  function<size_t(char)> getId = [](char c) { return c - '0'; };

  vector<vector<Vec2>> antenas('z' - '0' + 1);
  int w = lines[0].size();
  int h = lines.size();

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      char c = lines[y][x];
      if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
          (c >= '0' && c <= '9')) {
        antenas[getId(c)].push_back({x, y});
      }
    }
  }
  vector<vector<bool>> antinodes(h, vector<bool>(w, false));

  int terminalHeight(WEXITSTATUS(std::system("exit `tput lines`")));
  terminalHeight = 50;
  auto printAntinodes = [&](Vec2 a, Vec2 b) {
    string str = "";

    for (int y = 0; y < min(terminalHeight, h); y++) {
      for (int x = 0; x < w; x++) {
        char antena = lines[y][x];
        bool isAntenaValid = (antena >= 'A' && antena <= 'Z') ||
                             (antena >= 'a' && antena <= 'z') ||
                             (antena >= '0' && antena <= '9');

        bool antinode = antinodes[y][x];

        bool colorAdded = false;
        if ((x == a.x && y == a.y) || (x == b.x && y == b.y)) {
          colorAdded = true;
          str += "\e[31m";
        }

        if (isAntenaValid && antena != '.') {
          if (antinode) {
            colorAdded = true;
            str += "\e[1m";
            str += antena;
          } else {
            str += antena;
          }
        } else {
          str += (antinode ? '#' : '.');
        }

        if (colorAdded) {
          str += "\e[0m";
        }
      }
      str += "\n";
    }

    str = "\033[2J\033[1;1H" + str;
    cout << str << endl;
    nanosleep(1000000);
  };

  int sum = 0;

  for (size_t id = 0; id < antenas.size(); id++) {
    for (size_t ai1 = 0; ai1 < antenas[id].size(); ai1++) {
      Vec2 a1 = antenas[id][ai1];
      for (size_t ai2 = ai1 + 1; ai2 < antenas[id].size(); ai2++) {
        Vec2 a2 = antenas[id][ai2];
        Vec2 dist = {a1.x - a2.x, a1.y - a2.y};

        auto calc = [&sum, &antinodes, dist, w, h, part2, printAntinodes, &a1,
                     &a2](bool add, Vec2 a) {
          int mulSign = (add ? 1 : -1);

          for (int mul = part2 ? 0 : 1; part2 || mul == 1; mul++) {
            Vec2 v = {a.x + dist.x * mulSign * mul,
                      a.y + dist.y * mulSign * mul};

            if (v.x < 0 || v.x >= w || v.y < 0 || v.y >= h)
              return;

            if (!antinodes[v.y][v.x]) {
              antinodes[v.y][v.x] = true;
              sum++;
              if (v.y < 60) {
                printAntinodes(a1, a2);
              }
            }
          }
        };

        calc(true, a1);
        calc(false, a2);
      }
    }
  }

  return sum;
}

int main() {
  // printf("solve1 ex0 (14 expected): %d\n", solve1("ex0", false));
  // printf("solve1 in0 (329 expected): %d\n", solve1("in0", false));
  // printf("solve2 ex0 (34 expected): %d\n", solve1("ex0", true));
  // printf("solve2 in0 (1190 expected): %d\n", solve1("in0", true));
  // printf("solve1 biggirl.txt ( expected): %d\n", solve1("biggirl.txt",
  // false));
  printf("solve2 biggirl.txt ( expected): %d\n", solve1("biggirl.txt", true));
  return 0;
}
