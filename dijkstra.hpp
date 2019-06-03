struct State {
    int at;
    int cost; 
    int prev;
    State(int at, int cost, int prev) : at(at), cost(cost), prev(prev) {}
    bool operator>(const State& s) const {
        if (cost != s.cost) return cost > s.cost;
        if (prev != s.prev) return prev > s.prev; //最短経路を辞書順最小にする(省略可)
        return at > s.at;
    }
};

struct Edge {
    int to;
    int cost;  
    Edge(int to, int cost) : to(to), cost(cost) {}  
};

typedef vector<vector<Edge> > AdjList; //隣接リスト

const int INF = 1000000000;
const int NONE = -1;

AdjList graph;

//sは始点、mincは最短経路のコスト、Prevは最短経路をたどる際の前の頂点
void dijkstra(int s, vector<int>& minc, vector<int>& Prev){ 
    priority_queue<State, vector<State>, greater<State> > pq;
    pq.push(State(s, 0, NONE));
    while(!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        if (minc[cur.at] <= cur.cost) continue;
        minc[cur.at] = cur.cost;
        Prev[cur.at] = cur.prev;
        for(Edge e : graph[cur.at]) {           
            int cost = cur.cost + e.cost;
            if (minc[e.to] <= cost) continue;
            pq.push(State(e.to, cost, cur.at));
        }
    }
}
