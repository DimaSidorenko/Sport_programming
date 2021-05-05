int p[N], sz[N];
 
int get(int x) {
	if (x == p[x]) {
		return x;
	}
	return p[x] = get(p[x]);
}
 
 
void us(int a, int b) {
	a = get(a);
	b = get(b);
 
	if (a != b) {
		if (sz[a] < sz[b]) {
			swap(a, b);
		}
		p[b] = a;
		sz[a] += sz[b];
	}
}
 
