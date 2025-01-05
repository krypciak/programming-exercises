#include <iostream>
#include <vector>
#include <cassert>
#include <bitset>
#include <unordered_set>
#include <cmath>
#include <stack>

using namespace std;

#ifdef TEST
#include <print>
#include <fstream>
#include <sstream>

int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n;
	cin >> n;

	typedef unsigned long long ll;

	const ll moves = (1 << n) - 1;
	cout << moves << endl;

	const int BOTTOM = 1e6;
	vector<stack<int>> t(3);
	for (int i = 0; i < 3; i++) t[i].push(BOTTOM);
	for (int i = n; i >= 1; i--) t[0].push(i);

	typedef pair<int, int> pt;
	for (unsigned int i = 0; i < moves; i++) {
		if (i % 2 == 0) {
			auto [sm, smI] = min({(pt){t[0].top(), 0}, {t[1].top(), 1}, {t[2].top(), 2}});
			t[smI].pop();

			int dir = (n % 2 == 0) ? 1 : -1;
			int ni = smI + dir;
			if (ni < 0) ni = 2;
			ni %= 3;

			if (t[ni].top() <= sm) ni += dir;
			if (ni < 0) ni = 2;
			ni %= 3;

			t[ni].push(sm);
			cout << smI+1 << " " << ni+1 << endl;
		} else {
			auto [sm, smI] = min({(pt){t[0].top(), 0}, {t[1].top(), 1}, {t[2].top(), 2}});
			if (smI == 0) {
				tie(sm, smI) = min((pt){t[1].top(), 1}, {t[2].top(), 2});
			} else if (smI == 1) {
				tie(sm, smI) = min((pt){t[0].top(), 0}, {t[2].top(), 2});
			} else if (smI == 2) {
				tie(sm, smI) = min((pt){t[0].top(), 0}, {t[1].top(), 1});
			} 
			t[smI].pop();

			int dir = (n % 2 == 0) ? -1 : 1;
			int ni = smI+dir;
			if (ni < 0) ni = 2;
			ni %= 3;

			if (t[ni].top() <= sm) ni += dir;
			if (ni < 0) ni = 2;
			ni %= 3;

			t[ni].push(sm);
			cout << smI+1 << " " << ni+1 << endl;
		}
	}

	return 0;
}

#ifdef TEST
string rtrim(const string& str) {
	auto end = str.find_last_not_of(" \n\r\t\v\f");
	return (end == string::npos) ? str : str.substr(0, end + 1);
}
void test(string name) {
	ifstream in(format("{}.in", name));
	ostringstream out;

	ifstream exp(format("{}.out", name));
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);
	string outStr = rtrim(out.str());

	if (expStr != outStr) {
		print("\u001b[1m\u001b[31mx\u001b[0m\u001b[22m {} expected: \n'{}'\n----got:\n'{}'\n\n", name, expStr, outStr);
	} else {
		print("\u001b[1m\u001b[32m\u221A\u001b[0m\u001b[22m {}\n", name);
	}
}
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
