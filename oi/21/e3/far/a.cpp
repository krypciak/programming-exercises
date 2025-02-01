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

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
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
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \n\r\t\f\v");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n---got: \n'{}'\n\n", name, expS, outS);
	}
}
void test(string name) {
	ifstream in(name+".in");
	ostringstream out;

	run(in, out);
	string outS = rtrim(out.str());

	ifstream exp(name+".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	printT(name, outS, expS);
}
int main() {
	test("ex0");
	return 0;
}
#endif
