#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n;
	cin >> n;
	vector<vector<int>> G(n+1);
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	vector<int> P(n+1, 0);
	vector<int> V{1};
	vector<bool> visited(n+1, false);
	visited[1] = true;
	while(V.size()) {
		vector<int> NV;
		NV.reserve(V.size()*4);
		for (int u : V) for (int v : G[u]) {
			if (visited[v]) continue;
			visited[v] = true;
			P[v] = u;
			NV.push_back(v);
		}
		V = NV;
	}
	int q;
	cin >> q;
	while(q--) {
		int v;
		cin >> v;

		if (v == 1) cout << "ADAM" << '\n';
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
