constexpr ll INF = 1e18;

struct Dinic {
    using T = ll;

    struct Edge {
        int to;
        T cap;
        int rev;  //行き先、容量、逆辺
        Edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    vector< vector<Edge> > G;
    vector<int> level, iter;

private:
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (const Edge& e : G[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    T dfs(int v, int t, T f) {
        if (v == t) return f;
        for (int& i = iter[v]; i < G[v].size(); i++) {
            Edge& e = G[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

public:
    Dinic(int V) : G(V), level(V, -1), iter(V, 0) {}

    void add_edge(int from, int to, T cap) {
        G[from].push_back(Edge(to, cap, G[to].size()));
        G[to].push_back(Edge(from, 0, G[from].size() - 1));
    }

    T max_flow(int s, int t) {
        T flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            fill(iter.begin(), iter.end(), 0);
            T f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
    }
};
