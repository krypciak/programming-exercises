#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int t;
  cin >> t;
  string line;
  getline(cin, line);
  while (t--) {
    getline(cin, line);
    stringstream ss(line);
    char vt;
    string vu, vg, vo;
    int n;
    ss >> vt >> vu >> vg >> vo;
    ss >> n;

    string pwd;
    bool first = true;
    vector<string> wrong;

    auto checkEnd = [&]() {
      if (!first) {
        if (wrong.size()) {
          cout << pwd << '\n';
          for (auto s : wrong) {
            cout << s << '\n';
          }
        } else {
          cout << pwd << " ALL GOOD\n";
        }
      }
      wrong.clear();
        first = false;
    };

    while (n--) {
      getline(cin, line);
      if (line[0] == '.' && line[1] == '/') {
        checkEnd();
        pwd = line;
      } else {
        stringstream ss1(line);
        string tochck;
        ss1 >> tochck;
        string fileName;
        ss1 >> fileName >> fileName >> fileName >> fileName >> fileName >>
            fileName >> fileName >> fileName;

        if (tochck[0] == 'd' && vt == 'F')
          continue;
        if (tochck[0] == '-' && vt == 'D')
          continue;
        vector<string> lw;
        string cu;
        cu += tochck[1];
        cu += tochck[2];
        cu += tochck[3];
        if (cu != vu)
          lw.push_back("Owner");
        string cg;
        cg += tochck[4];
        cg += tochck[5];
        cg += tochck[6];
        if (cg != vg)
          lw.push_back("Group");
        string co;
        co += tochck[7];
        co += tochck[8];
        co += tochck[9];
        if (co != vo)
          lw.push_back("Other");

        if (lw.size()) {
          string out = fileName + ": WRONG PERM: ";
          for (int i = 0; i < (int)lw.size(); i++) {
            if (i != 0)
              out += ", ";
            out += lw[i];
          }
          wrong.push_back(out);
        }

        // std::cout << "pwd: " << pwd << ", file: " << fileName
        //           << ", perms: " << tochck << endl;
      }
    }
    checkEnd();
  }

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
