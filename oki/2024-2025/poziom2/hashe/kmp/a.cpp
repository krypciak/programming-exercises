#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cti(char c) {
	if (c <= 'Z') return c-'A'+1;
	return c-'a'+27;
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	const int BASE = 59;
	const ll M = 1e9 + 21;
	const int MAXN = 1000000;  
	vector<ll> MUL(MAXN, 0);
	MUL[0] = 1;
	for (int i = 1; i < MAXN; i++) MUL[i] = (MUL[i-1]*BASE) % M;

	int T;
	cin >> T;
	while(T--) {
		int pl;
		string p, s;

		cin >> pl >> p >> s;
		int sl = s.size();

		ll ph = 0;
		for (int i = 0; i < pl; i++) ph = (ph + (cti(p[i])*MUL[i])%M) % M;

		ll sh = 0;
		for (int i = 0; i < pl; i++) sh = (sh + (cti(s[i])*MUL[i])%M) % M;

		if (sh == ph) cout << 0 << '\n';

		for (int i = pl; i < sl; i++) {
			sh = (sh + M - (cti(s[i-pl])*MUL[i-pl])%M) % M;
			sh = (sh + (cti(s[i])*MUL[i])%M) % M;
			
			ph = (ph*BASE) % M;
			if (sh == ph) cout << (i-pl+1) << '\n';
		}
	}

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
