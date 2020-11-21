ll t[NMAX];

void inc(int i1, int change = 1) {
	for (int i = i1; i < NMAX; i = i | (i + 1)) {
		t[i] += change;
	}
}

ll prefix(int i1) {
	ll res = 0;
	for (int i = i1; i >= 0; i = (i & (i + 1)) - 1) {
		res += t[i];
	}
	return res;
}

//возвращает prefix (i1, i2]
ll prefix(int i1, int i2) {
	return prefix(i2) - prefix(i1);
}
