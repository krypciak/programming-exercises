#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
