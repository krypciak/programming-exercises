#include <iostream>

#ifdef DEBUG
#include <print>
#include <fstream>
#include <sstream>
#endif

using namespace std;

typedef long long ll;

int run(istream &cin, ostream &cout) {
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
