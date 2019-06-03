template <typename T>
struct SegmentTree {
    int n;
    vector<T> data;
    T INITIAL_VALUE;

    //使うときは、この2つを適宜変更する
    static T merge(T x, T y);
    void updateNode(int k, T x);

    SegmentTree(int size, T initial_value) {
        n = 1;
        INITIAL_VALUE = initial_value;
        while (n < size) n *= 2;
        data.resize(2 * n - 1, INITIAL_VALUE);
    }

    SegmentTree(const vector<T>& v, T initial_value) {
        int size = v.size();
        n = 1;
        INITIAL_VALUE = initial_value;
        while (n < size) n *= 2;
        data.resize(2 * n - 1, INITIAL_VALUE);

        for (int i = 0; i < size; i++) data[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; i--) data[i] = merge(data[i * 2 + 1], data[i * 2 + 2]);
    }

    T getLeaf(int k) {
        return data[k + n - 1];
    }

    void update(int k, T x) {
        k += n - 1; //葉の節点
        updateNode(k, x);
        while (k > 0) {
            k = (k - 1) / 2;
            data[k] = merge(data[k * 2 + 1], data[k * 2 + 2]);
        }
    }

    //区間[a, b)に対するクエリに答える
    //k:節点番号, [l, r):節点に対応する区間
    T query(int a, int b, int k, int l, int r) {
        //[a, b)と[l, r)が交差しない場合
        if (r <= a || b <= l) return INITIAL_VALUE;
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

    //非再帰版: バグってるかもしれないので定数倍高速化する時以外使わないで
    //区間[a, b)に対するクエリに答える
    T query_fast(int a, int b) {
        T vl = INITIAL_VALUE, vr = INITIAL_VALUE;
        for (int l = a + n, r = b + n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) vl = merge(vl, data[l++ - 1]);
            if (r & 1) vr = merge(data[--r - 1], vr);
        }
        return merge(vl, vr);
    }
};

//使うときは以下2つを変更
//非可換の場合は順序に注意！！！
template <typename T>
T SegmentTree<T>::merge(T x, T y) {
    return min(x, y);
}

template <typename T>
void SegmentTree<T>::updateNode(int k, T x) {
    data[k] = x;
}
