int sz[SIZE];
int p[SIZE];

void init() {
	for (int i = 0; i < NMAX; i++) {
		p[i] = i;
		sz[i] = 1;
	}
}

int get(int v) // получение лидера множества
{
	if (p[v] != v)
		p[v] = get(p[v]);
	return p[v];
}

void union_sets(int a, int b) // слияние двух множеств o_O
{
	a = get(a);
	b = get(b);

	if (a == b) return;

	if (sz[a] > sz[b]) // a < b
		swap(a, b);

	p[a] = b;
	sz[b] += sz[a];
}
