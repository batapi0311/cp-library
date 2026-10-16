// 区間を集合として管理する構造体（mex計算などに使える）
template <class T>
struct range_set {
 private:
    const T TINF = std::numeric_limits<T>::max() / 2; // 番兵（無限大）
    T sum; // 現在の全区間の長さの合計
    std::set<std::pair<T, T>> st; // 区間集合 [l, r) を保存

 public:
    range_set() : sum(0) {
        // 番兵を両端に設置（探索を楽にする）
        st.emplace(-TINF, -TINF);
        st.emplace(TINF, TINF);
    }

    // 区間 [l, r) がすでにカバーされているか判定
    bool covered(const T l, const T r) {
        assert(l <= r);
        if (l == r) return true; // 空区間は常にtrue
        auto itr = prev(st.upper_bound({l, TINF}));
        return itr->first <= l && r <= itr->second;
    }

    // 要素 x がカバーされているか判定
    bool covered(const T x) { return covered(x, x + 1); }

    // [l, r) を含む区間が存在する場合、それを返す。なければ[-TINF, -TINF]
    pair<T, T> covered_by(const T l, const T r) {
        assert(l <= r);
        if (l == r) return {-TINF, -TINF};
        auto itr = prev(st.upper_bound({l, TINF}));
        if (itr->first <= l && r <= itr->second) return *itr;
        return {-TINF, -TINF};
    }

    pair<T, T> covered_by(const T x) { return covered_by(x, x + 1); }

    // 区間 [l, r) を追加（必要に応じてマージ）、追加された長さを返す
    T insert(T l, T r) {
        assert(l <= r);
        if (l == r) return 0;

        auto itr = prev(st.upper_bound({l, TINF}));
        if (itr->first <= l && r <= itr->second) return 0; // 既にカバー済み

        T sum_erased = 0;

        // 左に接している or 食い込んでる区間の処理
        if (itr->first <= l && l <= itr->second) {
            l = itr->first;
            sum_erased += itr->second - itr->first;
            itr = st.erase(itr);
        } else {
            itr = next(itr);
        }

        // 完全に中にある区間を削除
        while (r > itr->second) {
            sum_erased += itr->second - itr->first;
            itr = st.erase(itr);
        }

        // 右端に重なっている区間を処理
        if (itr->first <= r) {
            sum_erased += itr->second - itr->first;
            r = itr->second;
            st.erase(itr);
        }

        st.emplace(l, r);
        sum += r - l - sum_erased;
        return r - l - sum_erased;
    }

    T insert(const T x) { return insert(x, x + 1); }

    // 区間 [l, r) を削除。削除された長さを返す
    T erase(const T l, const T r) {
        assert(l <= r);
        if (l == r) return 0;

        auto itr = prev(st.upper_bound({l, TINF}));

        // 完全に含まれる区間なら分割
        if (itr->first <= l && r <= itr->second) {
            if (itr->first < l) st.emplace(itr->first, l);
            if (r < itr->second) st.emplace(r, itr->second);
            st.erase(itr);
            sum -= r - l;
            return r - l;
        }

        T ret = 0;
        if (itr->first <= l && l < itr->second) {
            ret += itr->second - l;
            if (itr->first < l) st.emplace(itr->first, l);
            itr = st.erase(itr);
        } else {
            itr = next(itr);
        }

        while (itr->second <= r) {
            ret += itr->second - itr->first;
            itr = st.erase(itr);
        }

        if (itr->first < r) {
            ret += r - itr->first;
            st.emplace(r, itr->second);
            st.erase(itr);
        }

        sum -= ret;
        return ret;
    }

    T erase(const T x) { return erase(x, x + 1); }

    // 区間の数（番兵除く）
    int size() const { return (int)st.size() - 2; }

    // mex: x 以上で A に含まれない最小の非負整数
    T mex(const T x = 0) const {
        auto itr = prev(st.upper_bound({x, TINF}));
        if (itr->first <= x && x < itr->second)
            return itr->second;
        else
            return x;
    }

    T sum_all() const { return sum; }

    // 現在の区間をすべて取得（番兵は除く）
    set<pair<T, T>> get() const {
        set<pair<T, T>> res;
        for (auto &p : st) {
            if (abs(p.first) == TINF) continue;
            res.emplace(p.first, p.second);
        }
        return res;
    }

    void dump() const {
        cout << "range_set:";
        for (auto &p : st) {
            if (abs(p.first) == TINF) continue;
            cout << "[" << p.first << "," << p.second << "),";
        }
        cout << '\n';
    }
};
