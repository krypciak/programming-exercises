#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
#define endl "\n";

	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n, a, b;
		cin >> n >> a >> b;

		auto comp = [&]() -> bool {
			int dist = abs(a - b - 1);
			return dist % 2 == 1;
		};
		if (comp()) {
			cout << "YES" << endl
		} else {
			cout << "NO" << endl;
		}
	}

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
