#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ll;

struct Bot {
  int s, z;
  int id;
  int infl;
};

int main(void) {
#ifdef DEBUG
  ifstream cin("tests/input1/test908.in");
  signal(SIGINT, [](int signum) { exit(signum); });
#endif

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  Bot bots[n];
  Bot *sSort[n];
  Bot *zSort[n];

  Bot *botsSorted[n];

  // O(n)
  for (int i = 0; i < n; i++) {
    int s, z;
    cin >> s >> z;
    s--;
    z--;

    bots[i] = {
        s,
        z,
        i,
        0,
    };
    botsSorted[i] = &bots[i];
    sSort[s] = &bots[i];
    zSort[z] = &bots[i];
  }

  auto anihil = [](Bot *b1, Bot *b2) {
    return (b1->s > b2->s && b1->z < b2->z) || (b1->s < b2->s && b1->z > b2->z);
  };
  auto wins = [](Bot *b1, Bot *b2) { return b1->s > b2->s && b1->z > b2->z; };

  auto fast = [&]() {
    int headSize = 0;
    vector<Bot *> headBots;

    int base = n;
    base--;
    base |= base >> 1;
    base |= base >> 2;
    base |= base >> 4;
    base |= base >> 8;
    base |= base >> 16;
    base++;

    vector<int> rt(base * 2, 0);
    auto rtChange = [&rt, base](int i, int value) {
      i += base;
      rt[i] = value;
      i /= 2;
      while (i > 0) {
        rt[i] = rt[i * 2] + rt[i * 2 + 1];
        i /= 2;
      }
    };
    auto rtQuery = [&rt, base](int a, int b) {
      int res = 0;
      a = a - 1 + base;
      b = b + 1 + base;
      while (a / 2 != b / 2) {
        if (a % 2 == 0)
          res += rt[a + 1];
        if (b % 2 == 1)
          res += rt[b - 1];

        a /= 2;
        b /= 2;
      }
      return res;
    };

    vector<bool> inHead(n, false);

    bool goZ = true;
    bool goS = true;
    int x = n - 1, y = n - 1;
    while (goZ || goS) {
      if (goZ) {
        Bot *b1 = zSort[x];
        if (!inHead[b1->id]) {
          bool anihils = false;
          if (x == n - 1) {
            anihils = true;
          } else {
            for (Bot *b2 : headBots) {
              if (anihil(b1, b2)) {
                anihils = true;
                break;
              }
            }
          }
          if (!anihils) {
            goZ = false;
          } else {
            inHead[b1->id] = true;
            headBots.push_back(b1);
            headSize++;
          }
        }
        x--;
        if (x < 0)
          goZ = false;
      }
      if (goS) {
        Bot *b1 = sSort[y];
        if (!inHead[b1->id]) {
          bool anihils = false;

          for (Bot *b2 : headBots) {
            if (anihil(b1, b2)) {
              anihils = true;
              break;
            }
          }
          if (!anihils) {
            goS = false;
          } else {
            inHead[b1->id] = true;
            headBots.push_back(b1);
            headSize++;
          }
        }
        y--;
        if (y < 0)
          goS = false;
      }
    }
    // cout << "head size: " << headBots.size() << endl;

    int headInfl = 0;
    for (int i = n - 2; i >= n - headSize; i--) {
      Bot *bprev = zSort[i + 1];
      rtChange(bprev->s, 1);

      Bot *b1 = zSort[i];
      int res = rtQuery(b1->s + 1, n);

      if (res >= 1) {
        headInfl++;
        break;
      }
    }

    if (headSize % 2 == 0 || headInfl > 0) {
      cout << "TAK" << endl;
    } else {
      cout << "NIE" << endl;
    }
  };

  fast();
  return 0;
}
