#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
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
