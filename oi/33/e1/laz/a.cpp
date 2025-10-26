#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int calcGap(const int m, const int pCount) {
  int y = ceil(m / pCount);
  int x = (y * pCount) % m;

  int gap = y - 2 + (x == pCount || x == pCount - 1 ? 0 : 1);
  // if (gap < 0) print("x: {}, y: {}, gap: {}\n", x, y, gap);
  // assert(gap >= 0);
  return gap;
}
int slopeSeqCostForX(const int m, const int x) {
  int gap = calcGap(m, x);
  if (gap <= 0) return 1e9;
  int cost = 1 + (1 + 2*gap)*x;
  return cost;
}
char revDir(const char dir, const bool reverse) {
  if (!reverse) return dir;
  if (dir == 'D') return 'L';
  if (dir == 'G') return 'P';
  if (dir == 'L') return 'G';
  if (dir == 'P') return 'D';
  // impossible
  return ' ';
}
string slopeSeqForX(const int n, const int m, const int cost, const int x) {
  bool reverse = n < m;

  int gap = calcGap(m, x);
  string str;
  str.reserve(cost);
  str += revDir('D', reverse);
  for (int i = 0; i < x; i++) {
    str += revDir('L', reverse);
    str += string(gap, revDir('G', reverse));
    str += string(gap, revDir('D', reverse));
  }
  return str;
}
pair<int, int> findMinSlopeSeqX(const int n, const int m) {
  // assumes n > m
  int minLen = 1e9;
  int minX = -1;

  int smaller = min(n, m);

  for (int x = 1; x < smaller; x++) {
    int len = slopeSeqCostForX(smaller, x);
    if (len < minLen) {
      minLen = len;
      minX = x;
    }
  }
  // console.log('n:', n, 'm:', m)
  // console.log('minX:', minX)
  // console.log(minLen)
  return {minLen, minX};
}

vector<int> findPrimeFactors(int num) {
  vector<int> factors;
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      factors.push_back(i);
      while (num % i == 0) num /= i;
    }
  }
  if (num > 1) factors.push_back(num);
  return factors;
}
bool isCoprime(int val, const vector<int> &f) {
  for (int p : f) {
    if (val % p == 0) return false;
  }
  return true;
}

string solve(const int n, const int m) {
  int x = gcd(n, m);

  if (x == 1) return "DL";

  // if (n >= 100 and m >= 100 and (n >= 1000 or m >= 1000)) {
  //   auto [slopeCost, slopeX] = findMinSlopeSeqX(n, m);
  //   if (slopeCost < x) {
  //     return slopeSeqForX(n, m, slopeCost, slopeX);
  //   }
  // }

  vector<int> nf = findPrimeFactors(n);
  vector<int> mf = findPrimeFactors(m);

  for (int i = 1; i < x; i++) {
    if (isCoprime(i, nf) && isCoprime(x - i, mf)) {
      int d = i;
      int l = x-i;
      return string(d, 'D') + string(l, 'L');
    }
  }
  // impossible
  return "DL";
}

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;

  string sol = solve(n, m);
  cout << sol.size() << '\n';
  cout << sol << '\n';

  return 0;
}
#ifdef TEST
string rtrim(string s) {
  auto end = s.find_last_not_of(" \t\r\v\f\n");
  return end == string::npos ? s : s.substr(0, end + 1);
}

int runSeq(const int n, const int m, const string &seq) {
  vector<vector<char>> tiles(n, vector<char>(m));
  ll tilesLeft = n*m;
  int x = 0, y = 0;
  int noTilesChangedFor = 0;
  while (tilesLeft > 0 and noTilesChangedFor <= max(n,m)) {
    for (char c : seq) {
      if (!tiles[x][y]) {
        tiles[x][y] = true;
        tilesLeft--;
        if (tilesLeft == 0) break;
        noTilesChangedFor = 0;
      } else {
        noTilesChangedFor++;
      }

      if (c == 'D') x = (x+1)%n;
      else if (c == 'L') if (y == 0) y = m-1; else y--;
      else if (c == 'G') if (x == 0) x = n-1; else x--;
      else if (c == 'P') y = (y+1)%m;
    }
  }
  return tilesLeft;
}
string seqFind(const int n, const int m) {
  vector<string> seqs{""};
  while(true) {
    vector<string> nextSeqs;
    nextSeqs.reserve(seqs.size()*4);
    for (const string &seq : seqs) {
      for (char c : {'D', 'L', 'G', 'P'}) {
        string newSeq = seq + c;
        if (runSeq(n, m, newSeq) == 0) return newSeq;

        nextSeqs.push_back(newSeq);
      }
    }
    seqs = nextSeqs;
    // print("{}\n", seqs[0].size());
  }
}

