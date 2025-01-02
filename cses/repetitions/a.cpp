#include <iostream>
#include <vector>

#ifdef DEBUG
#include <print>
#include <fstream>
#include <sstream>
#endif

using namespace std;

int run(istream &cin, ostream &cout) {
	string seq;
	cin >> seq;

	int maxLen = 0;
	int currLen = 0;
	char prevChar = '@';
	for (char c : seq) {
		if (c == prevChar) {
			currLen++;
		} else {
			maxLen = max(maxLen, currLen);
			currLen = 1;
		}
		prevChar = c;
	}
	maxLen = max(maxLen, currLen);

	cout << maxLen << endl;
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
	return 0;
}
#else
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return run(cin, cout);
}
#endif
