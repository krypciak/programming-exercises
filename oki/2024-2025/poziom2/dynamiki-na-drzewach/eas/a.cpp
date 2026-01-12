#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<vector<int>> G;
vector<bool> visited;
tuple<int, int, int> dij(int v) {
	visited[v] = true;
	int amOn = 1;
	int baby = INT_MAX;
	int cbd = 0;
	for (int u : G[v]) {
		if (visited[u]) continue;
		auto [a, b, c] = dij(u);
		amOn += min({a, b, c});
		cbd += min(a, b);

		if (b == INT_MAX) {
			baby = min(baby, a);
		} else baby = min(baby, max(0, a-b));
	}
	if (baby == INT_MAX) baby = 0;
	baby += cbd;
	return {amOn, baby == 0 ? INT_MAX : baby, v == 1 ? INT_MAX : cbd};
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	cin >> n;
	G.assign(n+1, {});
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	visited.assign(n+1, false);
	
	auto [a, b, c] = dij(1);
	cout << min({a, b, c}) << '\n';
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex4");
	test("ex0");
	test("ex1");
	test("ex2");
	test("ex3");
	return 0;
}
#endif
