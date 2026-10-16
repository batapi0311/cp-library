// 単一始点最短路O(ElogV)
struct Edge {
  ll to;
  ll cost;
  // cost　1なら重みなしの最短経路
};
using Graph = vector<vector<Edge>>;

V Dijkstra(const Graph& g, ll n, int startIndex) {
  // 現時点での最短距離，頂点の順で取り出す(昇順)
  V dis(n, INF);
  priority_queue<P, vector<P>, greater<P>> q;
  q.emplace((dis[startIndex] = 0), startIndex);

  while(!q.empty()) {
    const ll di = q.top().first;
    const ll from = q.top().second;
    q.pop();
    // 最短距離のみ処理
    if(dis[from] < di) continue;

    for(const auto& edge : g[from]) {
      // toまでの距離
      const ll d = dis[from] + edge.cost;
      // 更新
      if(d < dis[edge.to]) {
        q.emplace((dis[edge.to] = d), edge.to);
      }
    }
  }
  return dis;
}
