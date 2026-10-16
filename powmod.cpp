//繰り返し二乗法
//aのb乗をmで割ったあまりを返す関数
//変数aはa^1→a^2→a^4→a^8→…と変化
ll powmod(ll a,ll b, ll m){
  if(!b)return 1;
  a%=m;
  ll r=powmod(a,b/2,m);
  (r*=r)%=m;
  if(b%2)(r*=a)%=m;
  return r;
}