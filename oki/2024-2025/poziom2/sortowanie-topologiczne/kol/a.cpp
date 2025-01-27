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

	vector<vector<int>> g(n+1);
	vector<vector<int>> revg(n+1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		revg[b].push_back(a);
	}

	priority_queue<int, vector<int>, greater<int>> empty;
	vector<int> degs(n+1);
	for (int i = 1; i < n+1; i++) { degs[i] = revg[i].size(); if (degs[i] == 0) empty.push(i); }

	while(empty.size()) {
		int v = empty.top();
		cout << v << ' ';
		empty.pop();

		for (auto u : g[v]) {
			degs[u]--;
			if (degs[u] == 0) empty.push(u);
		}
	}
	cout << endl;

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
