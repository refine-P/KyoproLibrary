// verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D&lang=ja
// verify: https://atcoder.jp/contests/abc141/tasks/abc141_e
// verify: https://atcoder.jp/contests/arc055/tasks/arc055_c
// verify: https://www.hackerrank.com/contests/yfkpo2/challenges/fuzzy-search-queries/problem
struct SuffixArray {
    string str;
    vector<int> sa;
    vector<int> rank; // saの逆関数に相当
 
    SuffixArray() {}
 
    SuffixArray(const string& s) : str(s) {
        constructSA();
        // constructSA_fast();
    }
 
    // O(N (log N)^2)
    void constructSA() {
        if (str.empty()) return;
 
        int n = str.size();
        sa.resize(n, 0);
        rank.resize(n, 0);
 
        if (n == 1) return;
 
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = str[i];
        }
 
        int len;
        auto compare_sa = [&](const int i, const int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            else {
                int ri = (i + len < n ? rank[i + len] : -1);
                int rj = (j + len < n ? rank[j + len] : -1);
                return ri < rj;
            }
        };
 
        vector<int> tmp(n);
        for (len = 1; len < n; len <<= 1) {
            sort(sa.begin(), sa.end(), compare_sa);
 
            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                tmp[sa[i]] = tmp[sa[i - 1]] + compare_sa(sa[i - 1], sa[i]);
            }
            rank.swap(tmp);
        }
    }
 
    // O(N log N)
    // オレオレ実装なのでバグってるかも？（ゆえに非推奨）
    void constructSA_fast() {
        if (str.empty()) return;
 
        int n = str.size();
        sa.resize(n, 0);
        rank.resize(n, 0);
 
        if (n == 1) return;
 
        // 長さ1のソート
        constexpr int CHAR_NUM = 256;
        vector<int> cnt(max(n, CHAR_NUM), 0);
 
        // とりあえずカウントソート
        for (int i = 0; i < n; i++) {
            cnt[str[i]]++;
        }
 
        for (int i = 1; i < CHAR_NUM; i++) {
            cnt[i] += cnt[i - 1];
        }
 
        // iが大きい方が辞書順で小さくなる可能性が高い？
        for (int i = 0; i < n; i++) {
            sa[--cnt[str[i]]] = i;
        }
 
        rank[sa[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (str[sa[i]] != str[sa[i - 1]]) classes++;
            rank[sa[i]] = classes - 1;
        }
 
        // 長さlen*2のソート
        int len;
        auto equal_class = [&](const int i, const int j) {
            if (rank[i] != rank[j]) return false;
            else {
                int ri = (i + len < n ? rank[i + len] : -1);
                int rj = (j + len < n ? rank[j + len] : -1);
                return ri == rj;
            }
        };
 
        vector<int> tmp_sa(n), tmp_rank(n);
        for (len = 1; len < n; len <<= 1) {
            // とりあえずカウントソート
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++) {
                cnt[rank[sa[i]]]++;
            }
 
            for (int i = 1; i < classes; i++) {
                cnt[i] += cnt[i - 1];
            }
 
            // SAの計算（ここが一番バグってそう）
            // 基本的なお気持ちはそすうささんの記事を読んで
            // http://wk1080id.hatenablog.com/entry/2018/12/25/005926
            for (int i = n - 1; i >= 0; i--) {
                // suffixの長さがlen以下の場合、ソートしても場所は変化しない
                if (sa[i] + len >= n) tmp_sa[i] = sa[i];
 
                // 場所が変化しないやつを除いて、お気持ちに従いソート
                if (sa[i] >= len) {
                    int s1 = sa[i] - len;
                    tmp_sa[--cnt[rank[s1]]] = s1;
                }
            }
            sa.swap(tmp_sa);
 
            tmp_rank[sa[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                if (!equal_class(sa[i-1], sa[i])) classes++;
                tmp_rank[sa[i]] = classes - 1;
            }
            rank.swap(tmp_rank);
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
