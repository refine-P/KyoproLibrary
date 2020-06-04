template <class U = ll>
struct RMQSL {
    using T = U;
    static T merge(const T& a, const T& b) { return min(a, b); }
};
