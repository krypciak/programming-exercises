#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

int n;
vector<vector<int>> g;

int dfs(int x, int v, int p) {
	int sum = 0;
	for (auto u : g[v]) {
		if (u == p) continue;
		sum += dfs(x, u, v) + 1;
	}
	return max(0, sum - x);
}

#ifdef TEST
#include <print>
#include <fstream>
#include <sstream>

int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	 g = vector<vector<int>>(n+1);
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	int i = 0, j = n+1;
	while (j > i) {
		int m = i + (j-i)/2;

		int res = dfs(m, 1, 1);

		if (res == 0) {
			j = m;
		} else {
			assert(res > 0);
			i = m + 1;
		}
	}
	cout << j << endl;
	return 0;
}

#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \t\n\r\v\f");
	return end == string::npos ? s : s.substr(0, end+1);
}
bool printT(string name, string outS, string expS) {
	if (outS == expS) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n---got: \n'{}'\n\n", name, expS, outS);
	}
	return outS == expS;
}
void test(string name) {
	ifstream in(name + ".in");
	ostringstream out;

	ifstream exp(name + ".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	run(in, out);

	string outS = rtrim(out.str());

	printT(name, outS, expS);
}
int main() {
	test("ex0");
	test("ex1");
	test("ex2");
	test("ex4");
	test("ex3");
	return 0;
}

#endif
