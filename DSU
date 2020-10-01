int sz[SIZE];
int p[SIZE];

int get(int v)
{
	if (p[v] != v)
		p[v] = get(p[v]);
	return p[v];
}

void union_sets(int a, int b)
{
	a = get(a);
	b = get(b);

	if (a == b) return;

	if (sz[a] > sz[b]) // a < b
		swap(a, b);

	p[a] = b;
	sz[b] += sz[a];
}
