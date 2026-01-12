#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

vector<vector<int>> G;
vector<int> dp;
int maxVal;

void dfs(int v, int p) {
	int maxPrev = -1000;
	for (auto u : G[v]) {
		if (u == p) continue;

		dfs(u, v);

		dp[v] = max(dp[v], dp[u] + (int)G[v].size() - 2); /* konczy sie na v */

		maxVal = max(max(
			maxVal,
			maxPrev + dp[u] + (int)G[v].size() - 2),
			dp[u] + (int)G[v].size() - 1
		);
		maxPrev = max(maxPrev, dp[u]);
	}
	dp[v] = max(dp[v], (int)G[v].size() - 1); /* start w v */
}

#ifdef TEST
#include <print>
#include <fstream>
#include <sstream>

int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	G = vector<vector<int>>(n+1);
	for (int i = 1; i < n; i++) {
		int f, t;
		cin >> f >> t;
		G[f].push_back(t);
		G[t].push_back(f);
	}

	dp = vector<int>(n+1, 0);
	maxVal = 0;

	dfs(1, 1);
	cout << maxVal << endl;
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
