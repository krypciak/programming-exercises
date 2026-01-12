#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	vector<int> app(n);
	for (int i = 0; i < n; i++) cin >> app[i];

	vector<int> apart(m);
	for (int i = 0; i < m; i++) cin >> apart[i];
	
	sort(app.begin(), app.end(), greater<int>());
	sort(apart.begin(), apart.end(), greater<int>());

	int i = 0;
	int j = 0;
	int sum = 0;
	while (i < n && j < m) {
		if (abs(app[i] - apart[j]) <= k) {
			i++;
			j++;
			sum++;
		} else {
			if (app[i] > apart[j]) i++;
			else j++;
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
	test("ex1");
	return 0;
}
#endif
