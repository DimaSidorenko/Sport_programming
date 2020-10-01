int mergethem(vector<int>& a, int l, int m, int r)
{
	int Inv = 0;

	vector<int> buff(r - l + 1);
	int pos1 = l, pos2 = m + 1, posB = 0;

	while (pos1 <= m && pos2 <= r)
	{
		if (a[pos1] < a[pos2])
		{
			buff[posB++] = a[pos1++];
		}
		else
		{
			Inv += m - pos1 + 1;
			buff[posB++] = a[pos2++];
		}
	}

	while (pos1 <= m)
		buff[posB++] = a[pos1++];

	while (pos2 <= r)
		buff[posB++] = a[pos2++];

	copy(buff.begin(), buff.end(), a.begin() + l);

	return Inv;
}

int mergesort(vector<int>& a, int l, int r)
{
	int curInv = 0;
	if (l == r)
		return curInv;

	int m = (l + r) / 2;

	curInv += mergesort(a, l, m);
	curInv += mergesort(a, m + 1, r);

	curInv += mergethem(a, l, m, r);

	return curInv;
}
