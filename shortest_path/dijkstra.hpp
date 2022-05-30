struct State {
    int at;
    ll cost;
    // int prev;
    State(int at, ll cost/*, int prev*/) : at(at), cost(cost)/*, prev(prev)*/ {}
    bool operator>(const State& s) const {
        return cost > s.cost;
    }
};

struct Edge {
    int to;
    ll cost;
    Edge(int to, ll cost) : to(to), cost(cost) {}
};

using Graph = vector< vector<Edge> >;  // 隣接リスト

const ll INF = 1e15;
// const int NONE = -1;

// sは始点、prevsは最短経路をたどる際の前の頂点
vector<ll> dijkstra(int s, const Graph& graph/*, vector<int>& prevs*/){
    vector<ll> minc(graph.size(), INF);
    // prevs.assign(graph.size(), NONE);

    priority_queue<State, vector<State>, greater<State> > pq;
    pq.emplace(s, 0/*, NONE*/);
    minc[s] = 0;

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        if (minc[cur.at] < cur.cost) continue; 

        for (const Edge& e : graph[cur.at]) {
            ll cost = cur.cost + e.cost;
            if (minc[e.to] <= cost) continue;
            minc[e.to] = cost;
            // prevs[e.to] = cur.at;
            pq.emplace(e.to, cost/*, cur.at*/);
        }
    }
    return minc;
}
