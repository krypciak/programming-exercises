#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex1");
	test("ex0");
	test("ex2");
	return 0;
}
#endif
