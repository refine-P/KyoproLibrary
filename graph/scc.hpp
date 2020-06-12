class StronglyConnectedComponents {
private:
    void dfs(int v, vector<int>& used) {
        used[v] = true;
        for (int i = 0; i < G[v].size(); i++) {
            if (!used[G[v][i]]) dfs(G[v][i], used);
        }
        vs.push_back(v);
    }

    void rdfs(int v, int k, vector<int>& used) {
        used[v] = true;
        cmp[v] = k;
        for (int i = 0; i < rG[v].size(); i++) {
            if (!used[rG[v][i]]) rdfs(rG[v][i], k, used);
        }
    }

public:
    int V;
    vector< vector<int> > G, rG;
    vector<int> vs;
    vector<int> cmp;

    StronglyConnectedComponents(int n) : V(n), G(n), rG(n), cmp(n, -1) {}

    void add_edge(int from, int to) {
        G[from].push_back(to);
        rG[to].push_back(from);
    }

    int run() {
        vector<int> used(V, false);
        vs.clear();
        for (int v = 0; v < V; v++) {
            if (!used[v]) dfs(v, used);
        }
        used.assign(V, false);
        int k = 0;
        for (int i = (int)vs.size() - 1; i >= 0; i--) {
            if (!used[vs[i]]) rdfs(vs[i], k++, used);
        }
        return k;
    }
};
