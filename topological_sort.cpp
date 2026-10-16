//DAG<->トポソ可能　不可能ならret.size()!=nのハズ…
//辞書順最小ならmin_priority_queue
//グラフ，頂点の入次数，頂点数nを受け取ってトポロジカルソートを返すO(|V|+|E|)
V topological_sort(G &g,V &ind, int &n){
  V ret;
  
  queue<int>q;//入次数0の頂点を入れるキュー
  rep(i,n){//一旦全部探す
    if(ind[i]==0){
      q.push(i);
    }
  }
  //キューが空になるまで
  // 1.入次数0の頂点vを発見する。
  // 2.頂点vを配列の末尾に追加する。
  // 3.有向グラフから頂点vと、その頂点から出ている辺をすべて削除
  // を試す
  while(!q.empty()){
    int p=q.front();
    q.pop();
    fore(e,g[p]){
      ind[e]-=1;
      if(ind[e]==0)q.push(e);
    }
    ret.push_back(p);
  }
  return ret;
}
