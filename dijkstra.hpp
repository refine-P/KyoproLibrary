struct State {
    int at;
    ll cost; 
    //int prev;
    State(int at, ll cost/*, int prev*/) : at(at), cost(cost)/*, prev(prev)*/ {}
    bool operator>(const State& s) const {
        //if (cost != s.cost) return cost > s.cost;
        //if (prev != s.prev) return prev > s.prev; //最短経路を辞書順最小にする(省略可)
        //return at > s.at;
        return cost > s.cost;
    }
};

struct Edge {
    int to;
    ll cost;  
    Edge(int to, ll cost) : to(to), cost(cost) {}  
};

using Graph = vector<vector<Edge> >; //隣接リスト

const ll INF = 1e15;
//const int NONE = -1;

//sは始点、mincは最短経路のコスト、Prevは最短経路をたどる際の前の頂点
void dijkstra(int s, const Graph& graph, vector<ll>& minc/*, vector<int>& Prev*/){
    minc.assign(graph.size(), INF);
    //Prev.assign(graph.size(), INF);
    priority_queue<State, vector<State>, greater<State> > pq;
    pq.emplace(s, 0/*, NONE*/);
    while(!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        if (minc[cur.at] <= cur.cost) continue;
        minc[cur.at] = cur.cost;
        //Prev[cur.at] = cur.prev;
        for(const Edge& e : graph[cur.at]) {           
            ll cost = cur.cost + e.cost;
            if (minc[e.to] <= cost) continue;
            pq.emplace(e.to, cost/*, cur.at*/);
        }
    }
}
