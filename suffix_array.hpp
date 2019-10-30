struct SuffixArray {
    string str;
    vector<int> sa;
    vector<int> rank; // saの逆関数に相当

    SuffixArray() {}
    SuffixArray(const string& s) : str(s) {
        constructSA();
    }

    // O(N (log N)^2)
    void constructSA() {
        if (str.empty()) return;

        int n = str.size();

        sa.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            sa[i] = i;
            rank[i] = (i < n ? str[i] : -1);
        }

        int len;
        auto compare_sa = [&](const int i, const int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            else {
                int ri = (i + len <= n ? rank[i + len] : -1);
                int rj = (j + len <= n ? rank[j + len] : -1);
                return ri < rj;
            }
        };

        vector<int> tmp(n + 1);
        for (len = 1; len <= n; len <<= 1) {
            sort(sa.begin(), sa.end(), compare_sa);

            tmp[sa[0]] = 0;
            for (int i = 1; i <= n; i++) {
                tmp[sa[i]] = tmp[sa[i - 1]] + compare_sa(sa[i - 1], sa[i]);
            }
            rank.swap(tmp);
        }
    }

    int operator[](int idx) const {
        return sa[idx];
    }

    // 文字列s以上となる最小の接尾辞について、SAのindexを返す（無いならsa.size()を返す）
    int lower_bound(const string& s) const {
        int ng = -1, ok = sa.size();
        while (ok - ng > 1) {
            int mid = (ok + ng) >> 1;
            (str.compare(sa[mid], s.size(), s) < 0 ? ng : ok) = mid;
        }
        return ok;
    }

    // 文字列sが文字列strに含まれるならSAのindexを、無いなら-1を返す
    int find(const string& s) const {
        int idx = lower_bound(s);
        return ((idx < sa.size() && str.compare(sa[idx], s.size(), s) == 0) ? idx : -1);
    }

    // 文字列sが文字列strに含まれるか？
    bool contain(const string& s) const {
        return find(s) != -1;
    }
};
