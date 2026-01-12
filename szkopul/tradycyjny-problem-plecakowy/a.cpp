#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	typedef long long ll;
	
	// k - ilosc przedmiotow
	// n - wielkosc plecaka
	int k, n;
	cin >> k >> n;

	vector<ll> dp(n+1, 0);
	for (int ki = 0; ki < k; ki++) {
		int kw, ku;
		cin >> kw >> ku;

		for (int i = n; i >= kw; i--) {
			dp[i] = max(dp[i], ku + dp[i-kw]);
		}
	}
	cout << dp[n] << endl;

	return 0;
}


#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
