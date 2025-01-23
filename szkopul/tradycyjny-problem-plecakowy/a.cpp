#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
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

#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \n\t\r\v\f");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n----got: \n'{}'\n\n", name, expS, outS);
	}
}
void test(string name) {
	ifstream in(name + ".in");
	ostringstream out;

	ifstream exp(name + ".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	run(in, out);
	
	string outS = rtrim(out.str());
	printT(name, outS, expS);
}
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
