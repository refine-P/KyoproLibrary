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
};

//使うときは以下2つを変更
template <typename T>
T SegmentTree<T>::merge(T x, T y) {
    return min(x, y);
}

template <typename T>
void SegmentTree<T>::updateNode(int k, T x) {
    data[k] = x;
}
