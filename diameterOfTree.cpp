//木の直径
//重みなしなら１をそれぞれ入れとく
//stが出発点、nがグラフのサイズ
//podis->trueで次の出発点、falseで木の直径を出力
ll diameterOfTree(vector<VP> &g, int st,int n, bool podis){
  
  ll ma=-1;
  ll po=-1;
  queue<ll>q;
  q.push(st);
  V dis(n,0);
  dis[st]=1;
  while(!q.empty()){
    int pa=q.front();q.pop();
    fore(e,g[pa]){
      if(dis[e.first]!=0)continue;
      dis[e.first]=dis[pa]+e.second;
      q.push(e.first);
      if(chmax(ma,dis[e.first]))po=e.first;
    }
  }
  if(podis)return po;
  else return ma-1;
}
