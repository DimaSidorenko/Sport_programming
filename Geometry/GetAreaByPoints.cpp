double get_area_by_coordinates(vector<pair<int, int>> &coordinates) // площадь многоугольника по точкам
{
	double sum = 0;
	int n = coordinates.size();
	for (int i = 0; i < n; i++)
	{
		int x_cur = coordinates[i].first, y_cur = coordinates[i].second;
		int x_next = coordinates[(i + 1) % n].first, y_next = coordinates[(i + 1) % n].second;

		sum += (x_cur - x_next) * (y_cur + y_next);
	}

	return sum / 2;
}
