#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);

	const int bs = 8;

	vector<string> inp(bs);
	for (int i = 0; i < bs; i++) {
		cin >> inp[i];
	}
	function<int(int, const vector<bool>&, const vector<bool>&, const vector<bool>&)> rec =
		[&](int qx, const vector<bool> &yTaken, const vector<bool> &diagUpTaken, const vector<bool> &diagDownTaken)
		-> int {

		if (qx == 8) {
			return 1;
		}
		int ret = 0;
		for (int qy = 0; qy < 8; qy++) {
			if (yTaken[qy]) continue;
			if (inp[qy][qx] == '*') continue;

			int diagUp = qy - qx;
			if (diagUp < 0) diagUp = -diagUp + 7;
			assert(diagUp >= 0 && diagUp <= 14);
			if (diagUpTaken[diagUp]) continue;

			int diagDown = qy + qx;
			assert(diagDown >= 0 && diagDown <= 14);
			if (diagDownTaken[diagDown]) continue;

			vector<bool> nyTaken = yTaken;
			nyTaken[qy] = true;
			vector<bool> ndiagUpTaken = diagUpTaken;
			ndiagUpTaken[diagUp] = true;
			vector<bool> ndiagDownTaken = diagDownTaken;
			ndiagDownTaken[diagDown] = true;

			ret += rec(qx+1, move(nyTaken), move(ndiagUpTaken), move(ndiagDownTaken)); 
		}
		return ret;
	};

	int res = rec(0, vector<bool>(8, false), vector<bool>(15, false), vector<bool>(15, false));
	cout << res << endl;
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
