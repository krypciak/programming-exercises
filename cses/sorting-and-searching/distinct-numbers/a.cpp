#include <iostream>
#include <set>

using namespace std;

#ifdef TEST
#include <print>
#include <fstream>
#include <sstream>

int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	set<int> s;
	for (int i = 0; i < n; i++) {
		int val;
		cin >> val;
		s.insert(val);
	}

	cout << s.size() << endl;
	return 0;
}

#ifdef TEST
string rtrim(const string &s) {
	auto end = s.find_last_not_of(" \n\t\r\v\f");
	return end == string::npos ? s : s.substr(0, end+1);
}
bool printRes(const string &name, const string &expStr, const string &outStr) {
	if (expStr == outStr) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} failed! expected: \n'{}'\n----got: \n'{}'\n\n", name, expStr, outStr);
	}
	return expStr == outStr;
}
void test(const string &name) {
	ifstream in(name + ".in");
	ostringstream out;

	ifstream exp(name + ".out");
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);

	string outStr = rtrim(out.str());
	printRes(name, expStr, outStr);
}
int main() {
	test("ex0");
	return 0;
}
#endif
