template <class MonoidOp>
struct LazySegmentTree {
    using Tm = typename MonoidOp::Tm;
    using To = typename MonoidOp::To;

    int n;
    vector<Tm> data;
    vector<To> lazy;

    LazySegmentTree() {}

    LazySegmentTree(int size, Tm initial_data_value = MonoidOp::unit()) {
        n = 1;
        while (n < size) n <<= 1;

        data.assign(2 * n - 1, initial_data_value);
        lazy.assign(2 * n - 1, MonoidOp::op_unit());

        if (initial_data_value != MonoidOp::unit()) {
            for (int i = n - 2; i >= 0; i--) data[i] = MonoidOp::merge(data[i * 2 + 1], data[i * 2 + 2]);
        }
    }

    LazySegmentTree(const vector<Tm>& v) {
        int size = v.size();
        n = 1;
        while (n < size) n <<= 1;
        data.assign(2 * n - 1, MonoidOp::unit());
        lazy.assign(2 * n - 1, MonoidOp::op_unit());

        for (int i = 0; i < size; i++) data[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; i--) data[i] = MonoidOp::merge(data[i * 2 + 1], data[i * 2 + 2]);
    }

    Tm getLeaf(int k) {
        return query(k, k + 1);
    }

    void push(int k, int l, int r) {
        if (lazy[k] == MonoidOp::op_unit()) return;
        MonoidOp::apply(data[k], lazy[k], r - l);
        if (r - l > 1) {
            MonoidOp::update(lazy[2 * k + 1], lazy[k]);
            MonoidOp::update(lazy[2 * k + 2], lazy[k]);
        }
        lazy[k] = MonoidOp::op_unit();
    }

    //区間[a, b)に対する更新
    //k:節点番号, [l, r):節点に対応する区間
    void update(int a, int b, To x, int k, int l, int r) {
        push(k, l, r);
        //[a, b)と[l, r)が交差しない場合
        if (r <= a || b <= l) return;
        //[a, b)が[l, r)を含む場合、節点の値
        if (a <= l && r <= b) {
            MonoidOp::update(lazy[k], x);
            push(k, l, r);
        } else {
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);
            data[k] = MonoidOp::merge(data[2 * k + 1], data[2 * k + 2]);
        }
    }

    void update(int a, int b, To x) {
        update(a, b, x, 0, 0, n);
    }

    //区間[a, b)に対するクエリに答える
    //k:節点番号, [l, r):節点に対応する区間
    Tm query(int a, int b, int k, int l, int r) {
        push(k, l, r);
        //[a, b)と[l, r)が交差しない場合
        if (r <= a || b <= l) return MonoidOp::unit();
        //[a, b)が[l, r)を含む場合、節点の値
        if (a <= l && r <= b) return data[k];
        else {
            //二つの子をマージ
            Tm vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            Tm vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return MonoidOp::merge(vl, vr);
        }
    }

    //外から呼ぶ用
    Tm query(int a, int b) {
        return query(a, b, 0, 0, n);
    }
};

// 以下、MonoidOpの例
template<class U = ll, class V = U>
struct RangeSumAdd {
    using Tm = U;
    using To = V;
    static Tm merge(Tm x, Tm y) { return x + y; }
    static void update(To& target, To x) { target += x; }
    static void apply(Tm& target, To x, int seg_len) { target += x * seg_len; }
    static constexpr Tm unit() { return Tm(0); }
    static constexpr To op_unit() { return To(0); }
};

// 作用素の単位元は更新クエリで与えられる値の定義域の範囲外の値にする
template<class U = ll, class V = U>
struct RangeMinUpdate {
    using Tm = U;
    using To = V;
    static Tm merge(Tm x, Tm y) { return min(x, y); }
    static void update(To& target, To x) { target = x; }
    static void apply(Tm& target, To x, int seg_len) { target = x; }
    static constexpr Tm unit() { return numeric_limits<Tm>::max(); }
    static constexpr To op_unit() { return numeric_limits<To>::max(); }
};

// 作用素の単位元は更新クエリで与えられる値の定義域の範囲外の値にする
template<class U = ll, class V = U>
struct RangeSumUpdate {
    using Tm = U;
    using To = V;
    static Tm merge(Tm x, Tm y) { return x + y; }
    static void update(To& target, To x) { target = x; }
    static void apply(Tm& target, To x, int seg_len) { target = x * seg_len; }
    static constexpr Tm unit() { return Tm(0); }
    static constexpr To op_unit() { return numeric_limits<To>::min(); }
};

// 初期値 != 単位元 の場合に注意
template<class U = ll, class V = U>
struct RangeMinAdd {
    using Tm = U;
    using To = V;
    static Tm merge(Tm x, Tm y) { return min(x, y); }
    static void update(To& target, To x) { target += x; }
    static void apply(Tm& target, To x, int seg_len) { target += x; }
    static constexpr Tm unit() { return numeric_limits<Tm>::max(); }
    static constexpr To op_unit() { return To(0); }
};
