struct Edge {
  int to;
  int cost;  
  Edge(int to, int cost) : to(to), cost(cost) {}  
};

typedef vector<vector<Edge> > AdjList; //隣接リスト

const int INF = 1000000000;
const int NONE = -1;

AdjList graph;
vector<int> minc; //最短経路のコスト
vector<int> Prev; //最短経路をたどる際の前の頂点

//trueなら負の閉路を検出
bool bellman_ford(int n, int s) { //nは頂点数、sは始点
    minc.resize(n, INF);
    Prev.resize(n, NONE);
    minc[s] = 0; //始点までの距離は0
    for (int i = 1; i < n; i++) {
        for (int from = 0; from < n; from++) {
            for (Edge e : graph[from]) {
                if (minc[from] != INF && minc[e.to] > minc[from] + e.cost) {
                    minc[e.to] = minc[from] + e.cost;
                    Prev[e.to] = from;
                }
            }
        }
    }
    
    //負の閉路を検出
    for (int from = 0; from < n; from++) {
        for (Edge e : graph[from]) {
            if (minc[from] != INF && minc[e.to] > minc[from] + e.cost) {
                return true;
            }
        }
    }
    return false;
}
