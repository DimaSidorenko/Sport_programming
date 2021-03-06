const int ALPHABETSIZE = 26;
const int NMAX = 300005;

struct Node {
	int nxt[ALPHABETSIZE];
	int longSuffLink = -1;
	int suffLink = -1;
	bool isTerminal = false;
	int parentNode = -1;
	int prevSym;
	int strIndex;
};

Node bor[NMAX];

int cur_free = 2; // индекс свободной вершины
int root = 1; // индекс вершины корня

void add_string_to_bor(string s, int ix = -1) // сама строка + можно добавить ее индекс
{
	int cur = root;
	for (char c : s)
	{
		int c_int = c - 'a';

		if (bor[cur].nxt[c_int])
		{
			cur = bor[cur].nxt[c_int];
		}
		else
		{
			bor[cur].nxt[c_int] = cur_free;
			bor[cur_free].parentNode = cur;
			bor[cur_free].prevSym = c_int;

			cur = cur_free;

			cur_free++;
		}

	}

	bor[cur].isTerminal = 1;
	bor[cur].strIndex = ix;
}

void create_suff_links() // создание суфф ссылок в боре(длинных и обычных)
{
	int cur;
	queue<int> q;
	bor[root].suffLink = bor[root].longSuffLink = root;
	cur = root;
	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		int nxt_node = bor[cur].nxt[i];
		if (nxt_node)
		{
			q.push(nxt_node);
			bor[nxt_node].suffLink = bor[nxt_node].longSuffLink = root;
		}
	}

	while (!q.empty())
	{
		cur = q.front(); q.pop();
		for (int c_int = 0; c_int < ALPHABETSIZE; c_int++)
		{
			int nxt_node = bor[cur].nxt[c_int];
			if (nxt_node)
			{
				q.push(nxt_node);
				int suffLinkCurrentNode = bor[cur].suffLink;

				while (suffLinkCurrentNode != root && bor[suffLinkCurrentNode].nxt[c_int] == 0)
				{
					suffLinkCurrentNode = bor[suffLinkCurrentNode].suffLink;
				}

				// update suff link
				if (bor[suffLinkCurrentNode].nxt[c_int] != 0)
				{
					bor[nxt_node].suffLink = bor[suffLinkCurrentNode].nxt[c_int];
				}
				else
				{
					bor[nxt_node].suffLink = root;
				}

				// update long suff link
				if (bor[bor[nxt_node].suffLink].isTerminal)
				{
					bor[nxt_node].longSuffLink = bor[nxt_node].suffLink;
				}
				else
				{
					bor[nxt_node].longSuffLink = bor[bor[nxt_node].suffLink].longSuffLink;
				}
			}
		}
	}
}

vector<bool> get_occurrences_in_text(string& text, vector<string>& patterns)
{
	int n = patterns.size();
	for (int i = 0; i < n; i++)
		add_string_to_bor(patterns[i], i);

	create_suff_links();

	vector<bool> occurs(n);

	int cur = root;

	for (char c: text)
	{
		int c_int = c - 'a';

		while (cur != root && bor[cur].nxt[c_int] == 0)
		{
			cur = bor[cur].suffLink;
		}
		if (bor[cur].nxt[c_int])
			cur = bor[cur].nxt[c_int];
		else
			cur = root;
		int curLongSuffLink = cur;
		while (curLongSuffLink != root)
		{
			if (bor[curLongSuffLink].isTerminal)
				occurs[bor[curLongSuffLink].strIndex] = 1;
			curLongSuffLink = bor[curLongSuffLink].longSuffLink;
		}
	}

	return occurs;
}
