template<class U = ll, class V = U>
struct RangeSumAdd {
    using Tm = U;
    using To = V;
    static Tm merge(const Tm& x, const Tm& y) { return x + y; }
    static To op_merge(const To& x, const To& y) { return x + y; }
    static Tm apply(const Tm& vm, const To& vo, int seg_len) { return vm + vo * seg_len; }
    static constexpr Tm unit() { return Tm(0); }
    static constexpr To op_unit() { return To(0); }
};

// Tmが非算術型（ex. pair）のときの numeric_limits<Tm>::max() は Tm() なので注意
template<class U = ll, class V = U>
struct RangeMinUpdate {
    using Tm = U;
    using To = V;
    static Tm merge(const Tm& x, const Tm& y) { return min(x, y); }
    static To op_merge(const To& x, const To& y) { return y; }
    static Tm apply(const Tm& vm, const To& vo, int seg_len) { return vo == op_unit() ? vm : vo; }
    static constexpr Tm unit() { return numeric_limits<Tm>::max(); }
    static constexpr To op_unit() { return numeric_limits<To>::max(); }
};

// 作用素の初期値は更新クエリで与えられる値の定義域の範囲外の値にする
template<class U = ll, class V = U>
struct RangeSumUpdate {
    using Tm = U;
    using To = V;
    static Tm merge(const Tm& x, const Tm& y) { return x + y; }
    static To op_merge(const To& x, const To& y) { return y; }
    static Tm apply(const Tm& vm, const To& vo, int seg_len) { return vo == op_unit() ? vm : vo * seg_len; }
    static constexpr Tm unit() { return Tm(0); }
    static constexpr To op_unit() { return numeric_limits<To>::min(); }
};

// 初期値 != 単位元 の場合に注意
// Tmが非算術型（ex. pair）のときの numeric_limits<Tm>::max() は Tm() なので注意
template<class U = ll, class V = U>
struct RangeMinAdd {
    using Tm = U;
    using To = V;
    static Tm merge(const Tm& x, const Tm& y) { return min(x, y); }
    static To op_merge(const To& x, const To& y) { return x + y; }
    static Tm apply(const Tm& vm, const To& vo, int seg_len) { return vm + vo; }
    static constexpr Tm unit() { return numeric_limits<Tm>::max(); }
    static constexpr To op_unit() { return To(0); }
};
