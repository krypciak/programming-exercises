#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
 
int run(istream &cin, ostream &cout) {
	ios_base::sync_with_stdio(0), cin.tie(0);
 
	int q;
	cin >> q;
 
	auto pow10 = [](int to) {
		ll res = 1;
		for (int i = 0; i < to; i++) res *= 10;
		return res;
	};
 
	for (int qi = 0; qi < q; qi++) {
		ll k;
		cin >> k;
 
		int i = 1;
		for (;; i++) {
			ll sub = i*9 * pow10(i-1);
			if (k <= sub) break; 
			k -= sub;
		}
 
		long num = (k - 1) / i + pow10(i - 1);
		int loc = (int)((k - 1) % i);
		cout << to_string(num)[loc] << endl;
	}
	return 0;
}
 
#ifndef TEST
int main() { run(cin, cout); }
#else
#include "../../../tester.h"
void fuzz() {
	const int N = 4;
	string str = " ";
	for (int i = 0; i < N; i++) {
		for (ll v = pow(10, i); v < pow(10, i+1); v++) {
			str += to_string(v);
		}
	}
 
	int k;
	for (k = 1; k < (int)str.size(); k++) {
		istringstream in(format("1\n{}", k));
		ostringstream out;
		run(in, out);
		string resStr = rtrim(out.str());
 
		bool isOk = isTestOk("", format("{}", str[k]), resStr);
		printT(format("fuzz k: {}", k), format("{}", str[k]), resStr, "", isOk);
		if (!isOk) {
			const int from = 10;
			const int to = 10;
			for (int j = k - from; j < k + to; j++) cout << j << '\t';
			cout << endl;
			for (int j = k - to; j < k + from; j++) cout << str[j] << '\t';
			cout << endl;
			break;
		}
		if (k % 1000000 == 0) {
			print("{} / {}\n", k, str.size());
		}
	}
	if (k == (int)str.size()) {
		printT("fuzz all", "", "", "", true);
	}
}
int main() {
	test("ex0");
	test("ex1");
	fuzz();
	return 0;
}
#endif
