#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cti(char c) { return c-'a'+1; }

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
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
	test("ex1");
	test("ex2");
	return 0;
}
#endif
