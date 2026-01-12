#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	
	vector<bool> nums(n + 1, true);
	for (int i = 0; i < n - 1; i++) {
		int val;
		cin >> val;
		nums[val] = false;
	}

	for (int i = 1; i <= n; i++) {
		if (nums[i]) {
			cout << i << endl;
			return 0;
		}
	}
	return -1;
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
