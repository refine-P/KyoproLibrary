// アルゴリズムまとめ
// see: https://miti-7.hatenablog.com/entry/2018/07/10/233335
// 負辺除去
// see: https://snuke.hatenablog.com/entry/2017/06/07/115821
// see: http://sigma425.hatenablog.com/entry/2014/10/12/122018
struct MinCostFlow {
    using Flow = ll;
    using Cost = ll;

    const Cost INF = 1e15;
    const int NONE = -1;

    struct Edge {
        int to;
        Flow cap;
        Cost cost;
        int rev;
        Edge(int to, Flow cap, Cost cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
    };

    bool has_negative;
    vector< vector<Edge> > G;
    vector<Cost> po;
    vector<int> prev_v, prev_e;

private:
    bool bellman_ford(int s, vector<Cost>& minc) {
        int n = G.size();
        minc.assign(n, INF);
        minc[s] = 0;

        for (int i = 1; i < n; i++) {
            bool updated = false;
            for (int from = 0; from < n; from++) {
                for (const Edge& e : G[from]) {
                    if (e.cap > 0 && minc[e.to] > minc[from] + e.cost) {
                        minc[e.to] = minc[from] + e.cost;
                        updated = true;
                    }
                }
            }
            if (!updated) return false;
        }

        //負の閉路を検出
        for (int from = 0; from < n; from++) {
            for (const Edge& e : G[from]) {
                if (e.cap > 0 && minc[e.to] > minc[from] + e.cost) {
                    return true;
                }
            }
        }
        return false;
    }

    struct State {
        int at;
        Cost cost;
        State(int at, Cost cost) : at(at), cost(cost) {}
        bool operator>(const State& s) const {
            return cost > s.cost;
        }
    };

    void dijkstra(int s, vector<Cost>& minc){
        minc.assign(G.size(), INF);

        priority_queue<State, vector<State>, greater<State> > pq;
        pq.emplace(s, 0);
        minc[s] = 0;

        while(!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            if (minc[cur.at] < cur.cost) continue;

            int sz = G[cur.at].size();
            for (int i = 0; i < sz; ++i) {
                const Edge& e = G[cur.at][i];

                ll cost = cur.cost + e.cost + po[cur.at] - po[e.to];
                if (e.cap <= 0 || minc[e.to] <= cost) continue;

                minc[e.to] = cost;
                prev_v[e.to] = cur.at;
                prev_e[e.to] = i;

                pq.emplace(e.to, cost);
            }
        }
    }

public:
    MinCostFlow(int V) : G(V), has_negative(false) {}

    void add_edge(int from, int to, Flow cap, Cost cost) {
        if (cost < 0) has_negative = true;
        G[from].emplace_back(to, cap, cost, G[to].size());
        G[to].emplace_back(from, 0, -cost, G[from].size() - 1);
    }

    Cost min_cost_flow(int s, int t, Flow f) {
        int n = G.size();
        prev_v.assign(n, NONE);
        prev_e.assign(n, NONE);

        if (has_negative) {
            // [WARNING!!!]: 負閉路には未対応
            // 負辺除去で対処可能？
            // 負閉路に対応する話
            // see: https://miti-7.hatenablog.com/entry/2018/07/10/233335
            // see: https://kopricky.github.io/code/Academic/min_cost_flow_with_negative_cycles.html
            assert(!bellman_ford(s, po));
        } else {
            po.assign(n, 0);
        }

        Cost res = 0;
        while (f > 0) {
            vector<Cost> minc;
            dijkstra(s, minc);

            if (minc[t] == INF) return NONE;

            for (int i = 0; i < n; i++) {
                po[i] += minc[i];
            }

            Flow d = f;
            for (int v = t; v != s; v = prev_v[v]) {
                d = min(d, G[prev_v[v]][prev_e[v]].cap);
            }

            f -= d;
            res += d * po[t];

            for (int v = t; v != s; v = prev_v[v]) {
                Edge& e = G[prev_v[v]][prev_e[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }

        return res;
    }
};
