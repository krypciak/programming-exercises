#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int AL = 26;

struct TreeNode {
  string str;
  vector<TreeNode> childrenList{};
  array<int, AL> childrenIndexArr{}; 

  bool isLeaf;
  int accLen;
  int maxAccLen;

  auto operator<=>(const TreeNode &a) const {
    return maxAccLen <=> a.maxAccLen;
  }

  TreeNode* getNodeOrCreate(char c, bool isLeaf) {
    int cv = c - 'a';
    if (childrenIndexArr[cv]) return &childrenList[childrenIndexArr[cv]-1];
    childrenIndexArr[cv] = childrenList.size()+1;
    childrenList.push_back({string(1, c), {}, {}, isLeaf, accLen+1, accLen+1});
    return &childrenList.back();
  }

  void compact() {
    while(childrenList.size() == 1 and !isLeaf) {
      TreeNode child = move(childrenList[0]);
      str += child.str;
      childrenList = move(child.childrenList);
      isLeaf = child.isLeaf;
      accLen += child.str.size();
      maxAccLen = max(maxAccLen, accLen);
    }

    for (TreeNode &node : childrenList) {
      node.compact();
      maxAccLen = max(maxAccLen, node.maxAccLen);
    }

    sortChildren();
  }

  void sortChildren() {
    sort(childrenList.begin(), childrenList.end());
  }

  void prt(int indent = 0) {
    print("{}\"{}\", leaf: {}, maxAccLen: {}: [{}", string(indent*2, ' '), str, isLeaf, maxAccLen, childrenList.size() == 0 ? "" : "\n");
    for (auto child : childrenList) {
      child.prt(indent+1);
    }
    print("{}]\n", childrenList.size() == 0 ? "" : string(indent*2, ' '));
  }

  vector<char> rec() {
    vector<char> actions;
    string prevStr = "";
    int accCommonPrefix = 0;
    rec(actions, "", prevStr, accCommonPrefix);

    return actions;
  }

  void rec(vector<char> &actions, string accStr, string &prevStr, int &accCommonPrefix) {
    accStr += str;
    if (isLeaf) {
      // cost without enter!
      int typeCost = accStr.size();


// #ifdef TEST
//       int accCommonPrefix1 = 0;
//       for (int i = 0; i < min((int)prevStr.size(), (int)accStr.size()) and prevStr[i] == accStr[i]; i++, accCommonPrefix1 = i);  
//       assert(accCommonPrefix1 == accCommonPrefix);
//       // accCommonPrefix = accCommonPrefix1;
// #endif

      int backspaceCount = prevStr.size() - accCommonPrefix;
      int tabToAdd = accStr.size() - accCommonPrefix;
      int tabCost = 1 + backspaceCount + tabToAdd;

      // print("accStr: {}, typeCost: {}, tabCost: {} = 1 + {} + {}\n", accStr, typeCost, tabCost, backspaceCount, tabToAdd);

      // > or >=, doesnt matter
      if (typeCost > tabCost) {
        actions.push_back('T');
        for (int i = 0; i < backspaceCount; i++) actions.push_back('B');
        for (int i = accCommonPrefix; i < (int)accStr.size(); i++) actions.push_back(accStr[i]);
      } else {
        for (auto c : accStr) actions.push_back(c);
      }
      actions.push_back('E');
      prevStr = accStr;
      accCommonPrefix = accStr.size();
      // cout << accCommonPrefix << endl;
    }

    for (auto &child : childrenList) {
      child.rec(actions, accStr, prevStr, accCommonPrefix);
    }
    accCommonPrefix -= str.size();
  }
};

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  ll n;
  cin >> n;

  vector<string> lines(n);
  for (auto &x : lines) cin >> x;
  sort(lines.begin(), lines.end(), [](const string &a, const string &b) {
    return a.size() < b.size();
  });

  TreeNode root{"", {}, {}, false, 0, 0};
  
  for (auto line : lines) {
    TreeNode *node = &root;
    int lineLen = (int)line.size();
    for (int i = 0; i < lineLen; i++) {
      char c = line[i];
      node = node->getNodeOrCreate(c, i == lineLen-1);
    }
  }
  // std::cout << endl << endl;
  // root.prt();
  // std::cout << endl << endl;

  root.compact();

  // root.prt();


  vector<char> actions = root.rec();
  cout << actions.size() << '\n';
  for (const char c : actions) cout << c;
  cout << '\n';

  return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
vector<string> runSeq(string seq) {
  vector<string> lines;
  string currStr = "";
  for (auto c : seq) {
    if (c == 'E') {
      assert(currStr != "");
      lines.push_back(currStr);
      currStr = "";
    } else if (c == 'B') {
      currStr = currStr.substr(0, currStr.size()-1);
    } else if (c == 'T') {
      for (int i = lines.size()-1; i >= 0; i--) {
        if (lines[i].starts_with(currStr)) {
          currStr = lines[i];
          break;
        }
      }
    } else {
      assert(c >= 'a');
      assert(c <= 'z');
      currStr += c;
    }
  }
  return lines;
}
#define TEST_OK
bool isTestOk(string inpS, string expS, string outS) {
  stringstream exp(expS);
  stringstream out(outS);

  int expLen, outLen;
  exp >> expLen;
  out >> outLen;

  if (expLen != outLen) return false;

  stringstream cin(inpS);
  int n;
  cin >> n;

  vector<string> lines(n);
  for (auto &x : lines) cin >> x;

  unordered_set<string> set(lines.begin(), lines.end());

  string outSeq;
  out >> outSeq;

  vector<string> outSeqLines = runSeq(outSeq);
  for (auto line : outSeqLines) {
      if (set.count(line) != 1) return false;
      set.erase(line);
  }

  return set.size() == 0;
}

#include "../../../../tester.h"

int main() {
  test("ex4");
  test("ex3");
  test("ex0");
  test("ex1");
  test("net0");
  test("prz0a");
  test("prz0b");
  test("prz0c");
  test("prz0d");
  test("prz0e");
  test("ex2");
  for (int i = 1; i < 1000; i++) {
    string name = format("net2/{}", i);
    test(name, i % 100 == 0);
  }
  for (int i = 1; i < 500; i++) {
    string name = format("net1/t{}", i);
    test(name, i % 100 == 0);
  }
  for (int i = 1; i < 10000; i++) {
    string name = format("net3/{}", i);
    test(name, i % 1000 == 0);
  }

  return 0;
}
#endif
