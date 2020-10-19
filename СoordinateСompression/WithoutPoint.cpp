//first = x, second = y;
	void CoordinateCommpression(vector<pair<int, int>> &pts) {
		vector <int> xs, ys;
		
		for (auto to : pts) {
			xs.pb(to.first);
			ys.pb(to.second);
		}

		xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
		ys.resize(unique(ys.begin(), ys.end()) - ys.begin());

		unordered_map<ll, int> x;
		unordered_map<ll, int> y;

		for (int i = 0; i < xs.size(); i++) {
			x[xs[i]] = i;
			y[ys[i]] = i;
		}

		for (auto &to : pts) {
			to.first = x[to.first];
			to.second = y[to.second];
		}
	}
