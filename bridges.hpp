typedef pair<int, int> P;
 
vector< vector<int> > G;
vector<int> ord, low;
vector<P> bridge;
 
void dfs(int cur, int par, int& t) {
    ord[cur] = ++t;
    low[cur] = ord[cur];
    for (int nex : G[cur]) {
        if (nex == par) continue;
        if (ord[nex] == 0) {
            dfs(nex, cur, t);
            low[cur] = min(low[cur], low[nex]);
            if (ord[cur] < low[nex]) bridge.push_back(minmax(cur, nex));
        } else {
            low[cur] = min(low[cur], ord[nex]);
        }
    }
}

// ?
void bridges(int v) {
    ord.resize(v, 0);
    low.resize(v);
    int t = 0;
    dfs(0, -1, t);
}
