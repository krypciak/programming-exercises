#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n, m;
	cin >> n >> m;

	vector<vector<int>> inp(n, vector<int>(m));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> inp[i][j];
	for (int i = 0; i < n; i++) sort(inp[i].begin(), inp[i].end());

	typedef tuple<int, int, int> pt;
	priority_queue<pt, vector<pt>, greater<pt>> Q;

	int cdMax = 0;
	for (int i = 0; i < n; i++) { int d = inp[i][0]; Q.emplace(d, i, 0); cdMax = max(cdMax, d); }

	int minRange = cdMax - get<0>(Q.top()) + 1;
	while(Q.size()) {
		auto [d, i, ptr] = Q.top();
		Q.pop();
		if (ptr == m-1) break;
		int nd = inp[i][ptr+1];
		Q.emplace(nd, i, ptr+1);
		cdMax = max(cdMax, nd);

		minRange = min(minRange, cdMax - get<0>(Q.top()) + 1);
	}
	cout << minRange << '\n';
	return 0;
}
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \r\n\t\f\v");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS)
	printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
	else
	printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n---got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
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
	test("tel0a");
	test("tel0b");
	test("tel0c");
	test("tel0d");
	test("tel0e");
	test("tel0f");
	return 0;
}
#endif
