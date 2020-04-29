struct Mo {
    const int width;
    vector<int> ls, rs, ord;
    Mo(int n) : width((int)sqrt(n)) {}

    inline void insert(int l, int r) {
        ls.emplace_back(l);
        rs.emplace_back(r);
    }

    inline void build() {
        ord.resize(ls.size());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](const int a, const int b) {
            int ablock = ls[a] / width, bblock = ls[b] / width;
            if (ablock != bblock) return ablock < bblock;
            return ablock & 1 ? rs[a] < rs[b] : rs[a] > rs[b];
        });
    }

    // void add(int idx): idx番目の要素を追加
    // void del(int idx): idx番目の要素を削除
    // void calc(int idx); クエリidxを処理
    template<class Add, class Del, class Calc>
    inline void run(const Add& add, const Del& del, const Calc& calc) {
        int nl = 0, nr = 0;
        for (const int idx : ord) {
            while (nl > ls[idx]) add(--nl);
            while (nr < rs[idx]) add(nr++);
            while (nl < ls[idx]) del(nl++);
            while (nr > rs[idx]) del(--nr);
            calc(idx);
        }
    }
};
