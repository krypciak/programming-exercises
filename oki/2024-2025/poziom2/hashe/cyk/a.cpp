#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int n;
const ll M = 1e9 + 21;
const ll BASE = 31;
vector<ll> MUL;

int cti(char c) { return c-'a'+1; }

ll hashOf(const string &s) {
	ll h = 0;
	for (int i = 0; i < n; i++)
		h = (h + MUL[i]*cti(s[i])%M) % M;
	return h;
}


int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string a, b;
	cin >> n;
	cin >> a >> b;

	MUL.assign(n*2, 0);
	MUL[0] = 1;
	for (int i = 1; i < n*2; i++) MUL[i] = (MUL[i-1] * BASE) % M;

	ll aHash = hashOf(a);
	ll bHash = hashOf(b);

	a += a;
	if (bHash == aHash) { cout << "TAK" << '\n'; return 0; }

	for (int i = n; i < n*2; i++) {
		aHash = (aHash - (MUL[i-n]*cti(a[i-n])%M) + M) % M;
		aHash = (aHash + (MUL[i]*cti(a[i])%M)) % M;

		bHash = (bHash * BASE) % M;
		if (bHash == aHash) { cout << "TAK" << '\n'; return 0; }
	}
	cout << "NIE" << '\n';
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
	test("ex3");
	return 0;
}
#endif
