#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;

	vector<ll> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	ll sum = 0;
	for (int i = 1; i < n; i++) {
		if (nums[i] > nums[i - 1]) continue;
		ll newVal = nums[i - 1];
		sum += newVal - nums[i];
		nums[i] = newVal;
	}
	cout << sum << endl;
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
