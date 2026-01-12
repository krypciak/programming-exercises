using namespace std;

string rtrim(string s) {
  auto end = s.find_last_not_of(" \t\r\v\f\n");
  return end == string::npos ? s : s.substr(0, end + 1);
}
#ifndef TEST_OK
bool isTestOk(string inpS, string expS, string outS) {
  if (inpS.size()) {}
  return expS == outS;
}
#endif
void printT(string name, string expS, string outS, string inpS, bool ok) {
  if (inpS.size()) {}
  int limit = 200;
  if (ok) print("\e[32m\e[1m\u221A\e[0m\e[22m {} success\n", name);
  else print("\e[31m\e[1mx\e[0m\e[22m {} fail! expected: \n'{}'\n-----got: \n'{}'\n\n", name, expS.substr(0, limit), outS.substr(0, limit));
}
bool testStrs(string &name, string inpS, string expS, bool passPrint = true) {
  stringstream inp(inpS);
  ostringstream out;

  run(inp, out);
  string outS = rtrim(out.str());

  expS = rtrim(expS);
  bool ok = isTestOk(inpS, expS, outS);
  if (passPrint) printT(name, expS, outS, inpS, ok);
  return ok;
}
bool test(string name, bool passPrint = true) {
  ifstream inp(name + ".in");
  ifstream exp(name + ".out");

  string inpS(istreambuf_iterator<char>{inp}, {});
  string expS(istreambuf_iterator<char>{exp}, {});
  return testStrs(name, inpS, expS, passPrint);
}
