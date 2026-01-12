#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;


	for (int i = 1; i <= n; i++) {
		auto calc = [i]() -> ll {
			if (i == 1) return 0;
			if (i == 2) return 6;

			ll size = i * i - 1;
			ll allPoss = (size * (size+1))/2;
			
			ll squareWH = i - 2;
			ll neg = 8;

			neg += (squareWH - 1) * 6; // x+
			neg += (squareWH - 1) * 6; // y+

			ll squareC = (squareWH - 1) * (squareWH - 1);
			neg += squareC * 4;

			ll res = allPoss - neg;

			return res;
		};

		cout << calc() << endl;
	}
	return 0;
}

#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
int main() {
	test("ex0");
	return 0;
}
#endif
