template<typename T>
T gcd(T a, T b) {
    while (b) {
        T tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}
