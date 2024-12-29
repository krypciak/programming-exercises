#include <bits/stdc++.h>
#include <stdexcept>

using namespace std;

typedef unsigned long long ll;

ll solve1(string inputFile) {
  ifstream cin(inputFile);

  struct val {
    int value = 0;
    bool incomp = false;
  };
  unordered_map<string, val> state;

  string line;
  while (getline(cin, line)) {
    if (line == "")
      break;
    transform(begin(line), end(line), begin(line),
              [](char c) { return c == ':' ? ' ' : c; });

    stringstream ss(line);
    string name;
    int value;
    ss >> name >> value;

    state[name] = {value};
  }

  enum Ope { AND, OR, XOR };
  struct Gate {
    string a, b;
    Ope ope;
    string res;
  };

  vector<Gate> gates;
  while (getline(cin, line)) {
    transform(begin(line), end(line), begin(line),
              [](char c) { return (c == '-' || c == '>') ? ' ' : c; });

    stringstream ss(line);
    string a, b, opeStr, res;
    ss >> a >> opeStr >> b >> res;

    gates.push_back({a, b,
                     opeStr == "AND"   ? AND
                     : opeStr == "XOR" ? XOR
                     : opeStr == "OR"  ? OR
                                       : throw invalid_argument(opeStr),
                     res});
  }

  unordered_map<string, vector<pair<string, Ope>>> graph;
  unordered_map<string, vector<string>> reverseGraph;

  for (auto [a, b, ope, res] : gates) {
    graph[a].push_back({res, ope});
    graph[b].push_back({res, ope});

    reverseGraph[res].push_back(a);
    reverseGraph[res].push_back(b);
  }

  vector<string> leafs;
  for (auto [a, _] : graph) {
    if (reverseGraph[a].empty()) {
      leafs.push_back(a);
    }
  }

  while (!leafs.empty()) {
    vector<string> nextLeafs;
    for (string a : leafs) {
      assert(reverseGraph[a].empty());
      assert(!state[a].incomp);

      for (auto [res, ope] : graph[a]) {
        if (!state.contains(res) || !state[res].incomp) {
          state[res] = {state[a].value, true};
        } else {
          int resVal;
          int sv = state[res].value;
          int av = state[a].value;
          if (ope == AND) {
            resVal = sv and av;
          } else if (ope == OR) {
            resVal = sv or av;
          } else if (ope == XOR) {
            resVal = sv xor av;
          }
          state[res] = {resVal, false};

          reverseGraph.erase(res);
          nextLeafs.push_back(res);
        }
      }
      graph.erase(a);
    }
    leafs = nextLeafs;
  }

  bitset<100> zRegisteres;
  for (int i = 0; i < 100; i++) {
    string key = format("z{:0>2}", i);
    if (!state.contains(key))
      break;
    assert(!state[key].incomp);
    int value = state[key].value;
    assert(value == 0 || value == 1);
    zRegisteres[i] = value;
  }

  return zRegisteres.to_ulong();
}

