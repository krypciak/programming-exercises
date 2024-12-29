#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'queensAttack' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. INTEGER r_q
 *  4. INTEGER c_q
 *  5. 2D_INTEGER_ARRAY obstacles
 */

int queensAttack(int n, int k, int r_q, int c_q,
                 vector<vector<int>> obstacles) {
  n++;
  int qx = r_q;
  int qy = c_q;

  vector<set<int>> obY(n, set<int>());
  vector<set<int>> obX(n, set<int>());

  for (vector<int> obs : obstacles) {
    int x = obs[0];
    int y = obs[1];
    obY[y].insert(x);
    obX[x].insert(y);
  }

  int sum = 0;

  // down
  for (int y = qy + 1; y < n; y++) {
    if (binary_search(begin(obX[qx]), end(obX[qx]), y)) {
      break;
    }
    sum++;
  }
  // up
  for (int y = qy - 1; y >= 1; y--) {
    if (binary_search(begin(obX[qx]), end(obX[qx]), y)) {
      break;
    }
    sum++;
  }
  // right
  for (int x = qx + 1; x < n; x++) {
    if (binary_search(begin(obY[qy]), end(obY[qy]), x)) {
      break;
    }
    sum++;
  }
  // left
  for (int x = qx - 1; x >= 1; x--) {
    if (binary_search(begin(obY[qy]), end(obY[qy]), x)) {
      break;
    }
    sum++;
  }

  // down right
  for (int x = qx + 1, y = qy + 1; x < n && y < n; x++, y++) {
    if (binary_search(begin(obY[y]), end(obY[y]), x)) {
      break;
    }
    sum++;
  }

  // down left
  for (int x = qx - 1, y = qy + 1; x >= 1 && y < n; x--, y++) {
    if (binary_search(begin(obY[y]), end(obY[y]), x)) {
      break;
    }
    sum++;
  }

  // up right
  for (int x = qx + 1, y = qy - 1; x < n && y >= 1; x++, y--) {
    if (binary_search(begin(obY[y]), end(obY[y]), x)) {
      break;
    }
    sum++;
  }

  // up left
  for (int x = qx - 1, y = qy - 1; x >= 1 && y >= 1; x--, y--) {
    if (binary_search(begin(obY[y]), end(obY[y]), x)) {
      break;
    }
    sum++;
  }

  return sum;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string first_multiple_input_temp;
  getline(cin, first_multiple_input_temp);

  vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

  int n = stoi(first_multiple_input[0]);

  int k = stoi(first_multiple_input[1]);

  string second_multiple_input_temp;
  getline(cin, second_multiple_input_temp);

  vector<string> second_multiple_input =
      split(rtrim(second_multiple_input_temp));

  int r_q = stoi(second_multiple_input[0]);

  int c_q = stoi(second_multiple_input[1]);

  vector<vector<int>> obstacles(k);

  for (int i = 0; i < k; i++) {
    obstacles[i].resize(2);

    string obstacles_row_temp_temp;
    getline(cin, obstacles_row_temp_temp);

    vector<string> obstacles_row_temp = split(rtrim(obstacles_row_temp_temp));

    for (int j = 0; j < 2; j++) {
      int obstacles_row_item = stoi(obstacles_row_temp[j]);

      obstacles[i][j] = obstacles_row_item;
    }
  }

  int result = queensAttack(n, k, r_q, c_q, obstacles);

  fout << result << "\n";

  fout.close();

  return 0;
}

string ltrim(const string &str) {
  string s(str);

  s.erase(s.begin(),
          find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
      s.end());

  return s;
}

vector<string> split(const string &str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
