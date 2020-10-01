struct Node
{
	int end, start;
	int length;
 
	int next[27] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
 
	int suff_edge;
};
 
Node tree[100005];
 
int curNode;
int ptr;
 
string s;
 
void insertNew(int i)
{
	int tmp = curNode;
	//максимальный суфф палиндром текущего палиндрома
	while (1)
	{
		int curLen = tree[tmp].length;
		if (i - curLen - 1 >= 0 && s[i] == s[i - curLen - 1])
			break;
		tmp = tree[tmp].suff_edge;
	}
 
	if (tree[tmp].next[s[i] - 'a'] != 0) // вершина уже была в боре
	{
		curNode = tree[tmp].next[s[i] - 'a'];
		return;
	}
 
	Node newNode;
	tree[tmp].next[s[i] - 'a'] = ptr;
 
	newNode.start = i - tree[tmp].length - 1;
	newNode.end = i;
	newNode.length = tree[tmp].length + 2;
 
	tree[ptr] = newNode;
 
	curNode = ptr;
	ptr++;
	tmp = tree[tmp].suff_edge;
 
	if (tree[curNode].length == 1) // суфф ссылка только на 0
	{
		tree[curNode].suff_edge = 1;
		return;
	}
 
	while (1)
	{
		int curLen = tree[tmp].length;
		if (i - curLen - 1 >= 0 && s[i] == s[i - curLen - 1])
			break;
		tmp = tree[tmp].suff_edge;
	}
 
	tree[curNode].suff_edge = tree[tmp].next[s[i]-'a'];
}
 
void solve(int t) {
	int n; cin >> n;
	cin >> s;
	
	Node d1, d2; // -1, 0
	d1.length = -1; 
	d2.length = 0;
	d1.suff_edge = d2.suff_edge = 0;
	tree[0] = d1;
	tree[1] = d2;
 
	curNode = 0;
	ptr = 2;
 
	for (int i = 0; i < n; i++)
		insertNew(i);

}
