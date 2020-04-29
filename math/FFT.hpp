// https://www.creativ.xyz/fast-fourier-transform/
namespace FFT {
    using Real = double;
    constexpr Real PI = 3.14159265358979323846;

    struct Complex {
        Real x, y;

        Complex() : x(0), y(0) {}
        Complex(Real x, Real y = 0) : x(x), y(y) {}
        inline Complex operator~() const { return Complex(x, -y); }
        inline Complex operator+(const Complex& c) const { return Complex(x + c.x, y + c.y); }
        inline Complex operator-(const Complex& c) const { return Complex(x - c.x, y - c.y); }
        inline Complex operator*(const Complex& c) const { return Complex(x * c.x - y * c.y, x * c.y + y * c.x); }
        inline Complex operator/(const Real& r) const { return Complex(x / r, y / r); }
    };

    // https://ei1333.github.io/luzhiled/snippets/math/fast-fourier-transform.html
    int base = 1;
    vector<Complex> w = {{0, 0}, {1, 0}};
    vector<int> rev = {0, 1};

    void ensure_base(int nbase) {
        if (nbase <= base) return;
        w.resize(1 << nbase);
        rev.resize(1 << nbase);

        for(int i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }

        for (; base < nbase; ++base) {
            Real theta = PI / (1 << base);
            Complex zeta(cos(theta), sin(theta));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                w[i << 1] = w[i];
                w[(i << 1) + 1] = w[i] * zeta;
            }
        }
    }

    template<bool inverse = false>
    vector<Complex> fft(vector<Complex>& a) {
        int n = a.size();
        assert((n & (n - 1)) == 0); // nは2べき

        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
        }

        for (int b = 1; b < n; b <<= 1) {
            for (int k = 0; k < n; k += (b << 1)) {
                for (int j = 0; j < b; j++) {
                    Complex s = a[j + k];
                    Complex t = a[j + k + b] * (inverse ? ~w[j + b] : w[j + b]);
                    a[j + k] = s + t;
                    a[j + k + b] = s - t;
                }
            }
        }

        if (inverse) for (int i = 0; i < n; i++) a[i] = a[i] / n;
        return a;
    }

    // https://lumakernel.github.io/ecasdqina/math/FFT/standard
    vector<ll> conv(const vector<int>& a, const vector<int>& b) {
        if (a.empty() || b.empty()) return {};
        int n = a.size() + b.size() - 1;
        int n2 = 1;
        while (n2 < n) n2 <<= 1;

        ensure_base(__builtin_ctz(n2));

        vector<Complex> A(n2);
        for (int i = 0; i < a.size(); i++) A[i].x = a[i];
        for (int i = 0; i < b.size(); i++) A[i].y = b[i];
        fft(A);

        const Complex COEF(0, -0.25);
        vector<Complex> C(n2);
        C[0] = (A[0] + ~A[0]) * (A[0] - ~A[0]) * COEF;
        for (int i = 1; i <= (n2 >> 1); i++) {
            int j = n2 - i;
            C[i] = (A[i] + ~A[j]) * (A[i] - ~A[j]) * COEF;
            C[j] = ~C[i];
        }
        fft<true>(C);

        vector<ll> res(n);
        for (int i = 0; i < n; i++) res[i] = llround(C[i].x);
        return res;
    }
}
