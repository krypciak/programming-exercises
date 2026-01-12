#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	vector<vector<int>> G;
	const int MH = 21;
	vector<vector<int>> JP;

	cin >> n;
	G.assign(n+1, {});
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	JP.assign(MH, vector<int>(n+1, 0));
	vector<int> V{1};
	JP[0][1] = 0;
	vector<bool> visited(n+1, false);
	visited[1] = true;
	while(V.size()) {
		vector<int> NV;
		for (int v : V) for (int u : G[v]) {
			if (visited[u]) continue;
			visited[u] = true;
			JP[0][u] = v;
			NV.push_back(u);
		}
		V = NV;
	}
	for (int deg = 1; deg < MH; deg++)
		for (int v = 0; v <= n; v++)
			JP[deg][v] = JP[deg-1][JP[deg-1][v]];
	int q;
	cin >> q;
	while(q--) {
		int v, p;
		cin >> v >> p;
		for (int deg = log2(p); deg >= 0; deg--) {
			if (p >= 1<<deg) {
				v = JP[deg][v];
				p -= 1<<deg;
				if (v == 0) break;
			}
		}
		if (v == 0) cout << "LUCY" << '\n';
		else cout << v << '\n';
	}
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
