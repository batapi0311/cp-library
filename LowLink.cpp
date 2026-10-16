//LowLink : 無向グラフの橋検出＋二重辺連結成分への分類
//add_edgeで辺を追加し、build()を呼ぶと使えるようになる
//bridge[辺id] : その辺が橋かどうか
//comp[頂点] : 二重辺連結成分の番号(0-indexed, 橋を除いたUnion-Findのグループ)
//comp_cnt : 二重辺連結成分の個数
// https://codeforces.com/problemset/submission/1000/383383006
struct LowLink{
  ll n;
  vector<VP> g;//g[v]={(to,edge_id)}
  V ord,low,par,par_edge;
  Vb used;
  VP edges;//edges[id]=(u,v)
  Vb bridge;//bridge[id]
  V comp;
  ll comp_cnt=0;

  LowLink(ll n_):n(n_),g(n_),ord(n_,-1),low(n_,-1),par(n_,-1),par_edge(n_,-1),used(n_,false),comp(n_,-1){}

  void add_edge(ll u,ll v){
    ll id=edges.size();
    edges.push_back({u,v});
    g[u].push_back({v,id});
    g[v].push_back({u,id});
  }

  //非再帰DFSでordとlowを計算(再帰だとスタックオーバーフローの恐れがあるため)
  void dfs(ll s,ll &k){
    vector<ll> stk={s};
    V iter(n,0);//各頂点で次に見る隣接リストのインデックス
    used[s]=true;
    ord[s]=low[s]=k++;
    while(!stk.empty()){
      ll v=stk.back();
      if(iter[v]<(ll)g[v].size()){
        auto [to,id]=g[v][iter[v]];
        iter[v]++;
        if(id==par_edge[v])continue;//親から来た辺はスキップ
        if(!used[to]){
          used[to]=true;
          ord[to]=low[to]=k++;
          par[to]=v;
          par_edge[to]=id;
          stk.push_back(to);
        }else{
          chmin(low[v],ord[to]);//後退辺
        }
      }else{
        stk.pop_back();
        if(par[v]!=-1)chmin(low[par[v]],low[v]);//子のlowを親へ伝播
      }
    }
  }

  void build(){
    ll k=0;
    rep(i,n)if(!used[i])dfs(i,k);

    //橋判定 : 木辺(v,u)(vが親)についてlow[u]>ord[v]なら橋
    bridge.assign(edges.size(),false);
    rep(i,edges.size()){
      auto [u,v]=edges[i];
      if(par_edge[u]==i)bridge[i]=(low[u]>ord[v]);
      else if(par_edge[v]==i)bridge[i]=(low[v]>ord[u]);
      //どちらでもなければ後退辺なので橋ではない(falseのまま)
    }

    //橋以外の辺だけでUnion-Findし、二重辺連結成分に分類
    dsu d(n);
    rep(i,edges.size())if(!bridge[i]){
      auto [u,v]=edges[i];
      d.merge(u,v);
    }
    rep(i,n){
      ll leader=d.leader(i);
      if(comp[leader]==-1)comp[leader]=comp_cnt++;
      comp[i]=comp[leader];
    }
  }
};