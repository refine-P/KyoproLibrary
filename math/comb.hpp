// g++ -Wl,--stack,[STACK SIZE] [file] でスタックサイズを増やすか、
// グローバル変数として宣言して使うこと！！！
template<size_t MAXV, class T = mint>
struct Comb {
    array<T, MAXV + 1> fact, fact_inv;

    constexpr Comb() noexcept {
        fact[0] = 1;
        for (size_t i = 1; i <= MAXV; i++) {
            fact[i] = fact[i - 1] * i;
        }

        fact_inv[MAXV] = fact[MAXV].inv();
        for (size_t i = MAXV; i > 0; i--) {
            fact_inv[i - 1] = fact_inv[i] * i;
        }
    }

    constexpr T operator()(int n, int k) const noexcept {
        if (n < k || n < 0 || k < 0) return 0;
        return fact[n] * fact_inv[k] * fact_inv[n - k];
    }

    constexpr T perm(int n, int k) const noexcept {
        if (n < k || n < 0 || k < 0) return 0;
        return fact[n] * fact_inv[n - k];        
    }
};

const Comb<200000> comb;
