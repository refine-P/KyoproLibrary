//1-indexであることに注意
template <typename T>
struct BIT {
    int n;
    vector<T> data;

    BIT(int n) : n(n), data(n + 1, 0) {}

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
};
