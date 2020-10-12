struct Edge {
    int u;
    int v;
    int al;
 
    Edge(int u_, int v_) {
        u = u_;
        v = v_;
        al = 1;
    }
};
 
vector<Edge> ed;
vector<int> g[SZ];
int pnt[SZ];
vector<int> tour;
 
void dfs(int cur) {
    int cnt = 0;
    for (; pnt[cur] < (int)g[cur].size(); pnt[cur]++) {
        int t = g[cur][pnt[cur]];
        int v = ed[t].v;
        if (v == cur) {
            v = ed[t].u;
        }
        if (ed[t].al) {
            ed[t].al = 0;
            dfs(v);
            cnt++;
        }
    }
    tour.push_back(cur);
}
