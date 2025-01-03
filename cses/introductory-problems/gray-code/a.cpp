#include <iostream>
#include <vector>
#include <cmath>

#ifdef DEBUG
#include <print>
#include <fstream>
#include <sstream>
#endif

using namespace std;

typedef long long ll;

struct Seg {
	int stage;
	bool half;
	bool l;
	bool r;
};

int run(istream &cin, ostream &cout) {
	int n;
	cin >> n;

	int segsL = ceil((double)n / 2);
	vector<Seg> segs(segsL, {0, false, false, false});
	if (n % 2 == 1) segs[0].half = true;

	const int perms = 1 << n;

	auto printSegs = [&]() {
		for (int i = 0; i < segsL; i++) {
			if (segs[i].half) {
				cout << (int)segs[i].r;
			} else {
				cout << (int)segs[i].l << (int)segs[i].r;
			}
		}
		cout << "\n";
	};
	printSegs();
	for (int i = 1; i < perms; i++) {
		Seg *seg;
		if (i % 4 == 0) {
			for (int j = segsL - 2; j >= 0; j--) {
				if (segs[j].stage == 3) continue;
				seg = &segs[j];
				for (int k = j + 1; k < segsL; k++) {
					segs[k].stage = 0;
				}
				break;
			}
		} else {
			seg = &segs[segsL-1];
		}
		if (seg->stage == 0) {
			seg->r = !seg->r;
			seg->stage++;
		} else if (seg->stage == 1) {
			seg->l = !seg->l;
			seg->stage++;
		} else if (seg->stage == 2) {
			seg->r = !seg->r;
			seg->stage++;
		}
		printSegs();
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
	tf("ex1");
	return 0;
}
#else
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return run(cin, cout);
}
#endif
