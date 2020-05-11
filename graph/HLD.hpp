// https://qiita.com/ageprocpp/items/8dfe768218da83314989
// http://codeforces.com/blog/entry/53170
// https://github.com/ningenMe/compro-library/blob/master/lib/graph/Tree.cpp#L220
// https://beet-aizu.github.io/library/library/tree/heavylightdecomposition.cpp.html
// https://ei1333.github.io/luzhiled/snippets/tree/heavy-light-decomposition.html
class HLD {
public:
    using Graph = vector< vector<int> >;
    using Segment = pair<int, int>;

private:
    void dfs_size(int cur, int par) {
        // if g[cur][0] == par, always sub_size[nex] < sub_size[par]
        // and this will be broken...
        if (!g[cur].empty() && g[cur][0] == par) swap(g[cur][0], g[cur].back());

        for (int& nex : g[cur]) {
            if (nex == par) continue;
            parent[nex] = cur;

            dfs_size(nex, cur);
            sub_size[cur] += sub_size[nex];

            if (sub_size[nex] > sub_size[g[cur][0]]) {
                swap(nex, g[cur][0]);
            }
        }
    }

    // head: HLD
    // in, out: Euler Tour
    void dfs_hld(int cur, int par, int& times) {
        in[cur] = times++;
        for (int nex : g[cur]) {
            if (nex == par) continue;

            // if nex == g[cur][0]: heavy edge
            // else: light edge
            head[nex] = (nex == g[cur][0] ? head[cur] : nex);

            dfs_hld(nex, cur, times);            
        }
        out[cur] = times;
    }

    // convert node/edge path to segments
    // segment: [l, r)
    // is_edge_path ? edge path : node path
    vector<Segment> to_segments(int u, int v, bool is_edge_path) {
        vector<Segment> segments;
        while (true) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) {
                if (u != v || !is_edge_path) {
                    segments.emplace_back(in[u] + is_edge_path, in[v] + 1);
                }
                break;
            }
            segments.emplace_back(in[head[v]], in[v] + 1);
            v = parent[head[v]];
        }
        return segments;
    }

public:

    Graph g;
    vector<int> sub_size, parent, in, out, head;

    HLD(const Graph& tree, const int root = 0) 
    : g(tree), sub_size(tree.size(), 1), parent(tree.size(), -1),
      in(tree.size()), out(tree.size()), head(tree.size(), root) {
        dfs_size(root, -1);
        int times = 0;
        dfs_hld(root, -1, times);
    }

    int lca(int u, int v) {
        while (true) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return u;
            v = parent[head[v]];
        }
    }

    inline vector<Segment> node_path_to_segments(int u, int v) {
        return to_segments(u, v, false);
    }

    // you have to convert edge cost to node cost
    // see: https://www.hamayanhamayan.com/entry/2017/04/10/172636
    inline vector<Segment> edge_path_to_segments(int u, int v) {
        return to_segments(u, v, true);
    }

    Segment subtree_to_segment(int v) {
        return {in[v], out[v]};
    }
};
