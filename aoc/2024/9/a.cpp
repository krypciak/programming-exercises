#include <bits/stdc++.h>
#include <cstdio>
#include <unistd.h>
using namespace std;

typedef unsigned long long ll;

ll solve1(string fileName) {
  fstream cin(fileName);

  string line;
  getline(cin, line);

  ll lastLenI = line.size() % 2 == 0 ? line.size() - 2 : line.size() - 1;

  ll pos = line[0] - '0';
  ll sum = 0;

  for (ll i = 1; i - 1 < lastLenI; i++) {
    int gap = line[i] - '0';

    int lastLen, lastLenPos;
    if (i % 2 == 1) {
      // gap
      lastLen = line[lastLenI] - '0';
      lastLenPos = lastLenI / 2;
    } else {
      // non gap
      lastLen = line[i] - '0';
      lastLenPos = i / 2;
    }

    int canFit = min(gap, lastLen);

    ll newLenI = pos + canFit - 1;
    ll checkSumVal =
        lastLenPos * ((newLenI * (newLenI + 1) / 2) - ((pos - 1) * pos / 2));

    sum += checkSumVal;
    pos += canFit;

    if (i % 2 == 1) {
      int lenLeft = lastLen - canFit;

      if (lenLeft == 0) {
        lastLenI -= 2;
      } else {
        line[lastLenI] = '0' + lenLeft;
      }

      if (gap > lastLen) {
        assert(lenLeft == 0);
        line[i] = '0' + gap - lastLen;

        i--;
      }
    }
  }

  return sum;
}

ll solve2(string fileName) {
  fstream cin(fileName);

  string line;
  getline(cin, line);

  struct Entry {
    int len;
    bool moved;
    int id;
    int gapLeft;
    vector<Entry> gapSubEntries;
  };
  vector<Entry> vec;
  int id = 0;
  for (int i = 0; i < (int)line.size(); i += 2, id++) {
    int len = line[i] - '0';
    int gap = 0;
    if (i + 1 < (int)line.size())
      gap = line[i + 1] - '0';

    vec.push_back({len, false, id, gap, vector<Entry>()});
  }

  for (int i = vec.size() - 1; i >= 1; i--) {
    Entry *e = &vec[i];

    for (int j = 0; j < i; j++) {
      Entry *tryE = &vec[j];
      if (tryE->gapLeft >= e->len) {
        tryE->gapSubEntries.push_back(*e);
        tryE->gapLeft -= e->len;

        vec[i - 1].gapLeft += e->len;
        e->moved = true;

        break;
      }
    }
  }

  ll sum = 0;

  ll pos = 0;
  for (int i = 0; i < (int)vec.size(); i++) {
    Entry e = vec[i];

    auto calc = [&pos](int len, int id) {
      ll newPos = pos + len - 1;
      ll checkSumVal =
          id * ((newPos * (newPos + 1) / 2) - ((pos - 1) * pos / 2));

      pos = newPos + 1;
      return checkSumVal;
    };

    if (!e.moved) {
      sum += calc(e.len, e.id);
    }
    for (Entry gapE : e.gapSubEntries) {
      sum += calc(gapE.len, gapE.id);
    }
    pos += e.gapLeft;
  }

  return sum;
}

int main() {
  printf("solve1 ex0 (1928 expected): %llu\n", solve1("ex0"));
  printf("solve1 in0 (6201130364722 expected): %llu\n", solve1("in0"));
  // printf("solve2 ex0 (2858 expected): %llu\n", solve2("ex0"));
  // printf("solve2 in0 (6221662795602 expected): %llu\n", solve2("in0"));
  // printf("solve1 bigboy.txt ( expected): %llu\n", solve1("bigboy.txt"));
  // printf("solve2 bigboy.txt ( expected): %llu\n", solve2("bigboy.txt"));
  return 0;
}
