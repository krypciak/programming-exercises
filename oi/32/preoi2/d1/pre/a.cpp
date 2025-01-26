#include <bits/stdc++.h>
using namespace std;

#ifdef TEST
int run(istream &cin, ostream &cout) {
#else
int main() {
#endif
	ios_base::sync_with_stdio(0), cin.tie(0);
	typedef long long ll;

	int d; // ilosc dni
	int p; // ilost zadan
	cin >> d >> p;

	struct Day {
		int t; // minimalna trudnosc
		int s; // satysfakcja za zadanie w ten dzien

		bool operator<(const Day &a) const { return s == a.s ? t < a.t : s > a.s; }
	};
	vector<Day> days; 
	days.reserve(d);
	int minT = INT_MAX;
	for (int i = 0; i < d; i++) {
		int t, s;
		cin >> t >> s;
		if (s == 0) continue;
		minT = min(minT, t);
		days.push_back({t, s});
	}
	sort(days.begin(), days.end());

	struct Task {
		int t; // trudnosc zadania
		int s; // strata satysfakcji za zadanie;

		bool operator<(const Task &a) const { return t == a.t ? s < a.s : t < a.t; }
	};
	vector<Task> tasks;
	tasks.reserve(p);
	for (int i = 0; i < p; i++) {
		int t, s;
		cin >> t >> s;
		if (t < minT) continue;
		tasks.push_back({t, s});
	}
	sort(tasks.begin(), tasks.end());

	#ifdef TEST
	bool debug = false;
	#else
	bool debug = false;
	#endif

	if (debug) {
		for (int i = 0; i < (int)days.size(); i++) 
			std::cout << "day " << i << ": " << days[i].t << ", " << days[i].s << endl;
		std::cout << endl;
	}

	ll sum = 0;
	for (auto t : tasks) {
		if (debug) std::cout << "t: " << t.t << ", " << t.s << endl;

		ll maxTaskS = 0;
		for (auto a : days) {
			if (t.t < a.t) continue;
			maxTaskS = max(maxTaskS, (ll)a.s - t.s);
			break;
		}
		sum += maxTaskS;
	}

	cout << sum << endl;
	return 0;
}
#ifdef TEST
string rtrim(string s) {
	auto end = s.find_last_not_of(" \t\r\v\f\n");
	return end == string::npos ? s : s.substr(0, end+1);
}
void printT(string name, string outS, string expS) {
	if (outS == expS) {
		printf("\u001b[32m\u001b[1m\u221A\u001b[0m\u001b[22m %s success\n", name.c_str());
	} else {
		printf("\u001b[31m\u001b[1mx\u001b[0m\u001b[22m %s fail! expected: \n'%s'\n---got: \n'%s'\n\n", name.c_str(), expS.c_str(), outS.c_str());
	}
}
void test(string name) {
	ifstream in(name+".in");
	ostringstream out;

	run(in, out);
	string outS = rtrim(out.str());

	ifstream exp(name+".out");
	string expS(istreambuf_iterator<char>{exp}, {});
	expS = rtrim(expS);

	printT(name, outS, expS);
}
int main() {
	test("ex0");
	test("ex1");
	return 0;
}
#endif

