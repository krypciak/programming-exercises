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
	int n, s;
	cin >> n >> s;
	
	vector<int> inp(n+1);
	for (int i = 1; i < n; i++) cin >> inp[i];
	inp[n] = 0;

	const int MAXLG = 30;
	const int CANTJUMP = 2000000;
	vector<vector<int>> skok(MAXLG+1, vector<int>(n+1, CANTJUMP));
	for (int i = 1; i <= n; i++) skok[0][i] = i;

	vector<int> psum(n+1);
	psum[0] = 0;
	for (int i = 1; i <= n; i++) psum[i] = psum[i-1] + inp[i];
	for (int j = 1; j <= n-1; j++) {
		auto ji = next(psum.begin(), j);
		int upperV = s + psum[j-1];
		auto upper = upper_bound(ji, next(ji, min(s, n-j+1)), upperV);
		int index = min(n, (int)distance(psum.begin(), upper));
		skok[1][j] = index;
		/*print("j: {}, upper: {}, index: {}\n", j, *upper, index);*/
	}

	for (int i = 2; i <= MAXLG; i++) {
		for (int j = 1; j <= n; j++) {
			if (skok[i-1][j] == CANTJUMP) break;
			skok[i][j] = skok[i-1][skok[i-1][j]];
		}
	}

	int p;
	cin >> p;

	while(p--) {
		int v, x;
		cin >> v >> x;
		if (x < v) swap(x, v);

		int jumps = 0;
		for (int i = MAXLG, jumpC = 1<<(MAXLG-1); i >= 1 && v < x;) {
			if (skok[i][v] <= x || i == 1) {
				v = skok[i][v];
				jumps += jumpC;
			} else {
				i--;
				jumpC/=2;
			}
		}
		cout << jumps << endl;
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
	test("ex1");
	test("ex2");
	return 0;
}
#endif
