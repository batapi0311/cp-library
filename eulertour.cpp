struct edge
{
  /* data */
  edge(ll v,ll c=1){to=v,w=c;}
  ll to;
  ll w;
};
V tour;
V in(303030);
V out(303030);
vector<vector<edge>> g(303030);
void dfs(int v,int p=-1){
  in[v]=tour.size();
  tour.push_back(v);
  fore(e,g[v])if(e.to!=p){
    dfs(e.to,v);
  }
  out[v]=tour.size();
  tour.push_back(v);
}