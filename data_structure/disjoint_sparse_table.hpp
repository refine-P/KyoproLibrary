template <class SemiGroup>
struct DisjointSparseTable {
    using T = typename SemiGroup::T;

    int n;
    vector< vector<T> > table;
    vector<int> msb_table;

    DisjointSparseTable() {}
    DisjointSparseTable(const vector<T>& v) : n(v.size()) {
        table.emplace_back(v.begin(), v.end());

        for (int i = 1; (1 << i) < n; i++) {
            table.emplace_back(n);
            int shift = (1 << i);
            for (int j = 0; j < n; j += (shift << 1)) {
                int m = min(j + shift, n);
                table[i][m - 1] = v[m - 1];
                for (int k = m - 2; k >= j; --k) table[i][k] = SemiGroup::merge(v[k], table[i][k + 1]);

                if (m >= n) break;

                int r = min(m + shift, n);
                table[i][m] = v[m];
                for (int k = m + 1; k < r; ++k) table[i][k] = SemiGroup::merge(table[i][k - 1], v[k]);                
            }
        }
    }

    //区間[l, r)に対するクエリに答える
    T query(int l, int r) {
        assert(l < r && r <= n);

        if (l == --r) return table[0][l];
        int msb = 31 - __builtin_clz(l ^ r);
        return SemiGroup::merge(table[msb][l], table[msb][r]);
    }
};

//以下、SemiGroupの例
template <class U = ll>
struct RSQSG {
    using T = U;
    static T merge(T a, T b) { return a + b; }
};
