#include <iostream>
#include <cassert>

#ifdef DEBUG
#include <print>
#include <fstream>
#include <sstream>
#endif

using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		auto check = [](const ll a, const ll b) {
			ll topA = 2*b - a;
			if (topA >= 0 && topA % 3 == 0) {
				ll y = topA / 3;
				ll x = b - 2 * y;
				if (x >= 0) {
					assert(2*x + y == a);
					assert(x + 2*y == b);

					return true;
				}
			}
			return false;
		};

		ll a, b;
		cin >> a >> b;

		if (check(a, b)) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}


#ifdef DEBUG

string rtrim(const string &s) {
	size_t end = s.find_last_not_of(" \n\r\t\f\v");
	return (end == string::npos) ? "" : s.substr(0, end + 1);
}

void tf(string name) {
	ifstream in(format("{}.in", name));
	ostringstream out;
	
	ifstream exp(format("{}.out", name));
	string expStr(istreambuf_iterator<char>{exp}, {});
	expStr = rtrim(expStr);

	run(in, out);
	string outStr = rtrim(out.str());

	if (outStr != expStr) {
		print("test {} failed! expected: \n'{}'\n--- got \n'{}'\n", name, expStr, outStr);
	} else {
		print("test {} success\n", name);
	}
}

int main() {
	tf("ex0");
	return 0;
}
#else
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return run(cin, cout);
}
#endif
