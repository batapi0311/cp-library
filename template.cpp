#include <bits/stdc++.h>
// #include <ranges>
#define _USE_MATH_DEFINES
// aclをatcoder以外で使うときは'combine [ファイル名]'とターミナルに打てばよい
//  #include <atcoder/dsu>
//  #include <atcoder/modint>
#include <atcoder/all>
// #include<atcoder/lazysegtree>
// #include<atcoder/string>
// #include<atcoder/fenwicktree>
using namespace atcoder;
// using mint = modint998244353;
// using mint = modint1000000007;
using namespace std;
// using mint = modint;
using ll = long long;
using ld = long double;
using lll = __int128_t;
#define rep(i, n) for(ll i = 0; i < (ll)(n); i++)
#define rep2(i, s, n) for(ll i = (s); i < (ll)(n); i++)
#define rrep(i, a, b) for(ll i = a; i >= b; i--)
#define fore(i, a) for(auto& i : a)
#define V vector<ll>
#define Vi vector<int>
#define Vd vector<double>
#define Vld vector<long double>
#define Vb vector<bool>
#define Vs vector<string>
#define Vc vector<char>
#define VV vector<V>
#define Vm vector<mint>
using P = pair<ll, ll>;
using G = vector<vector<ll>>;
#define VP vector<P>
#define VT vector<tuple<ll, ll, ll>>

