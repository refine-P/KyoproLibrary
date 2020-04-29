using Graph = vector< vector<int> >;
 
bool dfs(int cur, vector<int>& memo, Graph& g, vector<int>& order) {
    memo[cur] = 1;
    for (int nex : g[cur]) {
        if (memo[nex] == 2) continue;
        if (memo[nex] == 1) return false;
        if (!dfs(nex, memo, g, order)) return false;
    }
    memo[cur] = 2;
    order.push_back(cur);
    return true;
}
 
bool tsort(Graph& g, vector<int>& order) {
	vector<int> memo(g.size(), 0);
    for (int i = 0; i < g.size(); i++) {
        if (memo[i] != 0) continue;
        if (!dfs(i, memo, g, order)) return false;
    }
    reverse(order.begin(), order.end());
    return true;
}
