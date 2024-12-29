#include <bits/stdc++.h>

using namespace std;

struct Vec2 {
  int x, y;

  bool operator==(const Vec2 &a) const { return x == a.x && y == a.y; }
};

typedef unsigned long long ll;

ll solve1(string inputFile) {
  ifstream cin(inputFile);

  unordered_map<string, unordered_set<string>> graph;

  string line;
  while (getline(cin, line)) {
    transform(begin(line), end(line), begin(line),
              [](char c) { return c == '-' ? ' ' : c; });

    stringstream ss(line);
    string from, to;
    ss >> from >> to;

    if (graph.count(from) == 0)
      graph[from] = unordered_set<string>();
    graph[from].insert(to);
    if (graph.count(to) == 0)
      graph[to] = unordered_set<string>();
    graph[to].insert(from);
  }

  set<string> uniq;

  for (auto [orig, _] : graph) {
    for (string n1 : graph[orig]) {
      for (string n2 : graph[orig]) {
        if (n1 == n2)
          continue;

        if (graph[n1].count(n2) == 1) {
          if (orig.starts_with('t') || n1.starts_with('t') ||
              n2.starts_with('t')) {
            vector<string> seq = {orig, n1, n2};
            sort(begin(seq), end(seq));
            uniq.insert(format("{}{}{}", seq[0], seq[1], seq[2]));
          }
        }
      }
    }
  }

  return uniq.size();
}

string solve2(string inputFile) {
  ifstream cin(inputFile);

  typedef short Id;
  unordered_map<string, Id> stringToId;
  Id nextId = 0;

  const Id idArrSize = 520;
  vector<string> idToString(idArrSize);
  vector<unordered_set<Id>> graph(idArrSize);

  string line;
  while (getline(cin, line)) {
    transform(begin(line), end(line), begin(line),
              [](char c) { return c == '-' ? ' ' : c; });

    stringstream ss(line);
    string from, to;
    ss >> from >> to;

    if (stringToId.count(from) == 0) {
      idToString[nextId] = from;
      stringToId[from] = nextId;
      nextId++;
    }
    Id fromId = stringToId[from];

    if (stringToId.count(to) == 0) {
      idToString[nextId] = to;
      stringToId[to] = nextId;
      nextId++;
    }
    Id toId = stringToId[to];

    graph[fromId].insert(toId);
    graph[toId].insert(fromId);
  }

  vector<unordered_set<Id>> allCliques;
  function<void(unordered_set<Id> &&, unordered_set<Id> &&,
                unordered_set<Id> &&)>
      bron = [&graph, &bron, &allCliques](unordered_set<Id> &&R,
                                          unordered_set<Id> &&P,
                                          unordered_set<Id> &&X) -> void {
    if (P.empty() && X.empty()) {
      allCliques.push_back(R);
      return;
    }

    while (!P.empty()) {
      Id v = *P.begin();
      unordered_set<Id> newR = R;
      newR.insert(v);
      unordered_set<Id> newP;
      for (Id p : P) {
        if (graph[v].contains(p)) {
          newP.insert(p);
        }
      }
      unordered_set<Id> newX;
      for (Id x : X) {
        if (graph[v].contains(x)) {
          newX.insert(x);
        }
      }
      bron(std::move(newR), std::move(newP), std::move(newX));
      P.erase(v);
      X.insert(v);
    }
  };

  unordered_set<Id> vertices;
  generate_n(inserter(vertices, vertices.end()), nextId,
             [&] { return vertices.size(); });

  bron({}, std::move(vertices), {});

  unordered_set<Id> maxClique;
  for (unordered_set<Id> &clique : allCliques) {
    if (maxClique.size() < clique.size()) {
      maxClique = clique;
    }
  }

  vector<string> resStrVec(maxClique.size());
  transform(begin(maxClique), end(maxClique), begin(resStrVec),
            [&idToString](const Id &id) { return idToString[id]; });
  sort(begin(resStrVec), end(resStrVec));

  string res = "";
  for (string str : resStrVec) {
    res += str + ",";
  }
  res = res.substr(0, res.size() - 1);

  return res;
}

int main() {
  // clang-format off
  // printf("solve1 ex0 (7 expected): %llu\n", solve1("ex0"));
  // printf("solve1 in0 ( expected): %llu\n", solve1("in0"));
 
  print("solve2 ex1 (co,de,ka,ta expected): {}\n", solve2("ex0"));
  print("solve2 in0 (aa,cf,cj,cv,dr,gj,iu,jh,oy,qr,xr,xy,zb expected): {}\n", solve2("in0"));
  // clang-format on
  return 0;
}
