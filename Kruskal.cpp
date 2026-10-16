//クラスカル法
//要Unionfind!!!!!!!!
//ret:=最小全域木の重みの総和
//n:=頂点の総数
//計算量:=O(m log{n})
//辺の構造体
struct Edge{
    ll u,v,cost;
    //後ろにconstつける！
    bool operator<(const Edge& e) const {return this->cost<e.cost;}
};
/*
ll Kruskal(vector<Edge> &edges,ll n){
    sort(all(edges));//辺の重みの昇順
    UnionFind uf(n);
    ll ret=0;
    fore(e,edges){
        //その辺を加える必要があるか
        if (!uf.same(e.u,e.v)){
            uf.unite(e.u,e.v);
            ret+=e.cost;
        }
    }
    return ret;
}
*/
ll aclKruskal(vector<Edge> &edges,ll n){
    sort(all(edges));//辺の重みの昇順(最大全域木なら降順にする)
    dsu uf(n);
    ll ret=0;
    fore(e,edges){
        //その辺を加える必要があるか
        if (!uf.same(e.u,e.v)){
            uf.merge(e.u,e.v);
            ret+=e.cost;
        }
    }
    return ret;
}