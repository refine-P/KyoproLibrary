const int MAX_V = 10000;
const int INF = 1000000;

struct Edge {
    int to, cap, rev;  //行き先、容量、逆辺
    Edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};

vector<Edge> G[MAX_V];
bool used[MAX_V];

void add_edge(int from, int to, int cap) {
    G[from].push_back(Edge(to, cap, G[to].size()));
    G[to].push_back(Edge(from, 0, G[from].size() - 1));
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    used[v] = true;
    for (unsigned int i = 0; i < G[v].size(); i++) {
        Edge &e = G[v][i];
        if (!used[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (1) {
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, INF);
        if (f == 0) return flow;
        flow += f;
    }
}
