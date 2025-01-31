#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n, k;
	cin >> n >> k;

	typedef pair<int, int> pt;
	vector<vector<pt>> OS(n, vector<pt>(k));
	for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) {
		int val; cin >> val;
		OS[i][j].first = val;
	}
	for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) {
		int val; cin >> val;
		OS[i][j].second = val;
	}

	vector<int> reqMet(n, k);
	vector<priority_queue<pt, vector<pt>, greater<pt>>> reqs(k);
	for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) reqs[j].emplace(OS[i][j].first, i);

	vector<ll> CS(k, 0);
	bool lastWon = true;
	int sum = 0;
	while(lastWon) {
		lastWon = false;
		for (int j = 0; j < k; j++) {
			while (reqs[j].size()) {
				auto [sn, i] = reqs[j].top();
				if (CS[j] < sn) break;
				reqs[j].pop();
				if (--reqMet[i] == 0) {
					lastWon = true;
					for (int l = 0; l < k; l++) CS[l] += OS[i][l].second;
					sum++;
				}
			}
		}
	}
	cout << sum << '\n';
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
	test("ex1");
	test("ex0");
	test("ex2");
	test("ex3");
	return 0;
}
#endif
