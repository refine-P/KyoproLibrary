//1-indexであることに注意
template <typename T>
struct BIT {
    int n;
    vector<T> data;
    int n_msb;

    BIT(int n) : n(n), data(n + 1, 0) {
        n_msb = 1;
        while (n_msb <= n) n_msb <<= 1;
        n_msb >>= 1;
    }

    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += data[i];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, T x) {
        while (i <= n) {
            data[i] += x;
            i += i & -i;
        }
    }

    // sum(i) >= val となる最小のiを返す
    // ただし、sum(i)は広義単調増加すると仮定
    int lower_bound(T val) {
        if (val <= 0) return 0;

        int res = 0;
        for (int k = n_msb; k > 0; k >>= 1) {
            if (res + k <= n && data[res + k] < val) {
                val -= data[res + k];
                res += k;
            }
        }
        return res + 1;
    }
};