template <typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#define inf 1e9
template <typename T>
bool chmax(T& a, const T& b) {
  if(a < b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}
template <typename T>
bool chmin(T& a, const T& b) {
  if(a > b) {
    a = b;  // aをbで更新
    return true;
  }
  return false;
}

long long combi(long long n, long long k) {
  if(n == k || k == 0)
    return 1;
  else {
    return combi(n - 1, k - 1) + combi(n - 1, k);
  }
}
// 二項係数
#define CMAX 1010
int noinit = 1;
ll acbmemo[CMAX][CMAX];
ll aCb(ll a, ll b) {
  if(noinit) {
    rep2(i, 0, CMAX) rep2(j, 0, CMAX) acbmemo[i][j] = -1;
    noinit = 0;
  }
  if(b == 0 || a == b) return 1;
  if(0 <= acbmemo[a][b]) return acbmemo[a][b];
  return acbmemo[a][b] = aCb(a - 1, b - 1) + aCb(a - 1, b);
}
// 整数かどうか
bool isNumber(const string& str) {
  for(const char& c : str) {
    if(std::isdigit(c) == 0) return false;
  }
  return true;
}
///*
// 最大公約数
ll gcd(ll a, ll b) {
  if(b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}
// 最小公倍数
ll lcm(ll a, ll b) {
  ll g = gcd(a, b);
  return a / g * b;
}

std::ostream& operator<<(std::ostream& dest, __int128_t value) {
  std::ostream::sentry s(dest);
  if(s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char* d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while(tmp != 0);
    if(value < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if(dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}
//*/

// s = regex_replace(s, regex("あ"), "う");
/*stiring で char を検索するときは
    s.find(c)!=string::npos
 */

///*//各桁の和
int wa(int n) {
  int sum = 0;
  while(n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}
//*/
//
/*
//階乗
 int ki(int i){
   int k = 1;
   for(int j = 1; j<=i; j++){
     k *= j;
   }
   return k;
 }
//
*/
/*log_x(b)
double logN(double x, double b) {
    return log(x) / log(b);
}
*/
///*
// エラトステネスの篩O(NloglogN) main関数内にSieveofEratosthenes();を書き込む!!
const ll N = 1010101;  // 求める範囲
Vb isp(N + 1, true);
void SieveofEratosthenes() {
  isp[0] = false;
  isp[1] = false;
  for(ll i = 2; i + i <= N; i++) {
    if(isp[i])
      for(ll j = 2; i * j <= N; j++) isp[i * j] = false;
  }
}
//*/

///*
// 約数列挙 O(√n)
vector<long long> divisor(long long n) {
  vector<long long> ret;
  for(long long i = 1; i * i <= n; i++) {
    if(n % i == 0) {
      ret.push_back(i);
      if(i * i != n) ret.push_back(n / i);
    }
  }
  // sort(ret.begin(), ret.end()); // 昇順に並べる
  return ret;
}
//*/

///*
// 素因数分解O(√n)
map<ll, ll> prime_factor(ll n) {
  map<ll, ll> ret;
  for(ll i = 2; i * i <= n; i++) {
    while(n % i == 0) {
      ret[i]++;
      n /= i;
    }
  }
  if(n != 1) ret[n] = 1;
  return ret;
}
//*/

/*
ll modpow(ll x, ll n, ll mod){
 while(n){
   ll resu = 1;
   if(n&1)res = (res * x) %mod;
   x = (x*x)%mod;
   n>>=1;
 }
 return res;
}
*/
///*
// 繰り返し二乗法
// aのb乗をmで割ったあまりを返す関数
// 変数aはa^1→a^2→a^4→a^8→…と変化
ll powmod(ll a, ll b, ll m) {
  if(!b) return 1;
  a %= m;
  ll r = powmod(a, b / 2, m);
  (r *= r) %= m;
  if(b % 2) (r *= a) %= m;
  return r;
}
//*/
//
/*
//0~xまでのxor累積和
ll xor_sum(ll x){
  if(x%2!=0){
    x-1;
    if((x/2)%2==0)return 1;
    else return 0;
  }else{
    if(x%4==0)return x;
    else return x+1;
  }
}
//
*/
///*
template <typename T>
bool next_combination(const T first, const T last, int k) {
  const T subset = first + k;
  // empty container | k = 0 | k == n
  if(first == last || first == subset || last == subset) {
    return false;
  }
  T src = subset;
  while(first != src) {
    src--;
    if(*src < *(last - 1)) {
      T dest = subset;
      while(*src >= *dest) {
        dest++;
      }
      iter_swap(src, dest);
      rotate(src + 1, dest + 1, last);
      rotate(subset, subset + (last - dest) - 1, last);
      return true;
    }
  }
  // restore
  rotate(first, subset, last);
  return false;
}
//*/
int ctoi(char c) {
  if(c >= '0' and c <= '9')
    return c - '0';
  else
    return -inf;
}
char touplo(char c) {
  char ret = c;
  ret ^= 32;
  return ret;
}
// vector<int> dx = {1,0,-1,0,1,-1,-1,1};
// vector<int> dy = {0,1,0,-1,1,1,-1,-1};
// 時計回り
int clx[4] = {0, 1, 0, -1}, cly[4] = {-1, 0, 1, 0};
// 反時計回り
int cclx[4] = {0, -1, 0, 1}, ccly[4] = {-1, 0, 1, 0};
int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1}, dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
// int dx[8]={0,-1,-1,-1,0,1,1,1},dy[8]={1,1,0,-1,-1,-1,0,1};
// #define mod 998244353
// cout << mint.val() << endl;
// cout << fixed << setprecision(15) << y << endl;

P mima(ll a, ll b) {
  P ret;
  ret = make_pair(min(a, b), max(a, b));
  return ret;
}

// bit s に i番目のビットを立てる
#define bittate(s, i) (s | (1LL << i))
// bit sから i番目のビットを消す
#define bitkeshi(s, i) (s ^ (1LL << i))
// bit s が i番目のビットを含んでいるか
bool bitcheck(ll s, ll i) {
  if((s >> i) & 1LL)
    return true;
  else
    return false;
}
// string str(bitset<32>(value).to_string<char, char_traits<char>,
// allocator<char> >());
#define ppc(n) __builtin_popcountll(n)
string lltobin(ll n) {
  string re(
      (bitset<61>(n).to_string<char, char_traits<char>, allocator<char>>()));
  return re;
}
ll bintoll(string s) {
  ll re = stoll(s, nullptr, 2);
  return re;
}
//-1なら外れてる、それ以外なら座標を1次元に変換
ll kabe_check(ll i, ll j, ll h, ll w) {
  if((i < 0 or h <= i or j < 0 or w <= j))
    return -1;
  else
    return i * w + j;
}
#define yes "Yes"
#define no "No"
#define Yes "YES"
#define No "NO"
// mt19937_64 rng(58);
#define INF 1LL << 61
// 昇順（小さい順）: a < b
// bool fcomp(const int& a, const int& b) { return a < b; }
// auto fcomp=[&](const int &a, const int&b)->bool{
//     return p[a]<p[b];
// };

void tk() {}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  for(; t--;) {
    tk();
  }
}
