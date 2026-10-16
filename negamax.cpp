// 盤面の状態が state である状態からスタートして、
// その状態で手番であるプレイヤーの得られる得点から、
// 相手プレイヤーの得られる得点を引いた値の最大値を返す
int dfs(State state) {
    // 終端条件
    if (state が終局である) return (終局に応じた得点);

    // 打てる手をすべて試す
    int res = -INF;
    for (state2  : state から遷移できる局面全て) {
        int score = -dfs(state2);  // dfs(state2) は相手視点の得点なので、-1 倍する
        int add = (その手を打つこと自体の得点変化);  // 0 であることも多い
        res = max(res, score + add);
    }
    return res;
}