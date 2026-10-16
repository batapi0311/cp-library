//modintのincludeとmintの割り当て
//cominit()をちゃんと書く
//facが階乗　finvが逆数の階乗
const int MAX=202020;
mint fac[MAX],finv[MAX],inv[MAX];

//前処理
void cominit(){
  const int MOD=mint::mod();
  fac[0]=fac[1]=1;
  finv[0]=finv[1]=1;
  inv[1]=1;
  for(int i=2;i<MAX;i++){
    fac[i]=fac[i-1]*i;
    inv[i]=MOD-inv[MOD%i]*(MOD/i);
    finv[i]=finv[i-1]*inv[i];
  }
}

//二項係数
mint com(int n,int k){
  if(n<k)return 0;
  if(n<0 or k<0)return 0;
  return fac[n]*finv[k]*finv[n-k];
}
