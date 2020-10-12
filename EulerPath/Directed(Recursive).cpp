//нужно добавить без них умрет
#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:16777216")

int cnt[NMAX][NMAX];
set<int> g[NMAX];
string ans = "";


void dfs(int u) {
	for (auto v : g[u]) {
		if (cnt[u][v]) {
			cnt[u][v]--;
		}
		else {
			continue;
		}
		dfs(v);
		ans += v + 'a';
	}
}


void solve() {
	int n; string s;
	cin >> n;
	cin >> s;
	vector<int> in(26);
	vector<int> out(26);

	for (int i = 0; i < n - 1; i++) {
		int u = s[i] - 'a';
		int v = s[i + 1] - 'a';

		cnt[u][v]++;
		g[u].insert(v);

		out[u]++;
		in[v]++;
	}

	//find start vert
	int st = -1;

	for (int i = 0; i < 26; i++) {	
		if (out[i] > in[i]) {
			st = i;
			break;
		}
	}

	if (st == -1) {
		for (int i = 0; i < 26; i++) {
			if (out[i] > 0) {
				st = i;
				break;
			}
		}
	}

	dfs(st);
	ans += st + 'a';
	reverse(all(ans));
	cout << ans;
}
