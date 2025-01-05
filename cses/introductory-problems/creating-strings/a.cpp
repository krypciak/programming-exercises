#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#ifdef TEST
#include <print>
#include <fstream>
#include <sstream>

int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	string in;
	cin >> in;
	sort(in.begin(), in.end());

	vector<string> perms;
	do {
		perms.push_back(in);
	} while(next_permutation(in.begin(), in.end()));

	cout << perms.size() << endl;
	for (const string &s : perms) {
		cout << s << endl;
	}

	return 0;
}

#ifdef TEST
string rtrim(const string &s) {
	size_t end = s.find_last_not_of(" \n\r\t\v\f");
	return end == string::npos ? s : s.substr(0, end+1);
}
void test(string name) {
	ifstream in(format("{}.in", name));
	ostringstream out;

	ifstream exp(format("{}.out", name));
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);

	string outStr = rtrim(out.str());

	if (expStr != outStr) {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} failed! expeceted:\n'{}'\n---got:\n'{}'\n\n", name, expStr, outStr);
	} else {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	}
}
int main() {
	test("ex0");
	return 0;
}
#endif
