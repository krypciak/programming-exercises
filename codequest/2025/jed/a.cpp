#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  string line;
  getline(cin, line);
  while (t--) {
    getline(cin, line);
    getline(cin, line);
    getline(cin, line);
    transform(begin(line), end(line), begin(line),
              [](char c) { return (c >= '0' and c <= '9') ? c : ' '; });
    stringstream ss(line);
    int w, h, cc, unused;
    ss >> w >> h >> cc >> unused;
    char emptyC = 'a';
    for (int i = 0; i < cc; i++) {
      getline(cin, line);
      if (line[6] == 'C' and line[7] == '0' and line[8] == 'C' and
          line[9] == '0' and line[10] == 'C' and line[11] == '0') {
        emptyC = line[1];
      }
    }
    // std::cout << "emptyC: '" << emptyC << "'" << endl;

    vector<string> map(h);
    for (int y = 0; y < h; y++) {
      getline(cin, line);
      map[y] = line;
    }
    vector<vector<bool>> V(h, vector<bool>(w, false));
    vector<int> aX = {0, 0, 1, -1};
    vector<int> aY = {1, -1, 0, 0};

    int things = 0;
    for (int y = 0; y < h; y++) {
      for (int x = 1; x <= w; x++) {
        if (V[y][x] or map[y][x] == emptyC)
          continue;
        things++;
        // std::cout << "thing at "<< x<< ", "<< y<<endl;
        if (things >= 2) {
          cout << "WARNING\n";
          goto next;
        }
        vector<pair<int, int>> toVisit{{x, y}};
        while (toVisit.size()) {
          vector<pair<int, int>> nextToVisit;
          for (auto [x, y] : toVisit) {
            for (int i = 0; i < 4; i++) {
              int nx = x + aX[i];
              int ny = y + aY[i];
              if (nx < 1 or nx >= w + 1 or ny < 0 or ny >= h)
                continue;
              if (V[ny][nx] or map[ny][nx] == emptyC)
                continue;
              V[ny][nx] = true;
              nextToVisit.push_back({nx, ny});
            }
          }
          toVisit = nextToVisit;
        }
      }
    }
    cout << "OK\n";
  next:
    int _;
  }

  return 0;
}

#ifdef TEST
string rtrim(string s) {
  auto end = s.find_last_not_of(" \n\t\f\r\v");
  return end == string::npos ? s : s.substr(0, end + 1);
}
bool printTest(string name, string outStr, string expStr) {
  if (outStr == expStr) {
    print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
  } else {
    print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: "
          "\n'{}'\n---got: \n'{}'\n\n",
          name, expStr, outStr);
  }
  return outStr == expStr;
}
void test(string name) {
  ifstream in(name + ".in");
  ostringstream out;

  ifstream exp(name + ".out");
  string expStr(istreambuf_iterator<char>{exp}, {});
  expStr = rtrim(expStr);

  run(in, out);

  string outStr = rtrim(out.str());

  printTest(name, outStr, expStr);
}

int main() {
  test("ex0");
  return 0;
}
#endif
