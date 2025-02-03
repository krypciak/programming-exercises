#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cti(char c) {
	if (c <= 'Z') return c-'A'+1;
	return c-'a'+27;
}

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
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
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \n\r\t\f\v");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n---got: \n'{}'\n\n", name, expS, outS);
	}
}
void test(string name) {
	ifstream in(name+".in");
	ostringstream out;

	run(in, out);
	string outS = rtrim(out.str());

	ifstream exp(name+".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	printT(name, outS, expS);
}
int main() {
	test("ex0");
	return 0;
}
#endif
