#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, x;
	cin >> n >> x;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end(), greater<int>());

	int sum = n;
	int i = 0;
	int j = n - 1;

	while(v[i] > x) i++;
	while (j > i) {
		if (v[i] + v[j] <= x) {
			i++;
			j--;
			sum--;
		} else {
			i++;
		}
	}

	cout << sum << endl;
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
