#include <iostream>
#include <map>

#ifdef DEBUG
#include <print>
#include <fstream>
#include <sstream>
#endif

using namespace std;

int run(istream &cin, ostream &cout) {
	string str;
	cin >> str;
	map<char, int> m;
	for (char c : str) {
		m[c]++;
	}
	char failedChar = '\0';
	for (auto [c, count] : m) {
		if (count % 2 != 0) {
			if (failedChar) {
				cout << "NO SOLUTION" << endl;
				return 0;
			}
			failedChar = c;
		}
	}
	string res(str.size(), ' ');
	size_t pos = 0;
	for (auto [c, count] : m) {
		if (c == failedChar) count--;
		for (int i = 0; i < count / 2; i++) {
			res[pos] = c;
			res[str.size() - pos - 1] = c;
			pos++;
		}
	}
	if (failedChar) {
		res[str.size()/2] = failedChar;
	}
	cout << res << endl;

	return 0;
}


#ifdef DEBUG

string rtrim(const string &s) {
	size_t end = s.find_last_not_of(" \n\r\t\f\v");
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}

void tf(string name) {
	ifstream in(format("{}.in", name));
	ostringstream out;
	
	ifstream exp(format("{}.out", name));
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);
	string outStr = rtrim(out.str());

	if (outStr != expStr) {
		print("test {} failed! expected: \n'{}'\n--- got \n'{}'\n", name, expStr, outStr);
	} else {
		print("test {} success\n", name);
	}
}

int main() {
	tf("ex0");
	tf("ex1");
	tf("ex2");
	return 0;
}
#else
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return run(cin, cout);
}
#endif
