#include <bits/stdc++.h>

using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
/*#define endl "\n";*/

	int n, m;
	cin >> n >> m;

	typedef long long ll;

	vector<ll> costs(n);
	vector<ll> initial(n);
	vector<ll> states(n);
	{
		for (int i = 0; i < n; i++) cin >> costs[i];
		for (int i = 0; i < n; i++) cin >> initial[i];

		vector<pair<ll, ll>> ent(n);
		for (int i = 0; i < n; i++) ent[i] = {costs[i], initial[i]};
		sort(ent.begin(), ent.end(), greater<pair<ll, ll>>());

		for (int i = 0; i < n; i++) {
			costs[i] = ent[i].first;
			states[i] = initial[i] = ent[i].second;
		}
	}

	vector<multiset<ll>> mvals(m);
	for (int i = 0; i < m; i++) {
		vector<ll> vals(n);
		for (int j = 0; j < n; j++) cin >> vals[j];
		mvals[i] = multiset<ll>(vals.begin(), vals.end());
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			auto upper = mvals[i].upper_bound(states[j]-1);
			if (upper == mvals[i].end()) {
				cout << "NIE" << endl;
				return 0;
			}
			states[j] = *upper;
			mvals[i].erase(upper);
		}
	}

	ll sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (states[i] - initial[i]) * costs[i];
	}
	cout << sum << endl;

	return 0;
}


#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
