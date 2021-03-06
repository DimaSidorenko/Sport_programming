//не забудь вызвать calc_fact() в мейн функции
ll fact[NMAX];
const ll MOD = 1e9 + 9;
const int NMAX = 2e5 + 17;

void calc_fact() {
	fact[0] = 1;
	for (int i = 1; i < NMAX; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
}

long long binpow(long long a, long long n) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return (binpow(a, n - 1) * a) % MOD;
	else {
		long long b = binpow(a, n / 2) % MOD;
		return (b * b) % MOD;
	}
}

ll C(ll n, ll k) {
	if (n < k)
		return 0;
	return fact[n] * binpow(fact[k], MOD - 2) % MOD * binpow(fact[n - k], MOD - 2) % MOD;
}

