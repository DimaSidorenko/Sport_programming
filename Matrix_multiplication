long long mul(long long a, long long n)
{
	long long ans;
	if (n == 0)
		return 0;
	if (n % 2 == 0) {
		ll res = mul(a, n / 2);
		return (res + res) % MOD;
	}
	else {
		return (mul(a, n - 1) + a) % MOD;
	}
}


vec<vec<ll>> mult(vec<vec<ll>>& A, vec<vec<ll>>& B) {
	vec<vec<ll>> C(A.size(), vec<ll>(B[0].size(), 0));
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < B[0].size(); j++) {
			for (int k = 0; k < A[i].size(); k++) {
				C[i][j] += mul(A[i][k], B[k][j]);
				C[i][j] %= MOD;
			}
		}
	}
	return C;
}


vec<vec<ll>> BinPow(vec<vec<ll>>& A, ll n) {
	if (n == 1)
		return A;
	if (n % 2 == 0) {
		vec<vec<ll>> A1 = BinPow(A, n / 2);
		return mult(A1, A1);
	}
	else {
		vec<vec<ll>> val = BinPow(A, n - 1);
		return mult(A, val);
	}
}
