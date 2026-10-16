//最長増加部分列の長さを求める
//is_strong=false -> 重複可
template<class T>  int LIS(vector<T> a, bool is_strong=true){
  const T IINF =1<<30;
  int n=(int)a.size();
  vector<T> dp(n,IINF);
  rep(i,n){
    //dp[k]>=a[i]となる最小のイテレータを見つける
    //そこをa[i]で書き換える
    if(is_strong)*lower_bound(all(dp),a[i])=a[i];
    else *upper_bound(all(dp),a[i])=a[i];
  }
  //dp[k]<INFとなる最大のkに対してk+1が答え
  //つまりdp[k]>=INFとなる最小のkと一致する
  return lower_bound(all(dp),IINF)-dp.begin();
}
