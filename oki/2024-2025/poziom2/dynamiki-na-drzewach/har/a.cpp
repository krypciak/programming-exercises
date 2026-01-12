#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<vector<int>> G;
vector<bool> visited;
pair<int, int> dij(int v) {
	visited[v] = true;
	int imRoot = 1;
	int imNot = 0;
	for (int u : G[v]) {
		if (visited[u]) continue;
		auto [a, b] = dij(u);
		imRoot += b;
		imNot += max(a, b);
	}
	return { imRoot, imNot };
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	cin >> n;
	G = vector<vector<int>>(n+1);
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	visited = vector<bool>(n+1, false);
	
	auto [a, b] = dij(1);
	int out = max(a, b);
	cout << out << '\n';
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
