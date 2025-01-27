#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	int n, m;
	cin >> n >> m;
	int N = n+1;

	vector<vector<int>> G(N);
	vector<vector<int>> RG(N);
	for (int i = 0; i < m; i++) {
		int f, t;
		cin >> f >> t;
		G[f].push_back(t);
		RG[t].push_back(f);
	}
	priority_queue<int, vector<int>, greater<int>> zeros;
	vector<int> deg(N, 0);
	for (int i = 1; i < N; i++) {
		deg[i] = RG[i].size();
		if (deg[i] == 0) zeros.push(i);
	}

	vector<int> topsorted;
	topsorted.reserve(n);
	while (zeros.size()) {
		int v = zeros.top();
		zeros.pop();
		topsorted.push_back(v);
		for (auto u : G[v]) 
			if (--deg[u] == 0) zeros.push(u);
	}
	if ((int)topsorted.size() != n) cout << "UNMOGLICH" << endl;
	else for (int i = 0; i < n; i++) cout << topsorted[i] << ' ';

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
	test("ex1");
	return 0;
}
#endif