string solve2(string inputFile) {
  ifstream cin(inputFile);

  struct val {
    int value = 0;
    bool incomp = false;
    string oldName;
  };
  unordered_map<string, val> state;

  string line;
  while (getline(cin, line)) {
    if (line == "")
      break;
    transform(begin(line), end(line), begin(line),
              [](char c) { return c == ':' ? ' ' : c; });

    stringstream ss(line);
    string name;
    int value;
    ss >> name >> value;

    state[name] = {value};
  }
  const auto initialState = state;

  struct Gate {
    string a, b;
    string ope;
    string res;

    bool operator<(const Gate &v) const {
      return lexicographical_compare(begin(a), end(a), begin(v.a), end(v.a));
    }
  };

  vector<Gate> gates;
  while (getline(cin, line)) {
    transform(begin(line), end(line), begin(line),
              [](char c) { return (c == '-' || c == '>') ? ' ' : c; });

    stringstream ss(line);
    string a, b, opeStr, res;
    ss >> a >> opeStr >> b >> res;

    gates.push_back({a, b, opeStr, res});
  }

  unordered_map<string, vector<pair<string, string>>> graph;
  unordered_map<string, vector<string>> reverseGraph;

  for (auto [a, b, ope, res] : gates) {
    graph[a].push_back({res, ope});
    graph[b].push_back({res, ope});

    reverseGraph[res].push_back(a);
    reverseGraph[res].push_back(b);
  }

  vector<string> leafs;
  for (auto [a, _] : graph) {
    if (reverseGraph[a].empty()) {
      leafs.push_back(a);
    }
  }

  vector<vector<Gate>> hist;
  for (int ite = 0; !leafs.empty(); ite++) {
    hist.push_back(vector<Gate>());
    vector<string> nextLeafs;
    for (string a : leafs) {
      assert(reverseGraph[a].empty());
      assert(!state[a].incomp);

      for (auto [res, ope] : graph[a]) {
        if (!state.contains(res) || !state[res].incomp) {
          state[res] = {state[a].value, true, a};
        } else {
          int resVal;
          int sv = state[res].value;
          int av = state[a].value;
          if (ope == "AND") {
            resVal = sv and av;
          } else if (ope == "OR") {
            resVal = sv or av;
          } else if (ope == "XOR") {
            resVal = sv xor av;
          }

          {
            string b = state[res].oldName;
            if (a.starts_with("x")) {
              hist[ite].push_back({a, b, ope, res});
            } else {
              hist[ite].push_back({b, a, ope, res});
            }
          }
          state[res] = {resVal, false};

          reverseGraph.erase(res);
          nextLeafs.push_back(res);
        }
      }
      graph.erase(a);
    }
    sort(begin(hist[ite]), end(hist[ite]));
    leafs = nextLeafs;
  }

  struct AddEntry {
    string x;
    string a;
    string orr;
    string tmp;
  };
  vector<AddEntry> adds(100);
  unordered_map<string, string> knownRegToName;
  unordered_map<string, string> nameToKnownReg;

  auto rerunKnownName = [&] {
    for (auto [a, b, ope, res] : hist[0]) {
      if (a.starts_with("x") && b.starts_with("y")) {
        int index = stoi(a.substr(1));
        assert(index == stoi(b.substr(1)));

        if (ope == "AND") {
          adds[index].a = res;
          string key = "a" + to_string(index);
          knownRegToName[res] = key;
          knownRegToName[key] = res;
        } else if (ope == "XOR") {
          adds[index].x = res;
          string key = "x" + to_string(index);
          knownRegToName[res] = key;
          nameToKnownReg[key] = res;
        }
      }
    }
  };
  rerunKnownName();

  vector<pair<string, string>> swapped;
  auto swapResults = [&](int ite, int k1, string expRes) {
    string res = hist[ite][k1].res;

    int swapIte = -1, swapK;
    for (int j = 0; j < (int)hist.size(); j++) {
      for (int k2 = 0; k2 < (int)hist[j].size(); k2++) {
        if (hist[j][k2].res == expRes) {
          swapIte = j;
          swapK = k2;
          goto swapFound;
        }
      }
    }
    assert(swapIte != -1);
  swapFound:
    hist[swapIte][swapK].res = res;
    hist[ite][k1].res = expRes;
    rerunKnownName();

    swapped.push_back({res, expRes});
  };
  auto swapResultsFind = [&](string look, string expRes) {
    for (int ite = 0; ite < (int)hist.size(); ite++) {
      for (int k1 = 0; k1 < (int)hist[ite].size(); k1++) {
        if (hist[ite][k1].res == look) {
          return swapResults(ite, k1, expRes);
        }
      }
    }
  };

  int resIndex = 1;
  for (int ite = 1; ite < (int)hist.size(); ite++) {
    int thisIteResIndex = resIndex;
    for (int k1 = 0; k1 < (int)hist[ite].size(); k1++) {
      auto [a, b, ope, res] = hist[ite][k1];
      // print("{} {} {} = {}\n", a, ope, b, res);

      if (ope == "XOR") {
        // mwp is xor resIndex
        string exp1 = "x" + to_string(thisIteResIndex);
        bool exp1ok = knownRegToName[a] == exp1 || knownRegToName[b] == exp1;

        // tsk or res
        string exp2Or = adds[thisIteResIndex].orr;
        bool exp2ok = exp2Or == "" || a == exp2Or || b == exp2Or;

        if (!exp1ok && !exp2ok) {
          throw invalid_argument("fuck");
        }

        if (!exp1ok) {
          assert(exp2ok);
          string toSwap = a == exp2Or ? b : a;
          // print("problem! nor {} nor {} is equal to expected {}\n",
          //       knownRegToName[a], knownRegToName[b], exp1);

          string with = nameToKnownReg[exp1];

          swapResultsFind(toSwap, with);
        }

        if (!exp2ok) {
          print("exp2 not ok :( expected {} got {} {}\n", exp2Or, a, b);
          return "";
        }

        if (!res.starts_with("z")) {
          string expRes = format("z{:0>2}", thisIteResIndex);
          // print("problem! expected {}, got {}\n", expectedRes, res);

          swapResults(ite, k1, expRes);
        }
        resIndex++;
      } else if (ope == "AND") {
        adds[thisIteResIndex].tmp = res;

        // string exp1 = "x" + to_string(thisIteResIndex);
        // if (knownRegToName[a] != exp1 && knownRegToName[b] != exp1) {
        //   print("problem! nor {} nor {} equal to expected {}\n",
        //         knownRegToName[a], knownRegToName[b], exp1);
        //   return "";
        // }
      } else if (ope == "OR") {
        adds[thisIteResIndex].orr = res;

        // string exp1 = "a" + to_string(thisIteResIndex - 1);
        // if (knownRegToName[a] != exp1 && knownRegToName[b] != exp1) {
        //   print("problem! nor {} nor {} is equal to expected {}\n",
        //         knownRegToName[a], knownRegToName[b], exp1);
        //   return "";
        // }
      }
    }
    // print("\n");
  }
  // print("swap count: {}\n", swapped.size());

  vector<string> flat;
  for (auto [a, b] : swapped) {
    flat.push_back(a);
    flat.push_back(b);
  }
  sort(begin(flat), end(flat));

  string joined = "";
  for (string str : flat) {
    joined += str + ",";
  }

  joined = joined.substr(0, joined.size() - 1);
  return joined;
}

int main() {
  // clang-format off
  // printf("solve1 ex0 (4 expected): %llu\n", solve1("ex0"));
  // printf("solve1 ex1 (2024 expected): %llu\n", solve1("ex1"));
  // printf("solve1 ex2 (1 expected): %llu\n", solve1("ex2"));
  // printf("solve1 in0 (55920211035878 expected): %llu\n", solve1("in0"));
 
  print("solve2 in0 (btb,cmv,mwp,rdg,rmj,z17,z23,z30 expected): {}\n", solve2("in0"));
  print("solve2 das.txt ( expected): {}\n", solve2("das.txt"));
  // clang-format on
  return 0;
}
