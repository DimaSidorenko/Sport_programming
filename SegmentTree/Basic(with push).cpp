ll tAdd[NMAX * 4];
ll t[NMAX * 4];
ll a[NMAX];

const int INF = 1e9 + 5;

void build(int v, int tl, int tr){
    if (tl == tr){
        t[v] = a[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build(v *2 + 1, tl, tm);
    build(v * 2 + 2, tm +1, tr);
    t[v] = t[v * 2 +1 ] + t[v * 2 + 2];
}

void push(int v, int tl, int tr){
    if (tAdd[v] != INF){
        t[v] = (tr - tl + 1) * tAdd[v];
//        cout << "change done : " << t[v] << en;
        if (tl != tr) {
            tAdd[v * 2 + 1] = tAdd[v * 2 + 2] = tAdd[v];
        }
    }
   tAdd[v] = INF;
}

void modify(int v, int tl, int tr, int l, int r, ll value){
    push(v, tl, tr);
    if (tr < l || tl > r)
        return;
    if (l <= tl && tr <= r){
        tAdd[v] = value;
//        cout << "change " << tl<< " " << tr << " " << value<< en;
        push(v, tl, tr);
        return;
    }
    int tm =(tl + tr) /2;
    modify(v * 2 + 1, tl, tm, l, r, value);
    modify(v * 2 + 2, tm + 1, tr, l, r, value);
    t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

ll query(int v, int tl, int tr, int l, int r){
    push(v, tl, tr);
    if (tl > r || tr < l)
        return 0;
    if (l <= tl && tr <= r){
        return t[v];
    }
    int tm = (tl + tr) /2;
    ll ql =query(v * 2 +1, tl, tm, l, r);
    ll qr =query(v * 2 +2, tm+1, tr, l, r);
    return ql + qr;
}



void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        char q; int l, r, x;
        cin >> q;
        if (q == 'A'){
            cin >> l >> r >> x;
            l--;
            r--;
            modify(0, 0, n - 1, l, r, x);
        }
        else {
            cin >> l >> r;
            l--;
            r--;
            cout << query(0, 0, n-1, l, r) << en;
        }
    }

}


