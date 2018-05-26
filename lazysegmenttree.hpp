template <typename T>
struct LazySegmentTree {
    int n;
    vector<T> data;
    vector<T> lazy;
    T INITIAL_DATA_VALUE;
    T INITIAL_LAZY_VALUE;

    //使うときは、この3つを適宜変更する
    static T merge(T x, T y);
    void updateNode(int k, T x);
    void apply(int k, int seg_len);

    void init(int size, T initial_data_value, T initial_lazy_value) {
        n = 1;
        INITIAL_DATA_VALUE = initial_data_value;
        INITIAL_LAZY_VALUE = initial_lazy_value;
        while (n < size) n *= 2;
        data.resize(2 * n - 1, INITIAL_DATA_VALUE);
        lazy.resize(2 * n - 1, INITIAL_LAZY_VALUE);
    }

    LazySegmentTree(int size, T initial_data_value, T initial_lazy_value) {
        init(size, initial_data_value, initial_lazy_value);
    }

    LazySegmentTree(int size, T initial_value) {
        init(size, initial_value, initial_value);
    }

    T getLeaf(int k) {
        return data[k + n - 1];
    }

    void eval(int k, int l, int r) {
        if (lazy[k] == INITIAL_LAZY_VALUE) return;
        apply(k, r - l);
        if (r - l > 1) {
            updateNode(2 * k + 1, lazy[k]);
            updateNode(2 * k + 2, lazy[k]);
        }
        lazy[k] = INITIAL_LAZY_VALUE;
    }

    //区間[a, b)に対する更新
    //k:節点番号, [l, r):節点に対応する区間
    void update(int a, int b, T x, int k, int l, int r) {
        eval(k, l, r);
        //[a, b)と[l, r)が交差しない場合
        if (r <= a || b <= l) return;
        //[a, b)が[l, r)を含む場合、節点の値
        if (a <= l && r <= b) {
            updateNode(k, x);
            eval(k, l, r);
        } else {
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);
            data[k] = merge(data[2 * k + 1], data[2 * k + 2]);
        }
    }

    void update(int a, int b, T x) {
        update(a, b, x, 0, 0, n);
    }

    //区間[a, b)に対するクエリに答える
    //k:節点番号, [l, r):節点に対応する区間
    T query(int a, int b, int k, int l, int r) {
        eval(k, l, r);
        //[a, b)と[l, r)が交差しない場合
        if (r <= a || b <= l) return INITIAL_DATA_VALUE;
        //[a, b)が[l, r)を含む場合、節点の値
        if (a <= l && r <= b) return data[k];
        else {
            //二つの子をマージ
            T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return merge(vl, vr);
        }
    }

    //外から呼ぶ用
    T query(int a, int b) {
        return query(a, b, 0, 0, n);
    }
};

//使うときは以下3つを変更
template <typename T>
T LazySegmentTree<T>::merge(T x, T y) {
    return x + y;
}

template <typename T>
void LazySegmentTree<T>::updateNode(int k, T x) {
    lazy[k] += x;
}

template <typename T>
void LazySegmentTree<T>::apply(int k, int seg_len) {
    data[k] += lazy[k] * seg_len;
}
