#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;

	if (n == 2 or n == 3) {
		cout << "NO SOLUTION" << endl;
		return 0;
	}

	for (int i = 2; i <= n; i+=2) {
		cout << i << " ";
	}
	for (int i = 1; i <= n; i+=2) {
		cout << i << " ";
	}
	cout << endl;
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
