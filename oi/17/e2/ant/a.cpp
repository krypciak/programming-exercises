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

int run(istream &cin, ostream &cout) {
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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
