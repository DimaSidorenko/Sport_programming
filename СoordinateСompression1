struct pt {
		ll x, y;
	};

	istream& operator >> (istream &in, pt &p) {
		in >> p.x >> p.y;
		return in;
	}


	void solve() {
		int n;
		cin >> n;
		vector<pt> pts(n);
					
		input(pts);
				
		map<ll, int> x;
		map<ll, int> y;

		for (int i = 0; i < n; i++) {
			auto to = pts[i];
			x[to.x] = 0;
			y[to.y] = 0;
		}

		int cnt_x = 0;
		for (auto &to : x) {
			to.second = cnt_x++;
		}

		int cnt_y = 0;
		for (auto &to : y) {
			to.second = cnt_y++;
		}

		for (auto &to : pts) {
			to.x = x[to.x];
			to.y = y[to.y];
		}
	}
