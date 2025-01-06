#include <iostream>
#include <vector>

using namespace std;

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
	typedef long long ll;

	int n;
	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	vector<pair<ll, ll>> toVisit{{0, 0}};

	for (int i = 0; i < n; i++) {
		ll num = nums[i];
		vector<pair<ll, ll>> nextToVisit;
		nextToVisit.reserve(1 << (i+1));
		for (const auto& [n1, n2] : toVisit) {
			nextToVisit.push_back({n1+num, n2});
			nextToVisit.push_back({n1, n2+num});
		}
		toVisit = nextToVisit;
	}
	ll mini = 2e9;
	for (const auto& [n1, n2] : toVisit) {
		ll diff = abs(n1 - n2);
		mini = min(mini, diff);
	}
	cout << mini << endl;

	return 0;
}

#ifdef TEST
string rtrim(const string &s) {
	auto end = s.find_last_not_of(" \n\r\t\v\f");
	return end == string::npos ? s : s.substr(0, end+1);
}
void test(const string &name) {
	ifstream in(format("{}.in", name));
	ostringstream out;

	ifstream exp(format("{}.out", name));
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);
	string outStr = rtrim(out.str());

	if (outStr != expStr) {
		print("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m {} failed! expected:\n'{}'\n----got:\n'{}'\n\n", name, expStr, outStr);
	} else {
		print("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m {} success\n", name);
	}
}
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
