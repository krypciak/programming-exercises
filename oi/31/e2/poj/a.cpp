#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	ll k;
	cin >> n >> k;
	vector<ll> inp(n);
	for (int i = 0; i < n; i++) cin >> inp[i];

	vector<pair<ll, int>> big;
	vector<pair<ll, int>> small;
	for (int i = 0; i < n; i++) {
		ll v = inp[i];
		if (v > k) big.push_back({v, i});
		else small.push_back({v, i});
	}

	struct Out {
		int m;
		int ai;
		ll a;
		int bi;
		ll b;
	};
	vector<Out> out(n, {0});
	while(!big.empty() and !small.empty()) {
		auto [b, bi] = big.back();
		auto [s, si] = small.back();
		big.pop_back();
		small.pop_back();

		b -= k-s;
		assert(out[si].m == 0);
		out[si] = {2, bi, k-s, si, s};
		if (b > k) {
			big.push_back({b, bi});
		} else {
			small.push_back({b, bi});
		}
	}
	if (!big.empty()) { cout << "NIE" << '\n'; return 0; }
	cout << "TAK" << '\n';
	for (auto [s, si] : small) {
		assert(out[si].m == 0);
		out[si] = {1, si, s};
	}
	for (auto [m, ai, a, bi, b] : out) {
		cout << m;
		if (m >= 1) cout << " " << (ai+1) << " " << a;
		if (m >= 2) cout << " " << (bi+1) << " " << b;
		cout << '\n';
	}
	return 0;
}
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \t\n\r\t\v");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS)
	printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
	else
	printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n----got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
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
}
#endif
