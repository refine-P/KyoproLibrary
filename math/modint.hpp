// https://noshi91.hatenablog.com/entry/2019/03/31/174006
template <std::uint_fast64_t Modulus> 
struct ModInt {
    using u64 = std::uint_fast64_t;

    static constexpr u64 MOD = Modulus;

    u64 val;

    constexpr ModInt(const u64 x = 0) noexcept : val(x % MOD) {}

    constexpr ModInt operator+() const noexcept { return ModInt(*this); }
    constexpr ModInt operator-() const noexcept {
        ModInt res(*this);
        if (res.val != 0) res.val = MOD - res.val;
        return res;
    }

    // prefix increment/decrement
    constexpr ModInt& operator++() noexcept { return *this += ModInt(1); }
    constexpr ModInt& operator--() noexcept { return *this -= ModInt(1); }
    
    // postfix increment/decrement
    constexpr ModInt& operator++(int) noexcept {
        ModInt tmp(*this);
        ++*this;
        return tmp; 
    }
    constexpr ModInt& operator--(int) noexcept {
        ModInt tmp(*this);
        --*this;
        return tmp;
    }

    constexpr ModInt operator+(const ModInt& rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    constexpr ModInt operator-(const ModInt& rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    constexpr ModInt operator*(const ModInt& rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    constexpr ModInt operator/(const ModInt& rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {
        val += rhs.val;
        if (val >= Modulus) val -= MOD;
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {
        if (val < rhs.val) val += MOD;
        val -= rhs.val;
        return *this;
    }
    constexpr ModInt& operator*=(const ModInt& rhs) noexcept {
        val = val * rhs.val % MOD;
        return *this;
    }

    // prime Modulus only
    constexpr ModInt& operator/=(const ModInt& rhs) noexcept {
        return *this *= rhs.inv();
    }

    // prime Modulus only
    constexpr ModInt inv() const noexcept {
        return pow(*this, MOD - 2);
    }
};

template<std::uint_fast64_t Modulus>
constexpr ModInt<Modulus> pow(ModInt<Modulus> x, std::uint_fast64_t n) {
    ModInt<Modulus> res(1);
    while (n) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

template<std::uint_fast64_t Modulus>
istream& operator>>(istream& is, ModInt<Modulus>& x) {
    std::uint_fast64_t val;
    is >> val;
    x = ModInt<Modulus>(val);
    return is;
}

template<std::uint_fast64_t Modulus>
ostream& operator<<(ostream& os, const ModInt<Modulus>& x) {
    return os << x.val;
}

using mint = ModInt<1000000007>;
