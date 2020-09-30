const int alpha = 2;

//for trie max NMAX value is 5e6
const int NMAX = 6e6 + 10;

struct node {
	int temp;
	int cnt;
	vector<int> child;
	node() {
		child.resize(alpha, -1);
		temp = 0;
		cnt = 0;
	}
};

node arr[NMAX];
int sz = 0;
int const len = 30;

void insert(int x) {
	int v = 0;
	for (int i = len - 1; i >= 0; i--) {
		int c = (x & (1 << i)) ? 1 : 0;
		if (arr[v].child[c] == -1) {
			arr[v].child[c] = ++sz;
		}
		v = arr[v].child[c];
		arr[v].cnt++;
	}
}

int find_min(int x) {
	int v = 0;
	int ans = 0;
	bool is = false;
	for (int i = len - 1; i >= 0; i--) {
		int c = (x & (1 << i)) ? 1 : 0;
		int to;
		if (arr[v].child[c] == -1) {
			to = -1;
		}
		else {
			to = arr[v].child[c];
		}
		if (to != -1 && (is || arr[to].cnt != 1)){
			v = to;
		}
		else {
			ans += (1 << i);
			v = arr[v].child[(c ^ 1)];
			is = true;
		}
	}
	return ans;
}

int find_max(int x) {
	int v = 0;
	int ans = 0;
	for (int i = len - 1; i >= 0; i--) {
		int c = (x & (1 << i)) ? 0 : 1;
		int to;
		if (arr[v].child[c] == -1) {
			to = -1;
		}
		else {
			to = arr[v].child[c];
		}
		if (to != -1) {
			v = to;
			ans += (1 << i);
			continue;
		}
		v = arr[v].child[(c ^ 1)];
	}
	return ans;
}
