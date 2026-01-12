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

int run(istream &cin, ostream &cout) {
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

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
