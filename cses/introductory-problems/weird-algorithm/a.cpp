#include <iostream>

#ifdef DEBUG
#include <sstream>
#include <fstream>
#include <print>
#endif

using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
	ll n;
	cin >> n;

	while (n != 1) {
		cout << n << " ";
		if (n % 2 == 0) {
			n /= 2;
		} else {
			n = n * 3 + 1;
		}
	}
	cout << n << endl;
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
