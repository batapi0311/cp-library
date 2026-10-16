//全点対間最短経路
//負閉路があるのはk->kが負になるときO(V^3)
//繋がってるかどうかはdist[i][j]!=wfinfで判定可能
ll dist[0][0];////!!!!!!!!!!!!!グラフサイズ入れる
#define wfinf 1e15
//最初にk->kは0，それ以外はwfinfで初期化
void warshall_floyd(int n) {
  for (int k = 0; k < n; k++){       // 経由する頂点
    for (int i = 0; i < n; i++) {    // 始点
      for (int j = 0; j < n; j++) {  // 終点
        if(dist[i][k]==wfinf and dist[k][j]==wfinf)continue;
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}
//追加した点のみ見るのでO(V^2)
void add_edge(int s, int t, ll cost,int n)
{
  dist[s][t] = dist[t][s] = min(dist[s][t], cost);
  for(int k : {s, t}) {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}