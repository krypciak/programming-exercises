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
	string s;
	cin >> n;
	cin >> s;

	string ns = s;
	reverse(ns.begin(), ns.end());
	ns += "#" + s;

	vector<int> kmp(ns.size()+1);
	kmp[0] = -1;
	int t = -1;
	int maxPal = 0;
	for (int i = 1; i <= (int)ns.size(); i++) {
		while (t >= 0 and ns[t] != ns[i-1]) {
			t = kmp[t];
		}
		kmp[i] = ++t;
		if (i > n) maxPal = max(maxPal, t);
	}
	cout << s;
	for (int i = n-maxPal-1; i >= 0; i--) cout << s[i];
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
	test("ex3");
	return 0;
}
#endif
