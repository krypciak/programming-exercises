#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
#define endl "\n";

	int n, m;
	cin >> n >> m;
	multiset<int> t;
	for (int i = 0; i < n; i++) {
		int val;
		cin >> val;
		t.insert(val);
	}

	for (int i = 0; i < m; i++) {
		int c;
		cin >> c;

		auto it = t.upper_bound(c);
		if (it == t.begin()) {
			cout << -1 << endl;
		} else {
			it--;
			cout << *it << endl;
			t.erase(it);
		}
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
