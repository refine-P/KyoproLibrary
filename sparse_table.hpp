template <typename T>
struct SparseTable {
    int n;
    vector< vector<T> > table;
    vector<int> log_table;

    //使うときは、この2つを適宜変更する
    static T merge(T x, T y);
    static T INITIAL_VALUE;

    SparseTable(const vector<T>& v) {
        n = v.size();

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
                table[i][j] = merge(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    //区間[l, r)に対するクエリに答える
    T query(int l, int r) {
        if (l == r) return INITIAL_VALUE;
        int k = log_table[r - l];
        return merge(table[k][l], table[k][r - (1 << k)]);
    }
};

//使うときは以下2つを変更
//非可換の場合は順序に注意！！！
template <typename T>
T SparseTable<T>::merge(T x, T y) {
    return max(x, y);
}

//本来は必要無いはずだけど、区間幅0のときにバグるので一応単位元を用意
//(区間幅0のときは例外処理した方が良い？)
template <typename T>
T SparseTable<T>::INITIAL_VALUE = 0;
