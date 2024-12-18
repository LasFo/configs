#include "atcoder/all"
#include "bits/stdc++.h"
#include <ostream>

using namespace std;
using namespace atcoder;
using _int = int;

#define YESNO(b) ((b) ? "Yes" : "No")
#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define FOR3(i, x, n) for (int i = (x); i < (n); i++)
#define FOR2(i, n) FOR3(i, 0, n)
#define FOR(...) GET_MACRO(__VA_ARGS__, FOR3, FOR2)(__VA_ARGS__)
#define REP(n) FOR(__i, n)
#define int long long
#undef INT_MAX
#define INT_MAX numeric_limits<int>::max()
#undef INT_MIN
#define INT_MIN numeric_limits<int>::min()
#define vi vector<int>
#define vvi vector<vector<int>>
#define ALL(c) c.begin(), c.end()
#define SORT(x) sort(ALL(x))
#define SUM(x) accumulate(ALL(x), 0LL)
#define SZ(x) ((int)x.size())
#define pb push_back
#define ii pair<int, int>
#define vii vector<pair<int, int>>
#define DIR4                                                                   \
  {                                                                            \
    {0, 1}, {1, 0}, {0, -1}, { -1, 0 }                                         \
  }
#define DIR8                                                                   \
  {                                                                            \
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, { 1, 1 }     \
  }
#define DIR9                                                                   \
  {                                                                            \
    {1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}, {1, -2}, { 2, -1 }   \
  }
template <typename T> void read(vector<T> &a) { FOR(i, SZ(a)) cin >> a[i]; }

template <typename T> void read(vector<T> &a, vector<T> &b) {
  FOR(i, SZ(a)) cin >> a[i] >> b[i];
}

template <typename T> void read(vector<T> &a, vector<T> &b, vector<T> &c) {
  FOR(i, SZ(a)) cin >> a[i] >> b[i] >> c[i];
}

template <typename T> void read(vector<vector<T>> &a) {
  FOR(i, SZ(a)) read(a[i]);
}

template <typename T> void pp(const vector<T> &a, string d = " ") {
  for (T x : a)
    cout << x << d;
  cout << endl;
}

template <typename T> void pp(const vector<vector<T>> &a, string d = " ") {
  for (auto &b : a) {
    pp(b, d);
  }
}

int popcnt(unsigned int x) { return __builtin_popcountll(x); }
int clz(unsigned int x) { return __builtin_clzll(x); }

template <typename T> bool chmax(T &a, const T b) {
  return a < b ? a = b, true : false;
}
template <typename T>
class min_heap : public priority_queue<T, vector<T>, greater<T>> {};

template <typename T>
class max_heap : public priority_queue<T, vector<T>, less<T>> {};

template <typename T> T sgn(const T a) { return (a > 0) - (a < 0); }
template <typename T> bool chmin(T &a, const T b) {
  return a > b ? a = b, true : false;
}
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
  (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'),                        \
      (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'),                    \
      (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),                    \
      (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

#define fst first
#define snd second
#define vc vector<char>
#define vvc vector<vector<char>>
#define mpow pow_mod
#define eb emplace_back
using mint = atcoder::modint998244353;
// using mint = atcoder::modint1000000007;

#define YESNO(b) ((b) ? "Yes" : "No")

_int main() {
  string line;
  vii blocks;
  while (getline(cin, line, '\n')) {
    int x, y;
    char delim;
    stringstream(line) >> y >> delim >> x;
    blocks.emplace_back(x, y);
  }
  int const h = 71, w = 71, bs = 1024;
  //int const h = 7, w = 7, bs = 12;
  vvc grid(h, vc(w, '.'));
  FOR(i, blocks.size()) {
    auto [x, y] = blocks[i];
    grid[x][y] = '#';
    vvi vis(h, vi(w, 0));
    queue<tuple<int, int>> q;
    q.emplace(0, 0);
    vii dirs = DIR4;
    auto check = [](int x, int y) {
      return x >= 0 && x < h && y >= 0 && y < w;
    };
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      for (auto [dx, dy] : dirs) {
        int nx = x + dx;
        int ny = y + dy;
        if (!check(nx, ny) || vis[nx][ny] || grid[nx][ny] == '#')
          continue;
        vis[nx][ny] =  1;
        if (nx == h - 1 && ny == w - 1)
          goto end;
        q.emplace(nx, ny);
      }
    }
  end:
    if (vis[h - 1][w - 1] == 0) {
      cout << x << ' ' << y << endl;
      return 0;
    }
  }
}
