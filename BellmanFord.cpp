//単一始点最短経路(VE)
//負閉路も可(検出も可)
//負閉路が存在するときtrueを返し，負へ露の影響を受ける頂点は-INFにセットされる
//頂点targetIndexが負閉路の影響を受けない時，頂点startIndexからの最短経路をpathに格納
//disは頂点数と同じサイズ，全要素をINFで初期化すること
struct Edge{
    int from;
    int to;
    int cost;
};

bool BellmanFord(const vector<Edge> & edges, vector<long long> &dis, int startIndex, int targetIndex, vector<int> &path){
    dis[startIndex]=0;
    //直前の頂点を記録する配列
    vector<int> p(dis.size(),-1);

    bool changed=false;
    for(size_t i=0; i<dis.size();i++){
        changed=false;
        //各辺についてみる
        for(const auto & edge : edges){
            //(INF+cost)はINFなので無視
            if(dis[edge.from]==INF)continue;
            //toまでの新しいキョリ
            const long long d=(dis[edge.from]+edge.cost);
            //dが現在の記録より小さければ更新する
            if(d<dis[edge.to]){
                dis[edge.to]=d;
                //直前の頂点を記録
                p[edge.to]=edge.from;
                changed=true;
            }
        }
        //どの頂点も行進が無かったら終了
        if(!changed){
            break;
        }
    }
    //負閉路あり
    if(changed){
        //頂点数分だけさらに繰り返して，負閉路の影響を受ける頂点に-INFを伝播
        for(size_t i=0; i<dis.size();i++){
            for(const auto &edge : edges){
                if(dis[edge.from]==INF){
                    continue;
                }
                const long long d=(dis[edge.from]+edge.cost);
                if(d<dis[edge.to]){
                    //負閉路の影響を受ける頂点をINFに
                    dis[edge.to]=-INF;
                }
            }
        }
    }
    //頂点targetIndexに到達不可または負閉路の影響を受ける頂点ときは最短経路無し
    if((dis[targetIndex]!=INF) and (dis[targetIndex]!=-INF)){
        for(int i=targetIndex; i!=-1;i=p[i]){
            path.push_back(i);
        }
    }
    reverse(path.begin(), path.end());
    return changed;
}
