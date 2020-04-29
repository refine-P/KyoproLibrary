using ull = unsigned long long;

template<ull mod = 1000000007>
struct RollingHash {
	vector<ull> hashs, power;

	RollingHash() {}
	RollingHash(const string& s, ull base = 10007) {
		int sz = s.size();
		hashs.assign(sz + 1, 0);
		power.assign(sz + 1, 0);
		power[0] = 1;

		for (int i = 0; i < sz; i++) {
			power[i + 1] = power[i] * base % mod;
			hashs[i + 1] = (hashs[i] * base) % mod + s[i];
			if (hashs[i + 1] >= mod) hashs[i] -= mod;
		}
	}

	ull get(int l, int r) const {
		ull res = hashs[r] + mod - hashs[l] * power[r - l] % mod;
		if (res >= mod) res -= mod;
		return res;
	}
};
