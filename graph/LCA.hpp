struct LCA {
    using Graph = vector< vector<int> >;

    const Graph& g;
    const int LOGV;
    const int root;

    vector< vector<int> > parent;
    vector<int> depth;

    LCA(const Graph& g, int root = 0) : g(g), LOGV(32 - __builtin_clz(g.size())), root(root) {
        int V = g.size();
        parent.resize(LOGV, vector<int>(V));
        depth.resize(V);
        
        dfs(root, -1, 0);
        for (int k = 0; k + 1 < LOGV; k++) {
            for (int v = 0; v < V; v++) {
                if (parent[k][v] < 0) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    void dfs(int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for (int i : g[v]) {
            if (i != p) dfs(i, v, d + 1);
        }
    }

    int operator()(int u, int v) const {
        if (depth[u] > depth[v]) swap(u, v);
        for (int k = 0; k < LOGV; k++) {
            if ((depth[v] - depth[u]) >> k & 1) {
                v = parent[k][v];
            }
        }
        if (u == v) return u;
        for (int k = LOGV - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};
