vector<ll> h;
vector<ll> p;
 
const ll Pow = 31;
 
void Init(string &s)
{
	h[0] = s[0];
	p[0] = 1;
 
	for (int i = 1; i < s.length(); i++)
	{
		p[i] = p[i - 1] * Pow;
		h[i] = h[i - 1] + p[i] * s[i];
	}
}
 
ll GetHash(int l, int r)
{
	return h[r] - (l == 0 ? 0 : h[l - 1]);
}
