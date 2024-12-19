#include <bits/stdc++.h>
#include <csignal>
using namespace std;

typedef unsigned long long ll;

ll solve1(string inputFile, bool part2 = false) {
  ifstream cin(inputFile);

  string towelsStr;
  getline(cin, towelsStr);
  transform(begin(towelsStr), end(towelsStr), begin(towelsStr),
            [](char c) { return c == ',' ? ' ' : c; });
  stringstream ss(towelsStr);

  string line;
  vector<string> towels;
  while (ss >> line) {
    towels.push_back(line);
  }
  getline(cin, line);

  vector<string> inputs;
  while (getline(cin, line)) {
    inputs.push_back(line);
  }

  sort(begin(towels), end(towels),
       [](const string &a, const string &b) { return a.size() < b.size(); });

  const vector<char> allowed = {'w', 'u', 'b', 'r', 'g'};
  vector<int> charToId('w' + 1);
  charToId['w'] = 0;
  charToId['u'] = 1;
  charToId['b'] = 2;
  charToId['r'] = 3;
  charToId['g'] = 4;

  const int s = 5;

  struct Node {
    vector<Node *> next;
    bool canEnd;
  };

  Node prefixTree = {vector<Node *>(s), false};

  function<void(Node *, char, string)> addToTree =
      [&addToTree, charToId](Node *parent, int id, string rest) {
        if (parent->next[id] == nullptr) {
          parent->next[id] = new Node{vector<Node *>(s), false};
        }
        if (rest.size() > 0) {
          addToTree(parent->next[id], charToId[rest[0]], rest.substr(1));
        } else {
          parent->next[id]->canEnd = true;
        }
      };

  function<void(Node *, int)> printPrefixTree =
      [&prefixTree, allowed, &printPrefixTree](Node *parent, int depth) {
        for (int i = 0; i < s; i++) {
          if (parent->next[i] == nullptr)
            continue;
          print("{}-> {} {}\n", string(depth, ' '), allowed[i],
                parent->next[i]->canEnd ? "canEnd" : "");
          printPrefixTree(parent->next[i], depth + 2);
        }
      };

  for (string t : towels) {
    addToTree(&prefixTree, charToId[t[0]], t.substr(1));
  }

  // printPrefixTree(&prefixTree, 0);

  ll totalSum = 0;
  for (string inp : inputs) {
    const int toCache = (int)inp.size();
    vector<ll> cache(inp.size(), 0);

    function<ll(int, Node *, bool)> iter =
        [&prefixTree, inp, charToId, &iter, &cache,
         &totalSum](int pos, Node *node, bool part2) {
          char c = inp[pos];
          int id = charToId[c];
          Node *next = node->next[id];
          if (next == nullptr)
            return (ll)0;

          ll retSum = 0;

          if (next->canEnd) {
            if (pos == (int)inp.size() - 1) {
              return (ll)1;
            }
            if (part2) {
              retSum += cache[pos + 1];
              // retSum += iter(pos + 1, &prefixTree, part2);
            } else if (iter(pos + 1, &prefixTree, part2)) {
              return (ll)1;
            }
          }

          if (pos == (int)inp.size() - 1)
            return (ll)0;

          return retSum + iter(pos + 1, next, part2);
        };

    ll res = iter(0, &prefixTree, false);
    if (res == 0)
      continue;

    assert(res == 1);

    if (!part2) {
      totalSum++;
      continue;
    }

    for (int pos = inp.size() - 1; pos >= (int)inp.size() - toCache; pos--) {
      ll sum = iter(pos, &prefixTree, true);
      cache[pos] = sum;
    }
    totalSum += cache[0];
  }

  function<void(Node *)> deconstructTree = [&deconstructTree](Node *parent) {
    for (int i = 0; i < s; i++) {
      if (parent->next[i] != nullptr) {
        deconstructTree(parent->next[i]);
        delete parent->next[i];
      }
    }
  };
  deconstructTree(&prefixTree);

  return totalSum;
}

int main() {
  // clang-format off
  printf("solve1 ex0 (6 expected): %llu\n", solve1("ex0"));
  printf("solve1 ex1 (1 expected): %llu\n", solve1("ex1"));
  printf("solve1 in0 (363 expected): %llu\n", solve1("in0"));

  printf("solve2 ex0 (16 expected): %llu\n", solve1("ex0", true));
  printf("solve1 in0 (642535800868438 expected): %llu\n", solve1("in0", true));
  // clang-format on

  return 0;
}
