#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	typedef long long ll;

	int n;
	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	vector<pair<ll, ll>> toVisit{{0, 0}};

	for (int i = 0; i < n; i++) {
		ll num = nums[i];
		vector<pair<ll, ll>> nextToVisit;
		nextToVisit.reserve(1 << (i+1));
		for (const auto& [n1, n2] : toVisit) {
			nextToVisit.push_back({n1+num, n2});
			nextToVisit.push_back({n1, n2+num});
		}
		toVisit = nextToVisit;
	}
	ll mini = 2e9;
	for (const auto& [n1, n2] : toVisit) {
		ll diff = abs(n1 - n2);
		mini = min(mini, diff);
	}
	cout << mini << endl;

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
