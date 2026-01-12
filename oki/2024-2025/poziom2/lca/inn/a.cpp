#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, p, q;
vector<vector<int>> G;
vector<int> P;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n >> p;
	G.assign(n+1, {});
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	P.assign(n+1, 0);
	P[p] = p;
	vector<int> V{p};
	while(V.size()) {
		vector<int> NV;
		for (int v : V) for (int u : G[v]) {
			if (P[u] != 0) continue;
			P[u] = v;
			NV.push_back(u);
		}
		V = NV;
	}
	int q;
	cin >> q;
	while(q--) {
		int v;
		cin >> v;
		if (v == p) cout << "ADAM" << '\n';
		else cout << P[v] << '\n';
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
