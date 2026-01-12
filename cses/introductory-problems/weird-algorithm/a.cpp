#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	ll n;
	cin >> n;

	while (n != 1) {
		cout << n << " ";
		if (n % 2 == 0) {
			n /= 2;
		} else {
			n = n * 3 + 1;
		}
	}
	cout << n << endl;
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
