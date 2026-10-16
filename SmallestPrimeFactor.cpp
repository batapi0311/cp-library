//spf[i] 整数iについて、最小の素因数 高速素因数分解
//ABC445"https://atcoder.jp/contests/abc445/submissions/73334101"を参考
const ll MAX_A = 10000005;
ll spf[MAX_A];
// SPF構築 (O(N log log N))
void SPF(){
  iota(spf, spf + MAX_A, 0);
  for (int i = 2; i * i < MAX_A; i++) {
    if (spf[i] == i) {
      for (int j = i * i; j < MAX_A; j += i) {
        if (spf[j] == j) spf[j] = i;
      }
    }
  }
}



//相異なる素因数の個数を数える
const ll MAX_A = 20202021;
int mnp[MAX_A];  // 最小素因数
int cnt[MAX_A];  // 相異なる素因数の個数

void buildCnt(){
  for(int i=2;i<MAX_A;i++){
    if(mnp[i]==0){
      for(int j=i;j<MAX_A;j+=i){
        if(mnp[j]==0) mnp[j]=i;
      }
    }
  }
  for(int i=2;i<MAX_A;i++){
    int k=mnp[i];
    int u=i;
    while(u%k==0) u/=k;
    cnt[i]=cnt[u]+1;
  }
}