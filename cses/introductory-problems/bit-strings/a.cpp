#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;

	const ll MOD = 1e9 + 7;

	ll val = 1;
	ll a = 2;
	ll b = n;
	while (b > 0) {
		if (b & 1)
			val = val * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}

	cout << val << endl;

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
