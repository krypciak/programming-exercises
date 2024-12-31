#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <vector>

using namespace std;

typedef long long ll;

template <typename T> struct std::formatter<vector<T>> {
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

  auto format(const vector<T> &v, format_context &ctx) const {
    for (int i = 0; i < (int)v.size(); i++) {
      format_to(ctx.out(), "{}", v[i]);
      if (i < (int)v.size() - 1) {
        format_to(ctx.out(), ",");
      }
    }
    return format_to(ctx.out(), "");
  }
};

struct JillTime {
  ll time;
  int i;

  bool operator<(const JillTime &v) const { return time < v.time; }
};

template <> struct std::formatter<JillTime> : std::formatter<std::string> {
  auto format(JillTime p, format_context &ctx) const {
    return formatter<string>::format(std::format("{}", p.time), ctx);
  }
};

struct Task {
  int time;
  ll deadline;

  bool operator<(const Task &v) const { return deadline < v.deadline; }
};

template <> struct std::formatter<Task> : std::formatter<std::string> {
  auto format(Task p, format_context &ctx) const {
    return formatter<string>::format(std::format("[{},{}]", p.time, p.deadline),
                                     ctx);
  }
};

void run(istream &cin, ostream &cout) {
  int testCases;
  cin >> testCases;

  for (int testCase = 0; testCase < testCases; testCase++) {
    int n; // the number of homework tasks
    int m; // the number of episodes
    int q; // the number of possible times for the call with Jill
    cin >> n >> m >> q;
    assert(1 <= n && n <= 200000);
    assert(1 <= m && m <= 200000);
    assert(1 <= q && q <= 200000);

    // 1 <= a <= 10^9 (int) the number of minutes it takes to complete the task
    // 1 <= d <= 10^15 (ll)
    // the deadline before which this task must be completed
    vector<Task> tasks(n);
    for (int i = 0; i < n; i++) {
      cin >> tasks[i].time;
    }

    for (int i = 0; i < n; i++) {
      cin >> tasks[i].deadline;
    }
    sort(begin(tasks), end(tasks));

    // 1 <= l <= 10^9 (int)
    // the length of episodes in the order they need to be watched
    vector<int> episodeLens(m);
    for (int i = 0; i < m; i++) {
      cin >> episodeLens[i];
    }

    // 1 <= t <= 10^15 (ll)
    // the possible times of call with jill
    vector<JillTime> jillTimes(q);
    for (int i = 0; i < q; i++) {
      ll time;
      cin >> time;
      jillTimes[i] = {time, i};
    }
    sort(begin(jillTimes), end(jillTimes));

    // if (testCase != 4)
    //   continue;

    // print("tasks {}\n", tasks);
    // print("episodeLens {}\n", episodeLens);
    // print("jillTimes {}\n", jillTimes);

    vector<ll> leeway(n);
    leeway[n - 1] = tasks[n - 1].deadline - tasks[n - 1].time;
    for (int i = n - 2; i >= 0; i--) {
      ll minimum = min(leeway[i + 1], tasks[i].deadline);
      leeway[i] = minimum - tasks[i].time;
    }
    // print("leeway: {}\n", leeway);

    vector<ll> result(q, -1);

    int episodeI = 0;
    int jillTimeI = 0;
    ll timeUsed = 0;

    auto checkJillTime = [&] {
      for (; jillTimeI < q && jillTimes[jillTimeI].time < timeUsed;
           jillTimeI++) {
        result[jillTimes[jillTimeI].i] = episodeI;
      }
    };

    for (int taskI = 0; taskI < n; taskI++) {
      ll timeLeft = leeway[taskI] - timeUsed;
      assert(timeLeft >= 0);
      for (; episodeI < m && timeLeft >= episodeLens[episodeI]; episodeI++) {
        timeLeft -= episodeLens[episodeI];
        timeUsed += episodeLens[episodeI];
        checkJillTime();
        // print("stuffing episode {} at task {}\n", episodeI, taskI);
      }

      timeUsed += tasks[taskI].time;
      checkJillTime();
    }

    for (; episodeI < m; episodeI++) {
      timeUsed += episodeLens[episodeI];
      // print("binging episode {}\n", episodeI);
      checkJillTime();
    }
    checkJillTime();

    for (int i = 0; i < q; i++) {
      if (result[i] == -1) {
        result[i] = m;
      }
    }

    for (int i = 0; i < q; i++) {
      if (i > 0) {
        cout << ' ';
      }
      cout << result[i];
    }
    cout << "\n";

    // print("\n");
  }
}

std::string rtrim(const string &s) {
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
    print("test {} failed! expected: \n'{}'\n--- got \n'{}'\n", name, expStr,
          outStr);
  } else {
    print("test {} success\n", name);
  }
}
void test() {
  tf("ex0");
  tf("ex1");
}

int main() {
#ifdef DEBUG
  test();
#else
  run(cin, cout);
#endif
  return 0;
}
