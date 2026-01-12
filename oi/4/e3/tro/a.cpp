#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> red(n+1, 0);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		red[a]++;
		red[b]++;
	}

	ll cn = n*(n-1)*(n-2)/6;
	ll mixed = 0;
	for (int i = 1; i <= n; i++) mixed += (n-red[i]-1)*red[i];
	mixed /= 2;

	ll res = cn - mixed;
	cout << res << '\n';

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
