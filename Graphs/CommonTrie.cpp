const int alpha = 26;
const int NMAX = 2e6 + 10;

struct node {
	int temp;
	map<char, int> child;
	node() {
		//child.resize(alpha, -1);
		temp = 0;
	}
};

node arr[NMAX];
int sz = 0;

void insert(const string& s) {
	int n = s.size();
	int v = 0;
	for (int i = 0; i < n; i++) {
		char c = s[i] - 'a';
		if (arr[v].child.count(c) == 0) {
			arr[v].child[c] = ++sz;
		}
		v = arr[v].child[c];
	}
	arr[v].temp++;
}


//finding the k - th string in lexicographic order
string find_k(int k, int v = 0) {
	if (k <= arr[v].temp) {
		return "";
	}
	k -= arr[v].temp;

	for (auto to : arr[v].child) {
		if (k <= arr[to.second].cnt) {
			return char(to.first + 'a') + find_k(k, to.second);
		}
		else {
			k -= arr[to.second].cnt;
		}
	}
	return "";
}

bool find(const string& s) {
	int n = s.size();
	int v = 0;
	for (int i = 0; i < n; i++) {
		char c = s[i] - 'a';
		if (arr[v].child.count(c) == 0) {
			return false;
		}
		v = arr[v].child[c];
	}
	return arr[v].temp > 0;
}
