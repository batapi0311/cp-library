

// 巡回セールスマン問題 (bit DP + 経路復元)　O(N^2 * 2^N)
// 引数:
//   a: 隣接行列 (頂点間のコスト)
//   return_to_start: trueなら始点に戻る(閉路)、falseなら戻らない(パス)
//   start_node: 始点とする頂点 (-1 の場合は「任意の頂点からスタート可能」とする)
// 戻り値:
//   pair<ll, vector<int>>: {最小コスト, 訪問した頂点の順番(ルート)}
pair<ll, vector<int>> traveling_salesperson(const VV &a, bool return_to_start = true, int start_node = 0) {
    int n = a.size();
    int nn = 1 << n;
    
    // d[現在いる都市][訪問済みの集合] = 最小コスト
    VV d(n, V(nn, INF));
    // prev_node[現在いる都市][訪問済みの集合] = 1つ前にいた都市 (経路復元用)
    vector<vector<int>> prev_node(n, vector<int>(nn, -1));

    // 始点の初期化
    if (start_node != -1) {
        d[start_node][1 << start_node] = 0;
    } else {
        for (int i = 0; i < n; i++) d[i][1 << i] = 0;
    }

    // DPの遷移 (配るDP)
    for (int xx = 0; xx < nn; xx++) {
        for (int i = 0; i < n; i++) {
            if (d[i][xx] == INF) continue;

            ll dix = d[i][xx];
            for (int j = 0; j < n; j++) {
                if ((xx >> j) & 1) continue; // すでに訪問済みならスキップ
                
                int yy = xx | (1 << j);
                ll nd = dix + a[i][j];
                if (nd < d[j][yy]) {
                    d[j][yy] = nd;
                    prev_node[j][yy] = i; // どこから来たかを記録
                }
            }
        }
    }

    // 最小コストと最後の都市を特定
    ll min_cost = INF;
    int best_last_node = -1;
    int full = nn - 1; // 全部訪問済みの状態

    for (int i = 0; i < n; i++) {
        if (d[i][full] == INF) continue;
        
        ll current_cost = INF;
        if (return_to_start) {
            int goal = (start_node != -1) ? start_node : 0;
            current_cost = d[i][full] + a[i][goal];
        } else {
            current_cost = d[i][full];
        }

        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_last_node = i;
        }
    }

    // 経路復元
    vector<int> path;
    if (min_cost != INF) {
        int curr = best_last_node;
        int state = full;
        
        // ゴールから逆順に辿る
        while (curr != -1) {
            path.push_back(curr);
            int p = prev_node[curr][state];
            state ^= (1 << curr); // 現在の都市の訪問フラグを消す
            curr = p;
        }
        
        // 逆順で構築したので反転させる
        reverse(path.begin(), path.end());
        
        // 始点に戻る設定の場合は、パスの最後に始点を追加
        if (return_to_start) {
            int goal = (start_node != -1) ? start_node : 0;
            path.push_back(goal);
        }
    }

    return {min_cost, path};
}

//使い方
void tk() {
    // 距離行列 dist が構築されている前提
    
    // 例1: 都市0スタートで、すべての都市を巡って都市0に帰ってくる場合
    auto [ans_cost, ans_path] = traveling_salesperson(dist, true, 0);
    
    cout << "最小コスト: " << ans_cost << endl;
    cout << "ルート: ";
    for (int node : ans_path) {
        cout << node << " ";
    }
    cout << endl;
    
    // 例2: どこからスタートしても良く、最後はどこで終わっても良い場合（一筆書きパス）
    // auto [ans_cost, ans_path] = traveling_salesperson(dist, false, -1);
}