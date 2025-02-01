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

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
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
