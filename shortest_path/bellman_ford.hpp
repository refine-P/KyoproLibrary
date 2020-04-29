struct Edge {
    int to;
    ll cost;
    Edge(int to, ll cost) : to(to), cost(cost) {}
};

using Graph = vector<vector<Edge> >; //隣接リスト

const ll INF = 1e15;
// const int NONE = -1;

// sは始点、mincは最短経路のコスト、Prevは最短経路をたどる際の前の頂点
// trueなら負の閉路を検出
bool bellman_ford(int s, const Graph& graph, vector<ll>& minc/*, vector<int> Prev*/) { 
    int n = graph.size();
    minc.resize(n, INF);
    //Prev.resize(n, NONE);
    minc[s] = 0; //始点までの距離は0
    for (int i = 1; i < n; i++) {
        for (int from = 0; from < n; from++) {
            for (const Edge& e : graph[from]) {
                if (minc[from] != INF && minc[e.to] > minc[from] + e.cost) {
                    minc[e.to] = minc[from] + e.cost;
                    //Prev[e.to] = from;
                }
            }
        }
    }

    //負の閉路を検出
    for (int from = 0; from < n; from++) {
        for (const Edge& e : graph[from]) {
            if (minc[from] != INF && minc[e.to] > minc[from] + e.cost) {
                return true;
            }
        }
    }
    return false;
}
