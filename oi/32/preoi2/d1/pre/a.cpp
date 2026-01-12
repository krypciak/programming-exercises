#include <bits/stdc++.h>
using namespace std;

int run(istream &cin, ostream &cout) {
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

