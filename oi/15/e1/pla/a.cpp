#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	vector<ll> H;

	cin >> n;
	H.reserve(n);
	for (int i = 0; i < n; i++) {
		ll d; cin >> d;
		ll h; cin >> h;

		if (H[i] != h) H.push_back(h);
	}
	n = H.size();

	ll sum = 0;
	stack<ll> heights;

	for (int i = 0; i < n; i++) {
		ll v = H[i];
		while (!heights.empty() and heights.top() > v)
			heights.pop();

		if (heights.empty() or heights.top() < v) {
			sum++;
			heights.push(v);
		}
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
	test("ex1");
	test("ex2");
	return 0;
}
#endif
