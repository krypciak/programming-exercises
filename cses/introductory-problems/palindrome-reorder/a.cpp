#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	return 0;
}
#endif
