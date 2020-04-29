struct UnionFind {
    //各要素が属する集合の代表(根)を管理する
    //もし、要素xが根であればdata[x]は負の値を取り、-data[x]はxが属する集合の大きさに等しい
    vector<int> data;

    UnionFind(int sz) : data(sz, -1) {}

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        bool is_union = (x != y);
        if (is_union) {
            if (data[x] > data[y]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        return is_union;
    }

    int find(int x) {
        if (data[x] < 0) { //要素xが根である
            return x;
        } else {
            data[x] = find(data[x]); //data[x]がxの属する集合の根でない場合、根になるよう更新される
            return data[x];
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return -data[find(x)];
    }
};

struct Edge {
    int u, v;
    int cost;
    bool operator<(const Edge& e) const {
        return cost < e.cost;
    }
};

struct Graph {
    int n; //頂点数
    vector<Edge> es; //辺集合

    int kruskal() {
        sort(es.begin(), es.end());
        UnionFind uf(n);
        int min_cost = 0;
        for(int i = 0; i < (int)es.size(); i++) {
            Edge e = es[i];
            if (!uf.same(e.u, e.v)) {
                min_cost += e.cost;
                uf.unite(e.u, e.v);
            }
        }
        return min_cost;
    }
};

Graph input() {
   Graph g;
   int m;
   cin >> g.n >> m;
   g.es = vector<Edge>(m);
   for(int i = 0; i < m; i++) {
        cin >> g.es[i].u >> g.es[i].v >> g.es[i].cost;
   }
   return g;
}
