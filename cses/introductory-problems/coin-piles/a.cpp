#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		auto check = [](const ll a, const ll b) {
			ll topA = 2*b - a;
			if (topA >= 0 && topA % 3 == 0) {
				ll y = topA / 3;
				ll x = b - 2 * y;
				if (x >= 0) {
					assert(2*x + y == a);
					assert(x + 2*y == b);

					return true;
				}
			}
			return false;
		};

		ll a, b;
		cin >> a >> b;

		if (check(a, b)) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
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
