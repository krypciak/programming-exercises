#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;

	auto spiral = [](ll y) -> ll {
		if (y == 0) return 1;

		ll val = y - ((y % 2 == 0) ? 1 : 0);
		val = (val+1) * (val+1);
		if (y % 2 == 0) val++;
		return val;
	};

	for (int i = 0; i < t; i++) {
		ll y, x;
		cin >> y >> x;
		x--;
		y--;

		ll val;
		if (x > y) {
			if (x % 2 == 0) val = spiral(x) + (x + x - y);
			else val = spiral(x) - (x + x - y);
		} else {
			if (y % 2 == 0) val = spiral(y) + x;
			else val = spiral(y) - x;
		}
		cout << val << endl;
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