bool isTestOk(string inpS, string expS, string outS) {
  stringstream exp(expS);
  stringstream out(outS);

  int expC;
  int outC;
  exp >> expC;
  out >> outC;

  string seq;
  out >> seq;

  stringstream inp(inpS);
  int n, m;
  inp >> n >> m;

  print("outC: {}, expC: {}\n", outC, expC);
  if (outC > expC) return false;
  if ((ll)n*m >= 512000000) return true;

  bool doesFill = runSeq(n, m, seq) == 0;

  if (!doesFill) {
    print("{}x{} not filled!\n", n, m);
    return false;
  }

  // string optimalSeq = seqFind(n, m);
  // 
  // if (optimalSeq.size() != seq.size()) {
  //   print("{}x{} not optimal! optimal: {}\n", n, m, optimalSeq);
  //   return false;
  // }

  return true;
}
bool printT(string name, string expS, string outS, string inpS, bool passPrint) {
  if (isTestOk(inpS, expS, outS)) {
    if (passPrint) {
      printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
    }
    return true;
  } else {
    int limit = 200;
    printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n-----got: \n'%s'\n\n",
           name.c_str(), expS.substr(0, limit).c_str(), outS.substr(0, limit).c_str());
    return false;
  }
}
bool testStrs(string &name, string inS, string expS, bool passPrint = true) {
  stringstream in(inS);
  ostringstream out;

  run(in, out);
  string outS = rtrim(out.str());

  expS = rtrim(expS);

  return printT(name, expS, outS, inS, passPrint);
}
void test(string name, bool passPrint = true) {
  ifstream in(name + ".in");
  ifstream exp(name + ".out");

  string inS(istreambuf_iterator<char>{in}, {});
  string expS(istreambuf_iterator<char>{exp}, {});
  testStrs(name, inS, expS, passPrint);
}

// bool bul(int n, int m, const int startLen = 2, bool forcePrint = false) {
//   auto [d, l] = solveRaw(n, m);
//
//   bool doesFill = runSeqFast(n, m, d, l) == 0;
//   auto [od, ol] = seqFindFast(n, m, startLen);
//
//   bool isOptimal = od + ol == d + l;
//   if (!isOptimal or !doesFill) {
//     int gcd1 = gcd(n, m);
//
//     string err = "";
//     if (!doesFill) err += "not filled! ";
//     if (!isOptimal) err += "not optimal! ";
//     print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {}x{} {} optimal: {}d {}l, gcd: {}\n\n", n, m, err, od, ol, gcd1);
//
//     return false;
//   }
//
//   if (n == m or forcePrint) {
//     print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {}x{}\n", n, m);
//   }
//   return true;
// }
int main() {
  test("ex0");
  test("ex1");
  test("ex2");
  test("ex3");
  test("ex4");
  test("ex5");

  // int n = 4392, m = 9028;
  // string seq = solve(n, m);
  // print("seq: {}\n", seq);
  // int fill = runSeq(n, m, seq);
  // print("fill left: {}\n", fill);
  // return 0;
  //
  // return 0;

  // return 0;

  // string seq = seqFind(1000, 2000);
  // print("{}\n", seq);
  // return 0;

  // int upTo = 10000;
  // for (int n = 3000; n < upTo; n++) {
  //   for (int m = 2; m <= n; m++) {
  //     bul(n, m);
  //   }
  //   print("n: {}\n", n);
  // }
  // return 0;
  // return 0;
  // srand(time(NULL));
  // for (int i = 0; ; i++) {
  //   int n = rand() % (10000-1000) + 1000;
  //   int m = rand() % (10000-1000) + 1000;
  //   // int m = rand() % (100) + 2;
  //   bool ok = bul(n, m, 2, true);
  //   if (!ok) break;
  // }

  return 0;
}
#endif
