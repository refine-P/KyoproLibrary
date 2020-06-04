// [Related]: monoid
template <class Monoid>
struct SegmentTree {
    using T = typename Monoid::T;

    int n;
    vector<T> data;

    SegmentTree() {}
    
    SegmentTree(int size, T initial_value = Monoid::unit()) {
        n = 1;
        while (n < size) n <<= 1;
        data.assign(2 * n - 1, initial_value);

        if (initial_value != Monoid::unit()) {
            for (int i = n - 2; i >= 0; i--) data[i] = Monoid::merge(data[i * 2 + 1], data[i * 2 + 2]);
        }
    }

    SegmentTree(const vector<T>& v) {
        int size = v.size();
        n = 1;
        while (n < size) n <<= 1;
        data.assign(2 * n - 1, Monoid::unit());

        for (int i = 0; i < size; i++) data[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; i--) data[i] = Monoid::merge(data[i * 2 + 1], data[i * 2 + 2]);
    }

    T getLeaf(int k) {
        return data[k + n - 1];
    }

    void update(int k, T x) {
        k += n - 1; //葉の節点
        Monoid::update(data[k], x);
        while (k > 0) {
            k = (k - 1) / 2;
            data[k] = Monoid::merge(data[k * 2 + 1], data[k * 2 + 2]);
        }
    }

    //区間[a, b)に対するクエリに答える
    //k:節点番号, [l, r):節点に対応する区間
    T query(int a, int b, int k, int l, int r) {
        //[a, b)と[l, r)が交差しない場合
        if (r <= a || b <= l) return Monoid::unit();
        //[a, b)が[l, r)を含む場合、節点の値
        if (a <= l && r <= b) return data[k];
        else {
            //二つの子をマージ
            T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return Monoid::merge(vl, vr);
        }
    }

    //外から呼ぶ用
    T query(int a, int b) {
        return query(a, b, 0, 0, n);
    }

    //非再帰版: バグってるかもしれないので定数倍高速化する時以外使わないで
    //区間[a, b)に対するクエリに答える
    T query_fast(int a, int b) {
        T vl = Monoid::unit(), vr = Monoid::unit();
        for (int l = a + n, r = b + n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) vl = Monoid::merge(vl, data[l++ - 1]);
            if (r & 1) vr = Monoid::merge(data[--r - 1], vr);
        }
        return Monoid::merge(vl, vr);
    }
};
