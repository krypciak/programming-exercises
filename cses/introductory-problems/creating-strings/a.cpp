#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
