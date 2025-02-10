#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	const uint MAXN = 1'000'001;
	const uint MAXM = 1'000'001;
	const uint MAXBON = 1'000'001;

	uint m, n;
	uint maxBon;
	ll used[MAXBON]; memset(used, 0, sizeof(ll)*MAXBON);
	uint lastIndex[MAXBON]; memset(lastIndex, 0, sizeof(uint)*MAXBON);
	uint A[MAXN];

	cin >> m;
	maxBon = 0;
	for (uint i = 0; i < m; i++) {
		uint v; cin >> v;
		used[v] = -1;
		maxBon = max(maxBon, v+1);
	}

	cin >> n;
	for (uint i = 0; i < n; i++) cin >> A[i];

	ll *bought = new ll[MAXM]; ll boughtI = 0;
	ll customer = 1;
	for (uint ai = 0; ai < n; ai++) {
		uint a = A[ai];

		if (a < maxBon) {
			uint v = lastIndex[a]+a;
			for (uint i = 0; i < a and v < maxBon; i++, v += a) {
				ll u = used[v];
				if (u > 0) { i--; continue; }
				ll id = customer + i;
				used[v] = id;
				if (u == -1) bought[boughtI++] = id;
			}
			lastIndex[a] = v-a;
		}
		customer += a;
	}

	cout << boughtI << '\n';
	for (ll i = 0; i < boughtI; i++) cout << bought[i] << '\n';

	delete[] bought;
	return 0;
}
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \t\r\v\f\n");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string expS, string outS) {
	if (expS == outS)
	printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
	else
	printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n-----got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
}
void test(string name) {
	ifstream in(name+".in");
	ostringstream out;
	run(in, out);
	string outS = rtrim(out.str());

	ifstream exp(name+".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	printT(name, expS, outS);
}
int main() {
	test("ex0");
	test("ex1");
	/*test("ex2");*/
	test("ex3");
	test("ex4");
	return 0;
}
#endif
