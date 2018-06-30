vector< vector<int> > G;
vector<int> ord, low;
vector<bool> is_art;
 
void dfs(int cur, int par, int& t) {
    ord[cur] = ++t;
    low[cur] = ord[cur];
    int cnt = 0;
    for (int nex : G[cur]) {
        if (nex == par) continue;
        if (ord[nex] == 0) {
            cnt++;
            dfs(nex, cur, t);
            low[cur] = min(low[cur], low[nex]);
            if (par != -1 && ord[cur] <= low[nex]) is_art[cur] = true;
        } else {
            low[cur] = min(low[cur], ord[nex]);
        }
    }
    if (par == -1 && cnt > 1) is_art[cur] = true;
}

// 関節点
void articulationPoints(int v) {
    ord.resize(v, 0);
    low.resize(v);
    is_art.resize(v, false);
    int t = 0;
    dfs(0, -1, t);
}
