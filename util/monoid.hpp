template <class U = ll>
struct RangeMin {
    using T = U;
    static T merge(const T& x, const T& y) { return min(x, y); }
    static void update(T& target, const T& x) { target = x; }
    static constexpr T unit() { return numeric_limits<T>::max(); }
};

template <class U = ll>
struct RangeSum {
    using T = U;
    static T merge(const T& x, const T& y) { return x + y; }
    static void update(T& target, const T& x) { target += x; }
    static constexpr T unit() { return T(0); }
};
