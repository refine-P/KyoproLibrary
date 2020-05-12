class BipartiteMatching {
public:
    using Graph = vector< vector<int> >;

private:
    bool dfs(int v, vector<int>& used) {
        used[v] = true;
        for (int u : g[v]) {
            int w = match[u];
            if (w < 0 || !used[w] && dfs(w, used)) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

public:
    const Graph& g;
    vector<int> match;

    BipartiteMatching(const Graph& bi_graph) : g(bi_graph) {}

    int operator()() {
        int n = g.size();
        match.assign(n, -1);

        int res = 0;
        for (int v = 0; v < n; v++) {
            if (match[v] < 0) {
                vector<int> used(n, false);
                if (dfs(v, used)) res++;
            }
        }
        return res;
    }
};
