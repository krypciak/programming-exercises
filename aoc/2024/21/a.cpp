#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct Vec2 {
  int x, y;

  bool operator==(const Vec2 &a) const { return x == a.x && y == a.y; }
};

typedef unsigned long long ll;

ll solve1(string inputFile, int stageCount) {
  ifstream cin(inputFile);

  vector<string> codes;
  string line;
  while (getline(cin, line)) {
    codes.push_back(line);
  }

  ll sum = 0;

  // clang-format off
  /*
    +---+---+---+
    | 7 | 8 | 9 |
    +---+---+---+
    | 4 | 5 | 6 |
    +---+---+---+
    | 1 | 2 | 3 |
    +---+---+---+
        | 0 | A (10) |
        +---+---+
  */
  vector<vector<vector<string>>> numericShortestMap('A'+1);
  /*                           0                1                 2               3                 4               5               6               7                 8                 9                 A                 */
  numericShortestMap['0'] = { {""},             {"^<"},           {"^"},          {"^>", "^>"},     {"^^<"},        {"^^"},         {"^^>", ">^^"}, {"^^^<"},         {"^^^"},          {"^^^>", ">^^^"}, {">"},            };
  numericShortestMap['1'] = { {">v"},           {""},             {">"},          {">>"},           {"^"},          {"^>", ">^"},   {"^>>", ">>^"}, {"^^"},           {"^^>", ">^^"},   {"^^>>", ">>^^"}, {">>v"},          };
  numericShortestMap['2'] = { {"v"},            {"<"},            {""},           {">"},            {"^<", "<^"},   {"^"},          {"^>", ">^"},   {"^^<", "<^^"},   {"^^"},           {"^^>", ">^^"},   {"v>", ">v"},     };
  numericShortestMap['3'] = { {"v<", "<v"},     {"<<"},           {"<"},          {""},             {"^<<", "<<^"}, {"^<", "<^"},   {"^"},          {"^^<<", "<<^^"}, {"^^<", "<^^"},   {"^^"},           {"v"},            };
  numericShortestMap['4'] = { {">vv"},          {"v"},            {"v>", ">v"},   {">>v", "v>>"},   {""},           {">"},          {">>"},         {"^"},            {"^>", ">^"},     {"^>>", ">>^"},   {">>vv"},         };
  numericShortestMap['5'] = { {"vv"},           {"v<", "<v"},     {"v"},          {"v>", ">v"},     {"<"},          {""},           {">"},          {"^<", "<^"},     {"^"},            {"^>", ">^"},     {"vv>"},          };
  numericShortestMap['6'] = { {"vv<", "<vv"},   {"v<<", "v<<"},   {"v<", "<v"},   {"v"},            {"<<"},         {"<"},          {""},           {"^<<", "<<^"},   {"^<", "<^"},     {"^"},            {"vv"},           };
  numericShortestMap['7'] = { {">vvv"},         {"vv"},           {"vv>", ">vv"}, {"vv>>", ">>vv"}, {"v"},          {"v>", ">v"},   {"v>>", ">>v"}, {""},             {">"},            {">>"},           {">>vvv"},        };
  numericShortestMap['8'] = { {"vvv"},          {"vv<", "<vv"},   {"vv"},         {"vv>", ">vv"},   {"v<", "<v"},   {"v"},          {"v>", ">v"},   {"<"},            {""},             {">"},            {"vvv>", ">vvv"}, };
  numericShortestMap['9'] = { {"vvv<", "<vvv"}, {"vv<<", "<<vv"}, {"vv<", "<vv"}, {"vv"},           {"v<<", "<<v"}, {"v<", "<v"},   {"v"},          {"<<"},           {"<"},            {""},             {"vvv"},          };
  numericShortestMap['A'] = { {"<"},            {"^<<"},          {"^<", "<^"},   {"^"},            {"^^<<", },     {"^^<", "<^^"}, {"^^"},         {"^^^<<"},        {"^^^<", "<^^^"}, {"^^^"},          {""},             };
  // clang-format on
  vector<int> numericCharToId('A' + 1);
  for (int c = '0'; c <= '9'; c++) {
    numericCharToId[c] = c - '0';
  }
  numericCharToId['A'] = 10;

  for (int i = '0'; i < 'A' + 1; i++) {
    if (numericShortestMap[i].empty())
      continue;

    for (int j = 0; j < (int)numericShortestMap[i].size(); j++) {
      for (int k = 0; k < (int)numericShortestMap[i][j].size(); k++) {
        numericShortestMap[i][j][k] += 'A';
      }
    }
  }
  // clang-format off
  /*
        +---+---+
        | ^ | A |
    +---+---+---+
    | < | v | > |
    +---+---+---+
  */
  vector<vector<vector<string>>> keypadShortestMap('v'+1);
  //     /*                  ^ (0)         A (1)         < (2)    v (3)         > (4)         */
  keypadShortestMap['^'] = { {""},         {">"},        {"v<"},  {"v"},        {"v>", ">v"}, };
  keypadShortestMap['A'] = { {"<"},        {""},         {"v<<"}, {/*"v<",*/ "<v"}, {"v"},        };
  keypadShortestMap['<'] = { {">^"},       {">>^"},      {""},    {">"},        {">>"},       };
  keypadShortestMap['v'] = { {"^"},        {"^>", ">^"}, {"<"},   {""},         {">"},        };
  keypadShortestMap['>'] = { {/*"^<",*/ "<^"}, {"^"},        {"<<"},  {"<"},        {""},         };
  // clang-format on

  vector<int> keypadCharToId('v' + 1);
  keypadCharToId['^'] = 0;
  keypadCharToId['A'] = 1;
  keypadCharToId['<'] = 2;
  keypadCharToId['v'] = 3;
  keypadCharToId['>'] = 4;

  for (int i = '<'; i < 'v' + 1; i++) {
    if (keypadShortestMap[i].empty())
      continue;

    for (int j = 0; j < (int)keypadShortestMap[i].size(); j++) {
      for (int k = 0; k < (int)keypadShortestMap[i][j].size(); k++) {
        keypadShortestMap[i][j][k] += 'A';
      }
    }
  }

  for (string code : codes) {
    ll shortestLen = 10000000000000000000llu;

    struct Entry {
      string armPos;
      ll len;
      vector<string> leftToProcess;
      int stage;
      int charI;
      int id;
      vector<string> origExp;
      string path;
    };
    const int finalStage = stageCount + 1;

    struct CacheEntry {
      ll sum;
      int startId;
      bool done;
    };
    unordered_map<string, CacheEntry> cache;

    auto getCacheKey = [](int stage, string exp) -> string {
      return to_string(stage) + exp;
    };

    int cacheHits = 0;

    vector<Entry> toProcess;
    toProcess.push_back({string(finalStage, 'A'), 0,
                         vector<string>(finalStage, ""), 0, 0, -1,
                         vector<string>(finalStage), ""});

    int idklew = 0;
    while (toProcess.size() > 0) {
      vector<Entry> nextToProcess;
      for (auto [armPos, len, leftToProcess, stage, charI, id, origExp,
                 expanded] : toProcess) {

        if (stage == 0) {
          assert(leftToProcess[0].empty());
          if (charI >= (int)code.size()) {
            if (len < shortestLen) {
              shortestLen = len;
            }
            continue;
          }
          char c = code[charI];
          vector<string> paths =
              numericShortestMap[armPos[0]][numericCharToId[c]];

          for (string path : paths) {
            armPos[0] = c;
            leftToProcess[0] = path;
            origExp[0] = path;
            nextToProcess.push_back({armPos, len, leftToProcess, 1, charI,
                                     idklew++, origExp, expanded});
          }
        } else if (stage == 1) {
          assert(leftToProcess[1].empty());
          if (leftToProcess[0].empty()) {
            nextToProcess.push_back({armPos, len, leftToProcess, 0, charI + 1,
                                     id, origExp, expanded});
            continue;
          }

          char c = leftToProcess[0][0];
          leftToProcess[0] = leftToProcess[0].substr(1);
          // string path = keypadShortestMap[armPos[1]][keypadCharToId[c]][0];
          vector<string> paths =
              keypadShortestMap[armPos[1]][keypadCharToId[c]];

          for (string path : paths) {
            armPos[1] = c;
            leftToProcess[1] = path;
            origExp[1] = path;
            nextToProcess.push_back(
                {armPos, len, leftToProcess, 2, charI, id, origExp, expanded});
            break;
          }
        } else if (stage >= 2 && stage < finalStage) {
          const int minStageCache = 0;

          assert(leftToProcess[stage].empty());
          if (leftToProcess[stage - 1].empty()) {

            if (stage > minStageCache && stage != finalStage - 1) {
              auto cacheKey = getCacheKey(stage, origExp[stage - 1]);
              assert(cache.count(cacheKey) > 0);
              CacheEntry *e = &cache[cacheKey];
              if (!e->done && id == e->startId) {
                e->sum = len - e->sum;
                e->done = true;
              }
            }

            nextToProcess.push_back({armPos, len, leftToProcess, stage - 1,
                                     charI, id, origExp, expanded});
            continue;
          }

          if (stage > minStageCache && stage != finalStage - 1) {
            bool isFirst = true;
            for (int i = stage; i < finalStage; i++) {
              if (armPos[i] != 'A') {
                isFirst = false;
                break;
              }
            }
            if (isFirst) {
              // print("isFirstOrLast stage {}, armPos: {}\n", stage, armPos);
              auto cacheKey = getCacheKey(stage, origExp[stage - 1]);
              if (cache.count(cacheKey) == 0) {
                // print("cache start id: {}, key: {}\n", id, cacheKey);
                cache[cacheKey] = {len, id, false};
              } else {
                CacheEntry *e = &cache[cacheKey];
                if (e->done) {
                  len += e->sum;
                  cacheHits++;
                  if (cacheHits % 100000 == 0) {
                    print("skipping at stage {}, armPos: {}, add: {}\n", stage,
                          armPos, e->sum);
                    print("where char '{}' expanded into {}\n",
                          origExp[stage - 1], leftToProcess[stage - 1]);
                  }
                  leftToProcess[stage - 1] = "";
                  nextToProcess.push_back({armPos, len, leftToProcess, stage,
                                           charI, id, origExp, expanded});
                  continue;
                }
              }
            }
          }

          char c = leftToProcess[stage - 1][0];
          leftToProcess[stage - 1] = leftToProcess[stage - 1].substr(1);

          // string path =
          // keypadShortestMap[armPos[stage]][keypadCharToId[c]][0];
          vector<string> paths =
              keypadShortestMap[armPos[stage]][keypadCharToId[c]];

          for (string path : paths) {
            armPos[stage] = c;
            leftToProcess[stage] = path;
            origExp[stage] = path;
            nextToProcess.push_back({armPos, len, leftToProcess, stage + 1,
                                     charI, id, origExp, expanded});

            break;
          }
        } else if (stage == finalStage) {
          len += leftToProcess[finalStage - 1].size();
          string das = leftToProcess[finalStage - 1];
          string newPath = expanded + das + " ";

          leftToProcess[finalStage - 1] = "";

          nextToProcess.push_back({armPos, len, leftToProcess, finalStage - 1,
                                   charI, id, origExp, newPath});
        }
      }

      toProcess = nextToProcess;
    }
    // cout << endl;
    // print("------------------shortest len: {} -----------------\n",
    // shortestLen);

    auto calcNumericPart = [&code]() -> int {
      string newCode = code;
      transform(begin(newCode), end(newCode), begin(newCode),
                [](char c) { return (c >= '0' && c <= '9') ? c : ' '; });
      int num = stoi(newCode);

      return num;
    };
    int numericPart = calcNumericPart();

    sum += numericPart * shortestLen;
  }

  return sum;
}

int main() {
  // clang-format off
  printf("solve1 ex0 (126384 expected): %llu\n", solve1("ex0", 2));
  printf("solve1 in0 (164960 expected): %llu\n", solve1("in0", 2));
  printf("solve1 ex0 ( expected): %llu\n", solve1("ex1", 2));

  printf("solve2 in0 ( expected): %llu\n", solve1("in0", 25));
  // clang-format on
  return 0;
}
