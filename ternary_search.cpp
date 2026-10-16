// 整数上の凸関数の最大値を求める三分探索
// 関数 f(x) が上に凸（単峰性）の場合に、f(x) が最大となる x を返す
// l: 探索範囲の下限, r: 探索範囲の上限 (閉区間 [l, r])
template <typename F>
ll ternary_search_int_max(ll l, ll r, F f) {
  while (r - l > 2) {
    ll m1 = l + (r - l) / 3;
    ll m2 = r - (r - l) / 3;
    if (f(m1) < f(m2)) {
      l = m1;
    } else {
      r = m2;
    }
  }
  
  ll best_x = l;
  ll max_val = f(l);
  for (ll i = l + 1; i <= r; ++i) {
    ll current_val = f(i);
    if (chmax(max_val, current_val)) {
      best_x = i;
    }
  }
  return best_x;
}

// 実数上の凸関数の最大値を求める三分探索
// 関数 f(x) が上に凸（単峰性）の場合に、f(x) が最大となる x を返す
// l: 探索範囲の下限, r: 探索範囲の上限, iter: ループ回数 (デフォルト100回)
template <typename F>
double ternary_search_double_max(double l, double r, F f, int iter = 100) {
  rep(i, iter) {
    double m1 = l + (r - l) / 3.0;
    double m2 = r - (r - l) / 3.0;
    if (f(m1) < f(m2)) {
      l = m1;
    } else {
      r = m2;
    }
  }
  return l;
}