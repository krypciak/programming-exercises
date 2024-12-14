#include <bits/stdc++.h>
#include <csignal>
using namespace std;

typedef long long ll;

struct Robot {
  ll rx, ry;
  ll vx, vy;
};

pair<ll, vector<vector<ll>>> solve1(string fileName, const ll w = 101,
                                    const ll h = 103, const ll t = 100) {
  fstream cin(fileName);

  string line;
  vector<Robot> robots;
  while (getline(cin, line)) {
    transform(begin(line), end(line), begin(line), [](char c) {
      return ((c >= '0' && c <= '9') || c == '+' || c == '-') ? c : ' ';
    });
    stringstream ss(line);
    ll rx, ry, vx, vy;
    ss >> rx >> ry >> vx >> vy;

    robots.push_back({rx, ry, vx, vy});
  }

  vector<ll> quadrants(4, 0);

  vector<vector<ll>> grid(h, vector<ll>(w, 0));

  for (auto [rx, ry, vx, vy] : robots) {
    ll fx = (rx + t * vx) % w;
    ll fy = (ry + t * vy) % h;

    if (fx < 0) {
      fx = w + fx;
    }
    if (fy < 0) {
      fy = h + fy;
    }

    grid[fy][fx]++;

    if (fx == (w - 1) / 2 || fy == (h - 1) / 2)
      continue;

    int quadrant;
    if (fx > w / 2) {
      if (fy > h / 2)
        quadrant = 3;
      else
        quadrant = 1;
    } else {
      if (fy > h / 2)
        quadrant = 2;
      else
        quadrant = 0;
    }
    quadrants[quadrant]++;
  }

  ll sum = 1;
  for (int i = 0; i < (int)quadrants.size(); i++) {
    sum *= quadrants[i];
  }

  return {sum, grid};
}

void solve2() {
  const ll w = 101;
  const ll h = 103;
  for (ll t = 0;; t++) {
    auto grid = solve1("in0", w, h, t).second;

    bool display = false;
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (grid[y][x]) {
          int counter = 0;
          for (; x < w && grid[y][x]; x++, counter++) {
          }
          if (counter == 31) {
            display = true;
            goto end;
          }
        }
      }
    }

  end:
    if (display) {
      printf("\033[2J\033[1;1H");
      printf("time: %llu\n\n", t);

      for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
          char c = grid[y][x] ? '#' : ' ';
          cout << c;
        }
        cout << "\n";
      }
      cout << endl;
      cin.get();
    }
  }
}

int main() {
  // printf("solve1 ex0 ( expected): %llu\n", solve1("ex0", 11, 7, 100).first);
  // printf("solve1 in0 ( expected): %llu\n", solve1("in0").first);
  // printf("solve2 ex0 ( expected): %llu\n", solve1("ex0", true));
  // printf("solve2 in0 ( expected): %llu\n", solve1("in0", true).);

  solve2();
  return 0;
}
