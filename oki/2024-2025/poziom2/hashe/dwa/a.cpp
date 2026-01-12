#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int al, bl;
string a, b;
vector<ll> AP, BP;

const ll M = 1e9 + 21;
const int BASE = 31;
vector<ll> MUL;

bool check(int a1, int a2, int b1, int b2) {
	if (a2-a1 != b2-b1) return false;

	ll ah = (M + AP[a2] - AP[a1-1]) % M;
	ll bh = (M + BP[b2] - BP[b1-1]) % M;

	if (a1 >= b1) {
		bh = (bh * MUL[a1-b1]) % M;
	} else {
		ah = (ah * MUL[b1-a1]) % M;
	}
	return ah == bh;
}

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> al >> bl;
	cin >> a >> b;

	MUL.assign(max(al, bl), 0);
	MUL[0] = 1;
	for (int i = 1; i < (int)MUL.size(); i++) MUL[i] = (MUL[i-1]*BASE) % M;

	AP.assign(al+1, 0);
	BP.assign(bl+1, 0);
	for (int i = 0; i < al; i++) AP[i+1] = (AP[i] + (a[i]*MUL[i])%M) % M;
	for (int i = 0; i < bl; i++) BP[i+1] = (BP[i] + (b[i]*MUL[i])%M) % M;

	int q;
	cin >> q;
	while(q--) {
		int a1, a2, b1, b2;
		cin >> a1 >> a2 >> b1 >> b2;
		if (check(a1, a2, b1, b2)) cout << "TAK" << '\n';
		else cout << "NIE" << '\n';
	}
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../../../tester.h"
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif
