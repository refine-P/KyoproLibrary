template <class SemiLattice>
struct SparseTable {
    using T = typename SemiLattice::T;

    int n;
    vector< vector<T> > table;
    vector<int> log_table;

    SparseTable() {}
    SparseTable(const vector<T>& v) : n(v.size()) {
        log_table.resize(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            log_table[i] = log_table[i >> 1] + 1;
        }

        table.resize(log_table[n] + 1, vector<T>(n));
        for (int i = 0; i < n; i++) {
            table[0][i] = v[i];
        }

        size_t sz = table.size();
        for (int i = 1; i < sz; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                table[i][j] = SemiLattice::merge(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    //区間[l, r)に対するクエリに答える
    T query(int l, int r) {
        assert(l < r && r <= n);
        int k = log_table[r - l];
        return SemiLattice::merge(table[k][l], table[k][r - (1 << k)]);
    }
};

//以下、SemiLatticeの例
template <class U = ll>
struct RMQSL {
    using T = U;
    static T merge(T a, T b) { return min(a, b); }
};
