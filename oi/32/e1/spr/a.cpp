#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ll;

struct Eq {
  ll l;
  ll r;
  int s;
};
struct Ve {
  Eq w;
  Eq m;
  vector<bool> hist;
};

bool isOk(Eq *el, Eq *er) {
  bool wOk = el->l >= el->r - el->s;
  bool mOk = er->l >= er->r - er->s;
  return wOk && mOk;
}

void addL(Eq *a, int val) { a->l += val; }

void addR(Eq *b, int val) {
  if (b->s > val) {
    b->s = val;
  }
  b->r += val;
}

int n;
int *w;
int *m;

bool checkSubTask3() {
  bool allTheSameW = true;
  for (int i = 1; i < n; i++) {
    if (w[0] != w[i]) {
      allTheSameW = false;
      break;
    }
  }
  bool allTheSameM = true;
  for (int i = 1; i < n; i++) {
    if (m[0] != m[i]) {
      allTheSameM = false;
      break;
    }
  }

  if (allTheSameW && allTheSameM) {
    for (int i = 0; i < ceil((double)n / 2); i++) {
      cout << "1 ";
    }
    for (int i = ceil((double)n / 2); i < n; i++) {
      cout << "0 ";
    }
    cout << endl;
    return true;
  }
  return false;
}

int brute() {

  if (n > 20)
    return 1;

  vector<Ve> toVisit;
  toVisit.push_back({{0, 0, 2'000'000'000}, {0, 0, 2'000'000'000}, {}});
  for (int gen = 0; gen < n; gen++) {

    int size = toVisit.size();
    vector<Ve> toVisitOld = toVisit;
    toVisit.clear();

    for (int i = 0; i < size; i++) {
      Ve n0 = toVisitOld[i];
      addL(&n0.w, w[gen]);
      addR(&n0.m, m[gen]);
      n0.hist.push_back(0);
      toVisit.push_back(n0);

      Ve n1 = toVisitOld[i];
      addL(&n1.m, m[gen]);
      addR(&n1.w, w[gen]);
      n1.hist.push_back(1);
      toVisit.push_back(n1);
    }
  }
  // for (Ve ve : toVisit) {
  //   for (int j = 0; j < n; j++) {
  //     cout << ve.hist[j] << " ";
  //   }
  //   cout << "\n";
  // }

  for (Ve ve : toVisit) {
    if (isOk(&ve.w, &ve.m)) {
      for (int j = 0; j < n; j++) {
        cout << ve.hist[j] << " ";
      }
      cout << "\n";

      return 0;
    }
  }
  return 2;
}
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  w = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }
  m = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> m[i];
  }

  if (checkSubTask3())
    return 0;

  return brute();
}
