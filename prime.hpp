template<typename T>
bool is_prime(T n) {
    if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (T i = 3; i * i <= n; i += 2) {
		if (n % i == 0) return false;
	}
	return n != 1;
}

template<typename T>
vector<T> divisor(T n) {
	vector<T> res;
	for (T i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			res.emplace_back(i);
			if (i != n / i) res.emplace_back(n / i);
		}
	}
	return res;
}

template<typename T>
map<T, int> prime_factor(T n) {
	map<T, int> res;
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			++res[i];
			n /= i;
		}
	}
	if (n != 1) res[n] = 1;
	return res;
}

template<typename T>
vector<T> sieve(T n) {
	vector<T> res;
	vector<bool> is_prime(n + 1, true);
	is_prime[0] = false;
	is_prime[1] = false;
	for (T i = 2; i <= n; i++) {
		if (!is_prime[i]) continue;
		res.emplace_back(i);
		for (T j = 2 * i; j <= n; j += i) is_prime[j] = false;
	}
	return res;
}
