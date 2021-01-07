int need = k - sum;
vector<int> prev(need + 1);
vector<bool> dp(need + 1);

dp[0] = 1;
for (int i = 0; i < weights.size(); i++) {
	for (int w = need - weights[i]; w >= 0; w--) {
		if (dp[w] && !dp[w + weights[i]]) {
			dp[w + weights[i]] = 1;
			prev[w + weights[i]] = i;
		}
	}
}

if (!dp[need]) {
	cout << "No" << en;
	return;
}

vector<int> knapsack_ans;
int temp = need;
while (temp != 0) {
	knapsack_ans.pb(prev[temp]);
	temp -= weights[prev[temp]];
}
