#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	ll n;
	cin >> n;

	int zeros = 0;
	ll div = 5;
	while (div <= n) {
		zeros += n / div;
		div *= 5;
	}

	cout << zeros << endl;
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
