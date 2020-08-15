//алгоритм построен на поиске дополнительного пути.
// В массиве aut хранится: [0, n - 1] - левая часть, [n, n + m - 1] - правая часть

int mt[NMAX]; // здесь ребра
bool used[NMAX];
vector<int> g[NMAX];

bool dfs(int v) {
	if (used[v]) {
		return false;
	}
	used[v] = true;
	for (auto to : g[v]) {
		if (mt[to] == -1 || dfs(mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

ll kuhn(int n, int m) {
	for (int i = n; i < n + m; i++) {
		mt[i] = -1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			used[j] = false;
		}
		dfs(i);
	}
	ll ans = 0;
	for (int i = n; i < n + m; i++) {
		ans += (mt[i] != -1 ? 1 : 0);
	}
	return ans;
}

//вывод 
for (int i = n; i < n + m; i++){
  cout << i << " " << mt[i] << en;
}


