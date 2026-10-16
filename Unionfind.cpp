//以下、素集合と木は同じものを表す
class UnionFind{
public:
    vector<ll> parent; //parent[i]はiの親
    vector<ll> siz; //素集合のサイズを表す配列(1で初期化)
    map<ll,vector<ll>> group; //集合ごとに管理する(key:集合の代表元、value:集合の要素の配列)
    ll n; //要素数

    //配列追加ゾーン
    vector<int> min_node;
    vector<int> max_node;



    //コンストラクタ
    UnionFind(ll n_):n(n_),parent(n_),siz(n_,1) , min_node(n),max_node(n){ 
        //全ての要素の根が自身であるとして初期化
        for(ll i=0;i<n;i++){parent[i]=i;}
        for (int v = 0; v < n; ++v) min_node[v] = v;
        for (int v = 0; v < n; ++v) max_node[v] = v;
    }

    //データxの属する木の根を取得(経路圧縮も行う)
    ll root(ll x){
        if(parent[x]==x) return x;
        return parent[x]=root(parent[x]);//代入式の値は代入した変数の値なので、経路圧縮できる
    }

    //xとyの木を併合
    void unite(ll x,ll y){
        ll rx=root(x);//xの根
        ll ry=root(y);//yの根
        if(rx==ry) return;//同じ木にある時
        //小さい集合を大きい集合へと併合(ry→rxへ併合)
        if(siz[rx]<siz[ry]) swap(rx,ry);
        siz[rx]+=siz[ry];
        parent[ry]=rx;//xとyが同じ木にない時はyの根ryをxの根rxにつける
        
        // min_node,max_node の更新

        min_node[rx] = min(min_node[rx], min_node[ry]);
        max_node[rx] = max(max_node[rx], max_node[ry]);
    }

    //xとyが属する木が同じかを判定
    bool issame(ll x,ll y){
        ll rx=root(x);
        ll ry=root(y);
        return rx==ry;
    }

    //xの素集合のサイズを取得
    ll size(ll x){
        return siz[root(x)];
    }

    //素集合をそれぞれグループ化
    void grouping(){
        //経路圧縮を先に行う
        rep(i,n)root(i);
        //mapで管理する(デフォルト構築を利用)
        rep(i,n)group[parent[i]].push_back(i);
    }

    //素集合系を削除して初期化
    void clear(){
        rep(i,n){parent[i]=i;}
        siz=vector<ll>(n,1);
        group.clear();
    }
};




