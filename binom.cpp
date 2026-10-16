// 素数以外の二項係数はcommodを使えない
// mが小さければこれが使える
// cominitを書くのを忘れないこと！

const int MAX=5050;
ll binom[MAX][MAX];


//前処理
void cominit(ll mod){
  rep(n,MAX){
    binom[n][0]=1;
    rep2(k,1,n+1){
      binom[n][k]=(binom[n-1][k-1]+binom[n-1][k])%mod;
    }
  }
}