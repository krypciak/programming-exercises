#include <bits/stdc++.h>

using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
/*#define endl "\n";*/

	int n, m;
	cin >> n >> m;

	typedef long long ll;

	vector<ll> costs(n);
	vector<ll> initial(n);
	vector<ll> states(n);
	{
		for (int i = 0; i < n; i++) cin >> costs[i];
		for (int i = 0; i < n; i++) cin >> initial[i];

		vector<pair<ll, ll>> ent(n);
		for (int i = 0; i < n; i++) ent[i] = {costs[i], initial[i]};
		sort(ent.begin(), ent.end(), greater<pair<ll, ll>>());

		for (int i = 0; i < n; i++) {
			costs[i] = ent[i].first;
			states[i] = initial[i] = ent[i].second;
		}
	}

	vector<multiset<ll>> mvals(m);
	for (int i = 0; i < m; i++) {
		vector<ll> vals(n);
		for (int j = 0; j < n; j++) cin >> vals[j];
		mvals[i] = multiset<ll>(vals.begin(), vals.end());
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			auto upper = mvals[i].upper_bound(states[j]-1);
			if (upper == mvals[i].end()) {
				cout << "NIE" << endl;
				return 0;
			}
			states[j] = *upper;
			mvals[i].erase(upper);
		}
	}

	ll sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (states[i] - initial[i]) * costs[i];
	}
	cout << sum << endl;

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
