#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n, m;
	cin >> n >> m;

	vector<vector<int>> inp(n, vector<int>(m));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> inp[i][j];
	for (int i = 0; i < n; i++) sort(inp[i].begin(), inp[i].end());

	typedef tuple<int, int, int> pt;
	priority_queue<pt, vector<pt>, greater<pt>> Q;

	int cdMax = 0;
	for (int i = 0; i < n; i++) { int d = inp[i][0]; Q.emplace(d, i, 0); cdMax = max(cdMax, d); }

	int minRange = cdMax - get<0>(Q.top()) + 1;
	while(Q.size()) {
		auto [d, i, ptr] = Q.top();
		Q.pop();
		if (ptr == m-1) break;
		int nd = inp[i][ptr+1];
		Q.emplace(nd, i, ptr+1);
		cdMax = max(cdMax, nd);

		minRange = min(minRange, cdMax - get<0>(Q.top()) + 1);
	}
	cout << minRange << '\n';
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("tel0a");
	test("tel0b");
	test("tel0c");
	test("tel0d");
	test("tel0e");
	test("tel0f");
	return 0;
}
#endif
