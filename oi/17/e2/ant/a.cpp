#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


vector<int> manacher(string str) {
	int n = str.size();

	int L = 0;
	int R = -1;
	vector<int> P(n, 0);
	for (int i = 0; i < n-1; i++) {
		int &size = P[i];
		if (i < R) size = min(P[L+R-i-1], R-i);
		int l = i-size;
		int r = i+size+1;
		for (; l >= 0 and r < n and str[l] != str[r]; l--, r++) {
			size++;
			if (i + size > R) {
				L = i - size+1;
				R = i + size;
			}
		}
	}
	return P;
}

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	string str;

	cin >> n;
	str.reserve(n+1);
	cin >> str;

	vector<int> res = manacher(str);
	ll sum = 0;
	for (int i = 0; i < (int)res.size(); i++) sum += res[i];
	cout << sum << '\n';

	return 0;
}
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \t\r\v\f\n");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string expS, string outS) {
	if (expS == outS)
	printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
	else
	printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n-----got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
}
void test(string name) {
	ifstream in(name+".in");
	ostringstream out;
	run(in, out);
	string outS = rtrim(out.str());

	ifstream exp(name+".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	printT(name, expS, outS);
}
int main() {
	test("ex0");
	return 0;
}
#endif
