// task: https://codeforces.com/contest/508/problem/D
#define _USE_MATH_DEFINES
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include<climits>
#include<set>
#include<map>
#include<cmath>
#include<iomanip>
#include<iterator>
#include<queue>
#include<stack>
#include<cctype>
#include<deque>
#include<time.h>
#include<bitset>
#include<random>
#include<unordered_set>
#include<unordered_map>
#include<sstream>
#include<random>
#include<numeric>
#include <assert.h>

#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:16777216")

#define en "\n"
#define for0(i, n) for(int i = 0; i < n; i++)
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
#define pb push_back
#define pii pair<int, int>
#pragma warning(disable : 4996)
#define fst first
#define snd second
typedef long long ll;
typedef long double ld;

using namespace std;


template<typename T> void print(vector<T>& a)
{
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << ' ';
	cout << en;
}

template<typename T> void print(deque<T>& a)
{
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << ' ';
	cout << en;
}

template<typename T> void print(vector<vector<T>>& a)
{
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a[i].size(); j++)
			cout << a[i][j];
		cout << en;
	}
}

template <typename T> void input(vector<T>& a)
{
	for (int i = 0; i < a.size(); i++)
		cin >> a[i];
}

template<typename T> void input(deque<T>& a)
{
	for (int i = 0; i < a.size(); i++)
		cin >> a[i];
}

template<typename T> void input(vector<vector<T>>& a)
{
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < a[i].size(); j++)
			cin >> a[i][j];
}

const ll INF = 1e18;
const ll MOD = 998244353;
const int NMAX = 4e4;
double eps = 1e-8;


ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}


vector<int> g[NMAX];
vector<int> ans;


int get_hash(string s) {
	return s[0] * 200 + s[1];
}


string get_str(int hash) {
	string ans = "";
	ans += char(hash / 200);
	ans += char(hash % 200);
	return ans;
}


void dfs(int u) {
	while (!g[u].empty()) {
		int v = g[u].back();
		g[u].pop_back();
		dfs(v);
	}
	ans.push_back(u);
}


bool used[NMAX];
void dfs1(int v) {
	used[v] = false;
	for (auto to : g[v]) {
		if (used[to]) {
			dfs1(to);
		}
	}
}


void solveC() {
	int n;
	cin >> n;
	vector<int> deg(NMAX);

	int pot_st;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int u = get_hash(s.substr(0, 2));
		int v = get_hash(s.substr(1, 2));

		used[u] = true;
		used[v] = true;
		//cout << u << " " << v << en;
		g[u].push_back(v);
		deg[u]++;
		deg[v]--;
		if (i == 0) pot_st = u;
	}

	int st = -1, end = -1;
	for (int i = 0; i < NMAX; i++) {
		if (deg[i] == 0) {
			continue;
		}
		if (abs(deg[i]) > 1) {
			cout << "NO" << en;
			return;
		}

		if (deg[i] > 0) {
			if (st != -1) {
				cout << "NO" << en;
				return;
			}
			else {
				st = i;
			}
		}
		if (deg[i] < 0) {
			if (end != -1) {
				cout << "NO" << en;
				return;
			}
			else {
				end = i;
			}
		}
	}

	if (st == -1 && end != -1 || st != -1 && end == -1) {
		cout << "NO" << en;
		return;
	}

	if (st == -1 && end == -1) {
		st = pot_st;
	}

	dfs1(st);
	for (int i = 0; i < NMAX; i++) {
		if (used[i]) {
			cout << "NO" << en;
			return;
		}
	}


	cout << "YES" << en;
	dfs(st);
	reverse(all(ans));

	string ans1 = "";

	string cur;
	for (auto to : ans) {
		cur = get_str(to);
		ans1 += cur[0];
	}
	ans1 += cur[1];

	cout << ans1;
}





int main() {
	srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cout.setf(ios::fixed);
	cout.precision(10);
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int t = 1;
	//cin >> t;
	while (t--) {
		solveC();
	}
}
