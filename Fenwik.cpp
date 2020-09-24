void inc(int i1, int j1, int change = 1) {
	for (int i = i1; i < n; i = i | (i + 1))
		for (int j = j1; j < n; j = j | (j + 1)) {
			t[i][j] += change;
		}
}

ll prefix(int i1, int j1) {
	ll res = 0;
	for (int i = i1; i >= 0; i = (i & (i + 1)) - 1)
		for (int j = j1; j >= 0; j = (j & (j + 1)) - 1)
				res += t[i][j];
	return res;
}

ll prefix(int i1, int j1, int i2, int j2) {
	return prefix(i2, j2) - prefix(i1, j1);
}
