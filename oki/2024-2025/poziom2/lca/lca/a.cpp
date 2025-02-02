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
#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
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
	test("ex1");
	test("ex0");
	return 0;
}
#endif
