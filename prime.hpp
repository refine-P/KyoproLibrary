bool is_prime(int n) {
	if (n % 2 == 0) return false;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) return false;
	}
	return n != 1;
}

vector<int> divisor(int n) {
	vector<int> res;
	for (int i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			res.emplace_back(i);
			if (i != n / i) res.emplace_back(n / i);
		}
	}
	return res;
}

map<int, int> prime_factor(int n) {
	map<int, int> res;
	for (int i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			++res[i];
			n /= i;
		}
	}
	if (n != 1) res[n] = 1;
	return res;
}

vector<int> sieve(int n) {
	vector<int> res;
	vector<bool> is_prime(n + 1, true);
	is_prime[0] = false;
	is_prime[1] = false;
	for (int i = 2; i <= n; i++) {
		if (!is_prime[i]) continue;
		res.emplace_back(i);
		for (int j = 2 * i; j <= n; j += i) is_prime[j] = false;
	}
	return res;
}
