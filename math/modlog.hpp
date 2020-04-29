const ll MOD = 1000000007;

ll modpow(ll x, ll n, ll mod = MOD) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

// y * y >= x を満たす最小の整数yを求める
ll calcSquare(ll x) {
    ll ng = 0, ok = x;
    while (ok - ng > 1) {
        ll mid = (ng + ok) / 2;
        (mid * mid >= x ? ok : ng) = mid; 
    }
    return ok;
}

// g^x == y (mod p) の解xを求める（なければ-1を返す）
ll modlog(ll g, ll y, ll p = MOD) {
    g %= p;
    y %= p;

    if (g == 1 && y != 1) return -1;
    if (y == 1) return 0;

    ll sq = calcSquare(p);

    map<ll, ll> baby_table;
    for (ll i = 0, b = 1; i < sq; i++) {
        baby_table[b] = i;
        (b *= g) %= p;
    }

    ll inv_gsq = modpow(modpow(g, p - 2, p), sq, p);

    for (ll i = 0; i < sq; i++) {
        if (baby_table.find(y) != baby_table.end()) {
            return i * sq + baby_table[y];
        }
        (y *= inv_gsq) %= p;
    }
    return -1;
}
