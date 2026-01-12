#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	int N = n+1;

	vector<vector<int>> G(N);
	vector<vector<int>> RG(N);
	for (int i = 0; i < m; i++) {
		int f, t;
		cin >> f >> t;
		G[f].push_back(t);
		RG[t].push_back(f);
	}
	priority_queue<int, vector<int>, greater<int>> zeros;
	vector<int> deg(N, 0);
	for (int i = 1; i < N; i++) {
		deg[i] = RG[i].size();
		if (deg[i] == 0) zeros.push(i);
	}

	vector<int> topsorted;
	topsorted.reserve(n);
	while (zeros.size()) {
		int v = zeros.top();
		zeros.pop();
		topsorted.push_back(v);
		for (auto u : G[v]) 
			if (--deg[u] == 0) zeros.push(u);
	}
	if ((int)topsorted.size() != n) cout << "UNMOGLICH" << endl;
	else for (int i = 0; i < n; i++) cout << topsorted[i] << ' ';

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
