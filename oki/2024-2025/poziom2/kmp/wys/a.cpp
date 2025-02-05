#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int sl, pl;
	string s;
	{
		cin >> sl >> pl;
		string p;
		cin >> s >> p;
		s = p + "#" + s;
	}

	int slen = s.size();
	int t = -1;
	int sum = 0;

	vector<int> kmp(slen+1);
	kmp[0] = -1;
	for (int i = 1; i <= slen; i++) {
		while (t >= 0 and s[t] != s[i-1]) {
			t = kmp[t];
		}
		kmp[i] = ++t;
		if (t == pl)
			sum++;
	}
	cout << sum << '\n';
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
	test("ex1");
	test("ex0");
	test("ex2");
	return 0;
}
#endif
