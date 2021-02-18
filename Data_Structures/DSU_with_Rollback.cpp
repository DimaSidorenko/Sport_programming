const int N = 2e5 + 10;
int p[N], sz[N];
stack<int> st;
int cnt;

int get(int x) {
	if (x == p[x]) {
		return x;
	}
	return get(p[x]);
}


void us(int a, int b) {
	a = get(a);
	b = get(b);
	if (a != b) {
		if (sz[a] < sz[b]) {
			swap(a, b);
		}

		sz[a] += sz[b];
		p[b] = p[a];
		st.push(b);
		cnt--;
	}
}



void solve() {
	int n, m;
	cin >> n >> m;
	forn(i, n) {
		p[i] = i, sz[i] = 1;
	}
	cnt = n;
	forn(i, m) {
		string op;
		cin >> op;
		if (op == "persist") {
			st.push(-1);
		}
		if (op == "union") {
			int a, b;
			cin >> a >> b;
			us(a, b);
			cout << cnt << en;
		}
		if (op == "rollback") {
			int cur = st.top();
			while (cur != -1) {
				p[cur] = cur;
				cnt++;

				st.pop();
				cur = st.top();
			}
			st.pop();
			cout << cnt << en;
		}
	}
}
