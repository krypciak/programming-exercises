#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	string s;
	cin >> n >> s;

	vector<int> kmp(n+1);
	kmp[0] = -1;
	int t = -1;

	for (int i = 1; i <= n; i++) {
		while (t >= 0 and s[t] != s[i-1]) t = kmp[t];
		kmp[i] = ++t;
	}
	for (int i = 1; i <= n; i++) cout << kmp[i] << " ";
	cout << endl;

	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
