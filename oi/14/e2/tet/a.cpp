#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	uint n;
	cin >> n;

	const uint MAXN = 50000+1;
	const uint MAXNN = MAXN*2;

	uint S[MAXNN]; int Si = n*2-1;
	for (int i = n*2-1; i >= 0; i--) cin >> S[i];


	uint D[MAXNN]; uint Di = 0;
	char DS[MAXN+1]; memset(DS, false, MAXN+1);

	uint output[1000001]; uint outputI = 0;
	ostringstream out;

	while(Si >= 0) {
		uint x = S[Si--];
		if (DS[x] == false) { 
			D[++Di] = x;
			DS[x] = true;
		} else {
			uint y = D[Di--];
			DS[y] = false;
			if (x != y) {
				output[outputI++] = Di+1;
				S[++Si] = y;
				S[++Si] = x;
			}
		}
	}
	cout << outputI << '\n';
	for (uint i = 0; i < outputI; i++) cout << output[i] << '\n';
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
