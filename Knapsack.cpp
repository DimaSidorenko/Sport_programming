vector<int> get_items_with_max_value(vector<pair<int, int>> items, int max_weight) { // возвращает предметы для макс. стоимости
	int n = items.size();
	vector<vector<int>> dp(n+1, vector<int>(max_weight+1));

	for (int i = 0; i <= max_weight; i++)
		dp[0][i] = 0;

	for (int i = 0; i <= n; i++)
		dp[i][0] = 0;

	for (int cur_item = 1; cur_item <= n; cur_item++)
	{
		for (int cur_weight = 1; cur_weight <= max_weight; cur_weight++)
		{
			int weight_item = items[cur_item-1].first;
			int value_item = items[cur_item-1].second;

			if (cur_weight >= weight_item)
				dp[cur_item][cur_weight] = max(dp[cur_item - 1][cur_weight], dp[cur_item - 1][cur_weight - weight_item] + value_item);
			else
				dp[cur_item][cur_weight] = dp[cur_item - 1][cur_weight];
		}
	}

	vector<int> ans;

	int item = n;
	int weight = max_weight;
	
	while (dp[item][weight])
	{
		if (dp[item - 1][weight] == dp[item][weight])
			item--;
		else
		{
			weight -= items[item-1].second;
			ans.push_back(item-1);
			item--;
		}
	}

	return ans;
}
