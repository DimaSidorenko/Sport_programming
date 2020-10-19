	// Отдай Димасу задачу!
  
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
	#define rep(i, n) for(int i = 0; i < n; i++)
	#define all(x) (x).begin(), (x).end()
	#define allr(x) (x).rbegin(), (x).rend()
	#define pb push_back
	#define pii pair<int, int>
	#define pll pair<ll, ll>
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
	const int NMAX = 501;
	double eps = 1e-8;

	unordered_map<ll, int> x;
	unordered_map<ll, int> y;
	
	
	const int SEGTREE_SIZE = 1e5;
	struct segtree {

		vector<ll> t;
		int size;

		int const ZERO = 0;

		void init(int n) {
			size = 1;
			while (size < n) {
				size *= 2;
			}
			t.assign(2 * size, ZERO);
		}

		segtree(int n = SEGTREE_SIZE) {
			init(n);
		}

		segtree(vector<long long>& a) {
			init(a.size());
			build(a);
		}


		int combine(int a, int b) {
			return a + b;
		}


		void build(vector<long long>& a, int v, int tl, int tr) {
			if (tr - tl == 1) {
				if (tl < a.size())
					t[v] = ZERO;
				return;
			}
			int tm = (tr + tl) / 2;
			build(a, v * 2 + 1, tl, tm);
			build(a, v * 2 + 2, tm, tr);
			t[v] = combine(t[v * 2 + 1], t[v * 2 + 2]);
		}

		void build(vector<long long>& a) {
			build(a, 0, 0, size);
		}

		void modify(int v, int tl, int tr, int l, int r, int val) {
			if (tr <= l || tl >= r) {
				return;
			}

			if (l <= tl && tr <= r) {
				t[v] += val;
				return;
			}

			int tm = (tl + tr) / 2;

			modify(v * 2 + 1, tl, tm, l, r, val);
			modify(v * 2 + 2, tm, tr, l, r, val);
		}

		void modify(int l, int r, int val) {
			modify(0, 0, size, l, r, val);
		}


		ll get(int v, int tl, int tr, int pos) {

			if (tr == tl + 1) {
				return t[v];
			}

			int tm = (tl + tr) / 2;

			if (pos < tm) {
				return get(v * 2 + 1, tl, tm, pos) + t[v];
			}
			else {
				return get(v * 2 + 2, tm, tr, pos) + t[v];
			}
		}

		ll get(int pos) {
			return get(0, 0, size, pos);
		}
	};


	struct photo {
		int xl, yl, xr, yr;
	};


	struct query {
		int l, r,val;
	};

	
	void solve() {
		vector<pll> pts;
		int n;
		cin >> n;

		vector<photo> phs(n);
		vector<pii> pt;
		for (int i = 0; i < n; i++) {
			int xl, yl, xr, yr;
			cin >> phs[i].xl >> phs[i].yl >> phs[i].xr >> phs[i].yr;
			pts.pb({ phs[i].xl, phs[i].yl });
			pts.pb({ phs[i].xr, phs[i].yr });
			
			int m;
			cin >> m;
			for (int j = 0; j < m; j++) {
				int x, y;
				cin >> x >> y;
				pts.push_back({ x, y });
				pt.push_back({ x, y });
			}	
		}

		vector <int> xs, ys;
		for (auto to : pts) {
			xs.pb(to.first);
			ys.pb(to.second);
		}

		sort(all(xs));
		sort(all(ys));

		xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
		ys.resize(unique(ys.begin(), ys.end()) - ys.begin());

		for (int i = 0; i < xs.size(); i++) {
			x[xs[i]] = i;
		}
		for (int i = 0; i < ys.size(); i++) {
			y[ys[i]] = i;
		}

		
		vector<vector<int>> sl(xs.size());
		map<pii, int> cnt;

		vector<vector<query>> for_segtree(xs.size() + 1);

		for (int i = 0; i < pt.size(); i++) {
			int cur_x = x[pt[i].first];
			int cur_y = y[pt[i].second];
			
			if (cnt.count({ cur_x,cur_y }) == 0) {
				sl[cur_x].push_back(cur_y);
			}
			cnt[{cur_x, cur_y}]++;
		}


		for (auto to : phs) {	
			int xl = x[to.xl];
			int yl = y[to.yl];
			int xr = x[to.xr];
			int yr = y[to.yr];
		
			for_segtree[xl].pb({ yl, yr, 1 });
			for_segtree[xr + 1].pb({ yl, yr, -1 });
		}

		auto st = segtree(ys.size() + 1);

		ll ans = pt.size();
		for (int i = 0; i < xs.size(); i++) {	
			for (auto to : for_segtree[i]) {
				st.modify(to.l, to.r + 1, to.val);
			}

			for (auto to : sl[i]) {	
				int x = i;
				int y = to;
				
				int res = st.get(y);

				if (res == cnt[{x, y}]) {
					ans -= cnt[{x, y}];
				}
			}
		}

		cout << ans << en;
	}


	int main() {
		srand(time(0));
		ios::sync_with_stdio(false);
		cin.tie(0);
		cout.tie(0);
		cout.setf(ios::fixed);
		cout.precision(10);
		/*freopen("filter.in", "r", stdin);
		freopen("filter.out", "w", stdout);*/
	#ifdef _DEBUG
		freopen("input.txt", "r", stdin);
		//freopen("output.txt", "w", stdout);
	#endif
		int t = 1;
		//cin >> t;
		while (t--) {
			solve();
		}
	}
