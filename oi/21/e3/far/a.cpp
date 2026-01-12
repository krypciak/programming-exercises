#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<ll> C;
vector<vector<int>> G;
vector<bool> visited;
typedef pair<ll, ll> pt;
pt dfs(int v, int p) {
	visited[v] = true;
	if (G[v].size() == 1 and visited[p]) return {C[v], 0};
	
	vector<pt> res;
	res.reserve(G[v].size());
	for (int u : G[v]) if (!visited[u]) res.push_back(dfs(u, v));
	sort(res.begin(), res.end(), greater<pt>());


	ll T = accumulate(res.begin(), res.end(), 0, [](int acc, const pt& a) { return acc + a.second; }) + (G[v].size() - 1)*2;
	if (v == 1) T += 2;
	ll extra = C[v] - T;

	ll t = 1;
	for (auto [cost, extraT] : res) {
		t += extraT;
		ll tl = T - t;
		extra = max(extra, cost - tl);
		t += 2;
	}
	extra = max(extra, (ll)0);
	return {extra, T};
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	C.assign(n+1, 0);
	for (int v = 1; v <= n; v++) cin >> C[v];
	G.assign(n+1, {});
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	visited.assign(n+1, false);
	auto [cost, extraT] = dfs(1, 0);

	ll res = max(cost, C[1]) + extraT;
	cout << res << '\n';
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
