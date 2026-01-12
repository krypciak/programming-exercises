#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> g(n+1);
	vector<vector<int>> revg(n+1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		revg[b].push_back(a);
	}

	priority_queue<int, vector<int>, greater<int>> empty;
	vector<int> degs(n+1);
	for (int i = 1; i < n+1; i++) { degs[i] = revg[i].size(); if (degs[i] == 0) empty.push(i); }

	while(empty.size()) {
		int v = empty.top();
		cout << v << ' ';
		empty.pop();

		for (auto u : g[v]) {
			degs[u]--;
			if (degs[u] == 0) empty.push(u);
		}
	}
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
