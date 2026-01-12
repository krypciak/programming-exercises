#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
  test("ex0");
  return 0;
}
#endif
