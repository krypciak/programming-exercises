#include <bits/stdc++.h>
#include <string>

using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  map<string, map<string, string>> G = {
      {"BEGIN", {{"C", "New"}}},
      {"New", {{"S", "Draft"}}},
      {"Draft",
       {
           {"S", "Draft"},
           {"B", "Preliminary Review"},
       }},
      {"Preliminary Review",
       {
           {"S", "Preliminary Review"},
           {"R", "Waiting Preliminary"},
           {"A", "Final Review"},
           {"X", "Rejected"},
       }},
      {"Waiting Preliminary",
       {
           {"I", "Preliminary Review"},
       }},
      {"Final Review",
       {
           {"S", "Final Review"},
           {"R", "Waiting Final"},
           {"A", "Approved"},
           {"X", "Rejected"},
       }},
      {"Waiting Final",
       {
           {"I", "Final Review"},
       }},
      {"Approved",
       {
           {"N", "Customer Notified"},
       }},
      {"Rejected",
       {
           {"N", "Customer Notified"},
       }},
      {"Customer Notified", {}},
  };

  int t;
  cin >> t;
  int id;
  cin >> id;
  while (t--) {
    cout << id << " ";

    string inp;
    string state = "BEGIN";
    int i = 0;
    while (cin >> inp) {
      if (inp.size() == 1 && inp[0] >= 'A' && inp[0] <= 'Z') {
        string c;
        c += inp[0];
        if (G[state].count(c) == 0) {
          if (i != 0)
            cout << ">";
          cout << "Invalid Command";
        } else {
          if (i != 0)
            cout << ">";
          string nstate = G[state][c];
          cout << nstate;
          state = nstate;
        }
        i++;
      } else {
        id = stoi(inp);
        cout << '\n';
        break;
      }
    }
  }
  cout << '\n';

  return 0;
}

#ifdef TEST
string rtrim(string s) {
  auto end = s.find_last_not_of(" \n\t\f\r\v");
  return end == string::npos ? s : s.substr(0, end + 1);
}
bool printTest(string name, string outStr, string expStr) {
  if (outStr == expStr) {
    print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
  } else {
    print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: "
          "\n'{}'\n---got: \n'{}'\n\n",
          name, expStr, outStr);
  }
  return outStr == expStr;
}
void test(string name) {
  ifstream in(name + ".in");
  ostringstream out;

  ifstream exp(name + ".out");
  string expStr(istreambuf_iterator<char>{exp}, {});
  expStr = rtrim(expStr);

  run(in, out);

  string outStr = rtrim(out.str());

  printTest(name, outStr, expStr);
}

int main() {
  test("ex0");
  return 0;
}
#endif
