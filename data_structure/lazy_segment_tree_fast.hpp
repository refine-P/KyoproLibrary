// [Related]: monoid_op
// 参考: http://kazuma8128.hatenablog.com/entry/2017/12/29/081929
template <class MonoidOp>
struct LazySegmentTree {
    using Tm = typename MonoidOp::Tm;
    using To = typename MonoidOp::To;

    int n;
    int h;
    vector<Tm> data;
    vector<To> lazy;

    LazySegmentTree() {}
    
    LazySegmentTree(int size, Tm initial_data_value = MonoidOp::unit()) {
        n = 1;
        h = 0;
        while (n < size) {
            h++;
            n <<= 1;
        }

        data.assign((n << 1), initial_data_value);
        lazy.assign((n << 1), MonoidOp::op_unit());

        if (initial_data_value != MonoidOp::unit()) {
            for (int i = n - 1; i > 0; i--) data[i] = MonoidOp::merge(data[(i << 1)], data[(i << 1) + 1]);
        }
    }

    LazySegmentTree(const vector<Tm>& v) {
        int size = v.size();
        n = 1;
        h = 0;
        while (n < size) {
            h++;
            n <<= 1;
        }

        data.assign((n << 1), MonoidOp::unit());
        lazy.assign((n << 1), MonoidOp::op_unit());

        for (int i = 0; i < size; i++) data[i + n] = v[i];
        for (int i = n - 1; i > 0; i--) data[i] = MonoidOp::merge(data[(i << 1)], data[(i << 1) + 1]);
    }

    // https://komiyam.hatenadiary.org/entry/20131202/1385992406
    inline int getSegLen(int k) {
        return n / (1 << (31 - __builtin_clz(k)));
    }

    Tm getLeaf(int k) {
        return query(k, k + 1);
    }

    void push(int k) {
        if (lazy[k] == MonoidOp::op_unit()) return;
        int seg_len = getSegLen(k);
        data[k] = MonoidOp::apply(data[k], lazy[k], seg_len);
        if (seg_len > 1) {
            lazy[(k << 1)] = MonoidOp::op_merge(lazy[(k << 1)], lazy[k]);
            lazy[(k << 1) + 1] = MonoidOp::op_merge(lazy[(k << 1) + 1], lazy[k]);
        }
        lazy[k] = MonoidOp::op_unit();
    }

    void update(int k) {
        Tm vl = MonoidOp::apply(data[(k << 1)], lazy[(k << 1)], getSegLen(k << 1));
        Tm vr = MonoidOp::apply(data[(k << 1) + 1], lazy[(k << 1) + 1], getSegLen((k << 1) + 1));
        data[k] = MonoidOp::merge(vl, vr);
    }

    //区間[a, b)に対する更新
    void update(int a, int b, To x) {
        a += n, b += n - 1;
        for (int i = h; i > 0; i--) {
            push(a >> i);
            push(b >> i);
        }

        for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) lazy[l] = MonoidOp::op_merge(lazy[l], x), l++;
            if (r & 1) --r, lazy[r] = MonoidOp::op_merge(lazy[r], x);
        }

        while (a >>= 1, b >>= 1, a) {
            if (lazy[a] == MonoidOp::op_unit()) update(a);
            if (lazy[b] == MonoidOp::op_unit()) update(b);
        }
    }

    //区間[a, b)に対するクエリに答える
    Tm query(int a, int b) {
        a += n, b += n - 1;
        for (int i = h; i > 0; i--) {
            push(a >> i);
            push(b >> i);
        }

        Tm vl = MonoidOp::unit(), vr = MonoidOp::unit();
        for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                vl = MonoidOp::merge(vl, MonoidOp::apply(data[l], lazy[l], getSegLen(l)));
                l++;
            }

            if (r & 1) {
                --r;
                vr = MonoidOp::merge(MonoidOp::apply(data[r], lazy[r], getSegLen(r)), vr);
            }
        }
        return MonoidOp::merge(vl, vr);
    }
};
