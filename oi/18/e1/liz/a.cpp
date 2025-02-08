#include <bits/stdc++.h>
using namespace std;

const uint MAXN = 1000000+1;
uint n, q;
char inp[MAXN];
pair<uint, uint> R[MAXN*2];
uint MAX;

void rembr(uint l, uint r, uint k) {
	const uint initK = k;
	for (uint i = 0; i < (initK-1)/2; i++, k-=2) {
		R[k] = {l+1, r+1};

		if (inp[r] == 'T') r--;
		else if (inp[l] == 'T') l++;
		else l++, r--;
	}
	R[k] = {l+1, r+1};
}

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> n >> q;
	MAX = 0;

	cin.get();
	cin.read(inp, n);

	for (uint i = 0; i < n; i++) MAX += inp[i] == 'W' ? 1 : 2;
	rembr(0, n-1, MAX);

	uint l = INT_MAX;
	for (uint i = 0; i < n; i++) { if (inp[i] == 'W') { l = i; break; } }
	uint r = INT_MAX;
	if (l != INT_MAX) for (int i = n-1; i >= 0; i--) { if (inp[i] == 'W') { r = i; break; } }

	if (l != INT_MAX) {
		if (l+1 != n) rembr(l+1, n-1, MAX - (2*l)-1);
		if (r != 0) rembr(0, r-1, MAX - (2*(n-r-1))-1);
	}

	while (q--) {
		uint k;
		cin >> k;

		if (k > MAX or R[k].first == 0) cout << "NIE" << '\n';
		else cout << R[k].first << " " << R[k].second << '\n';
	}
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
	return 0;
}
#endif
