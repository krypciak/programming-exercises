#include <bits/stdc++.h>

using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#define endl "\n";

	int n, q;
	cin >> n >> q;

	vector<int> G(n+1);
	for (int i = 1; i <= n; i++) {
		cin >> G[i];
	}

	const int MAXLG = 30;
	vector<vector<int>> skok(MAXLG+1, vector<int>(n+1));

	for (int i = 1; i <= n; i++) skok[0][i] = G[i];
	for (int i = 1; i <= MAXLG; i++) for (int j = 1; j <= n; j++) skok[i][j] = skok[i-1][skok[i-1][j]];

	while (q--) {
		int v, x;
		cin >> v >> x;

		int dist = 1 << MAXLG;
		for (int i = MAXLG; i >= 0; i--) {
			if (x >= dist) {
				v = skok[i][v];
				x -= dist;
			}
			dist /= 2;
		}
		cout << v << endl;
	}

	return 0;
}

#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \n\t\f\r\v");
	return end == string::npos ? s : s.substr(0, end+1);
}
bool printTest(string name, string outStr, string expStr) {
	if (outStr == expStr) {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	} else {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} fail! expected: \n'{}'\n---got: \n'{}'\n\n", name, expStr, outStr);
	}
	return outStr == expStr;
}
void test(string name) {
	ifstream in(name + ".in");
	ostringstream out;

	ifstream exp(name + ".out");
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);

	string outStr = rtrim(out.str());

	printTest(name, outStr, expStr);
}

int main() {
	test("ex0");
	return 0;
}
#endif

