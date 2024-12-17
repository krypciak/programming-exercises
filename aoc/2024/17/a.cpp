#include <bits/stdc++.h>
#include <csignal>
#include <functional>
using namespace std;

typedef unsigned long long ll;

string run(vector<ll> reg, vector<int> prog) {

  function<ll(ll)> get = [&reg](ll val) {
    if (val >= 4)
      return reg[val - 4];

    return val;
  };

#define A 0
#define B 1
#define C 2

  int inst = 0;
  stringstream out;

  // clang-format off
  vector<function<void(int)>> operations{
    [&reg, &get](int combo) {
      // adv 0
      reg[A] = reg[A] >> get(combo);
    },
    [&reg](int literal) {
      // bxl 1
      reg[B] = reg[B] ^ literal;
    },
    [&reg, &get](int combo) {
      // bst 2
      reg[B] = get(combo) % 8;
    },
    [&reg, &inst](int literal) {
      // jnz 3
      if (reg[A] == 0) return;
      inst = literal - 2;
    },
    [&reg](int _) {
      // bxc 4
      reg[B] = reg[B] ^ reg[C];
    },
    [&reg, &get, &out](int combo) {
      // out 5
      out << get(combo) % 8 << ",";
    },
    [&reg, &get](int combo) {
      // bdv 6
      reg[B] = reg[A] >> get(combo);
    },
    [&reg, &get](int combo) {
      // cdv 7
      reg[C] = reg[A] >> get(combo);
    },
  };
  // clang-format on

  for (; inst < (int)(prog.size() - (prog.size() % 2)); inst += 2) {
    int opcode = prog[inst];
    assert(opcode >= 0 && opcode <= 7);
    int operand = prog[inst + 1];
    assert(operand >= 0 && operand <= 7);

    operations[opcode](operand);
  }

  string res = out.str();
  res = res.substr(0, res.size() - 1);

  return res;
}

pair<vector<ll>, vector<int>> input(string fileName) {
  ifstream cin(fileName);

  string line;

  vector<ll> reg(3);
  for (int i = 0; i < 3; i++) {
    getline(cin, line);
    transform(begin(line), end(line), begin(line),
              [](char c) { return c >= '0' && c <= '9' ? c : ' '; });

    stringstream ss(line);
    long long num;
    ss >> num;
    reg[i] = num;
  }
  getline(cin, line);
  getline(cin, line);
  transform(begin(line), end(line), begin(line),
            [](char c) { return c >= '0' && c <= '9' ? c : ' '; });

  vector<int> prog;
  stringstream ss(line);
  int num;
  while (ss >> num) {
    prog.push_back(num);
  }

  return {reg, prog};
}

string solve1(string fileName) {
  auto [reg, prog] = input(fileName);
  return run(reg, prog);
}

bool solve2Check(ll iterA) {
  const vector<ll> expected = {2, 4, 1, 1, 7, 5, 1, 4, 0, 3, 4, 5, 5, 5, 3, 0};

  //          0  .  1  .  2  .  3  .  4  .  5  .  6  .  7  .
  // Program: 2, 4, 1, 1, 7, 5, 1, 4, 0, 3, 4, 5, 5, 5, 3, 0

  ll a = iterA;
  ll b = 0;
  ll c = 0;

  int expectedI = 0;

  for (; a != 0 && expectedI < 16; expectedI++) {
    // 0
    b = a % 8;
    // 1
    b = b ^ 1;
    // 2
    c = a >> b;
    // 3
    b = b ^ 4;
    // 4
    a = a >> 3;
    // 5
    b = b ^ c;

    if (expected[expectedI] != b % 8) {
      return false;
    }
  }
  if (expectedI == 16) {
    return true;
  }
  return false;
};

ll solve2() {
  const vector<int> expected = {2, 4, 1, 1, 7, 5, 1, 4, 0, 3, 4, 5, 5, 5, 3, 0};

  struct Entry {
    int i;
    ll a;
    ll fullA;

    bool operator>(const Entry &e) const { return a > e.a; }
  };
  priority_queue<Entry, vector<Entry>, greater<Entry>> queue;
  queue.push({0, 0});
  long long ite = 0;

  ll min = 202322936867377;
  while (queue.size() > 0) {
    auto [i, ea, efullA] = queue.top();
    queue.pop();

    for (ll origA = 0; origA < 256; origA++) {
      ll fullA = efullA + (origA << (i * 8));
      ll a = fullA >> (i * 3);

      ll b = a & 7;
      b = b ^ 1;
      ll c = a >> b;
      b = b ^ 4;
      a = a >> 3;
      b = b ^ c;
      b = b & 7;

      if (b == (ll)expected[i]) {
        const int MAX = 6;
        if (i + 1 == MAX) {
          vector<ll> reg = {fullA, 0, 0};
          if (solve2Check(fullA)) {
            string proof = run(reg, expected);
            printf("i: %d, %llu, solution! proof: %s\n", i, fullA,
                   proof.c_str());
            if (fullA < min) {
              min = fullA;
              printf("new minimum\n");
            }
          }
        } else if (a != 0) {
          queue.push({i + 1, a, fullA});

          ite++;
          if (ite % 10000000 == 0) {
            vector<ll> reg = {fullA, 0, 0};
            string proof = run(reg, expected);
            printf("ite: %llu, size: %d, i: %d, proof: %s\n", ite,
                   (int)queue.size(), i, proof.c_str());
          }
        }
      }
    }
  }
  return min;
}

int main() {
  // clang-format off
  // printf("solve1 ex0 (4,6,3,5,6,3,5,2,1,0 expected): %s\n", solve1("ex0").c_str());
  // printf("solve1 in0 (5,1,4,0,5,1,0,2,6 expected): %s\n", solve1("in0").c_str());
  // printf("solve1 in1 ( expected): %s\n", solve1("in1").c_str());
  // return 0;

  printf("solve2 in0 (202322936867370 expected): %llu\n", solve2());

  // clang-format on

  return 0;
}
