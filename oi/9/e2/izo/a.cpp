#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	vector<int> inp(n);
	for (int i = 0; i < n; i++) cin >> inp[i];
	sort(begin(inp), end(inp));

	ll sum = 0;
	for (int i = 0; i < n/2; i++) {
		sum += inp[n-i-1] - inp[i];
	}
	for (int i = 0; i < n; i++) sum += inp[i];
	cout << sum;
	
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
