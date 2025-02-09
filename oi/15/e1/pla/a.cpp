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
	vector<ll> H;

	cin >> n;
	H.reserve(n);
	for (int i = 0; i < n; i++) {
		ll d; cin >> d;
		ll h; cin >> h;

		if (H[i] != h) H.push_back(h);
	}
	n = H.size();

	ll sum = 0;
	stack<ll> heights;

	for (int i = 0; i < n; i++) {
		ll v = H[i];
		while (!heights.empty() and heights.top() > v)
			heights.pop();

		if (heights.empty() or heights.top() < v) {
			sum++;
			heights.push(v);
		}
	}

	cout << sum << endl;
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
	test("ex1");
	test("ex2");
	return 0;
}
#endif
