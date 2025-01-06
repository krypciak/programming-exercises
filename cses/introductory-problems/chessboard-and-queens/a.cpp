#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <variant>
#include <functional>
#include <iterator>

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
	return 0;
}
#endif
