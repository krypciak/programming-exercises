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
    if (numericShortestMap[i].size() == 0)
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
  keypadShortestMap['A'] = { {"<"},        {""},         {"v<<"}, {"v<", "<v"}, {"v"},        };
  keypadShortestMap['<'] = { {">^"},       {">>^"},      {""},    {">"},        {">>"},       };
  keypadShortestMap['v'] = { {"^"},        {"^>", ">^"}, {"<"},   {""},         {">"},        };
  keypadShortestMap['>'] = { {"^<", "<^"}, {"^"},        {"<<"},  {"<"},        {""},         };
  // clang-format on

  vector<int> keypadCharToId('v' + 1);
  keypadCharToId['^'] = 0;
  keypadCharToId['A'] = 1;
  keypadCharToId['<'] = 2;
  keypadCharToId['v'] = 3;
  keypadCharToId['>'] = 4;

  for (int i = '<'; i < 'v' + 1; i++) {
    if (keypadShortestMap[i].size() == 0)
      continue;

    for (int j = 0; j < (int)keypadShortestMap[i].size(); j++) {
      for (int k = 0; k < (int)keypadShortestMap[i][j].size(); k++) {
        keypadShortestMap[i][j][k] += 'A';
      }
    }
  }

  for (string code : codes) {
    ll shortestLen = 1000000000000000000;

    struct Entry {
      vector<char> armPos;
      ll len;
      vector<string> leftToProcess;
      int stage;
      int charI;
    };

    const int finalStage = stageCount + 1;

    int ite = 0;
    vector<Entry> toProcess;
    toProcess.push_back({vector<char>(finalStage, 'A'), 0,
                         vector<string>(finalStage, ""), 0, 0});
    while (toProcess.size() > 0) {
      ite++;
      if (ite % 1000000 == 0) {
        print("ite: {}, size: {}\n", ite, toProcess.size());
      }
      vector<Entry> nextToProcess;
      for (auto [armPos, len, leftToProcess, stage, charI] : toProcess) {

        // print("stage {}, len: {}, charI: {}\n", stage, len, charI);
        if (stage == 0) {
          assert(leftToProcess[0].size() == 0);
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
            vector<char> newArmPos = armPos;
            newArmPos[0] = c;

            vector<string> newLeftToProcess = leftToProcess;
            newLeftToProcess[0] = path;
            nextToProcess.push_back(
                {newArmPos, len, newLeftToProcess, 1, charI});
          }
        } else if (stage == 1) {
          assert(leftToProcess[1].size() == 0);
          if (leftToProcess[0].size() == 0) {
            nextToProcess.push_back({armPos, len, leftToProcess, 0, charI + 1});
            continue;
          }

          char c = leftToProcess[0][0];
          leftToProcess[0] = leftToProcess[0].substr(1);

          string path = keypadShortestMap[armPos[1]][keypadCharToId[c]][0];
          armPos[1] = c;
          leftToProcess[1] = path;
          nextToProcess.push_back({armPos, len, leftToProcess, 2, charI});
        } else if (stage >= 2 && stage < finalStage) {
          assert(leftToProcess[stage].size() == 0);
          if (leftToProcess[stage - 1].size() == 0) {
            nextToProcess.push_back(
                {armPos, len, leftToProcess, stage - 1, charI});
            continue;
          }

          char c = leftToProcess[stage - 1][0];
          leftToProcess[stage - 1] = leftToProcess[stage - 1].substr(1);

          string path = keypadShortestMap[armPos[stage]][keypadCharToId[c]][0];
          armPos[stage] = c;
          leftToProcess[stage] = path;
          nextToProcess.push_back(
              {armPos, len, leftToProcess, stage + 1, charI});
        } else if (stage == finalStage) {
          len += leftToProcess[finalStage - 1].size();
          leftToProcess[finalStage - 1] = "";

          nextToProcess.push_back(
              {armPos, len, leftToProcess, finalStage - 1, charI});
        }
      }

      toProcess = nextToProcess;
    }

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

  // printf("solve2 in0 ( expected): %llu\n", solve1("in0", 20));
  // clang-format on
  return 0;
}
