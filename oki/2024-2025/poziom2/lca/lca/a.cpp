#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k, z;
vector<vector<int>> G;
vector<int> D;
const int MH = 21;
vector<vector<int>> JP;

int lca (int v, int u) {
	if (D[u] > D[v]) swap(v, u);
	for (int i = MH-1; i >= 0; i--)
		if (D[JP[i][v]] >= D[u])
			v = JP[i][v];
	if (v == u) return v;

	for (int i = MH-1; i >= 0; i--) {
		int nv = JP[i][v];
		int nu = JP[i][u];
		if (nv != nu) {
			v = nv;
			u = nu;
		}
	}
	return JP[0][u];
}
int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n >> k >> z;
	G.assign(n+1, {});
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	D.assign(n+1, 0);
	JP.assign(MH, vector<int>(n+1, 0));
	JP[0][k] = k;
	{
		vector<int> V{k};
		for (int depth = 1; V.size(); depth++) {
			vector<int> NV;
			for (int v : V) for (int u : G[v]) {
				if (JP[0][u] != 0) continue;
				JP[0][u] = v;
				D[u] = depth;
				NV.push_back(u);
			}
			V = NV;
		}
	}
	for (int deg = 1; deg < MH; deg++)
		for (int v = 1; v <= n; v++)
			JP[deg][v] = JP[deg-1][JP[deg-1][v]];

	while(z--) {
		int v, u;
		cin >> v >> u;
		cout << lca(v, u) << '\n';
	}
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex1");
	test("ex0");
	return 0;
}
#endif
