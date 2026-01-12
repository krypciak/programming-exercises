#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cti(char c) { return c-'a'+1; }

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	string s;

	cin >> n >> s;

	const int BASE = 3;
	const ll M = 1e9 + 21;
	vector<ll> MUL(n);
	MUL[0] = 1;
	for (int i = 1; i < n; i++) MUL[i] = (MUL[i-1]*BASE) % M;

	ll hl = 0;
	ll hr = 0;

	int maxP = n;
	for (int i = n-1; i >= 0; i--) {
		int mulI = n-i-1;
		hl = (hl + (cti(s[i])*MUL[mulI])%M) % M;

		hr = (hr*BASE) % M;
		hr = (hr + cti(s[i])) % M;

		if (hl == hr) maxP = i;
	}
	cout << s;
	for (int i = maxP-1; i >= 0; i--) cout << s[i];
	cout << '\n';
	
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	return 0;
}
#endif
