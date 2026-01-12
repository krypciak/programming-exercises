#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
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


#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
