// [Depends]: StronglyConnectedComponents
struct TwoSAT {
    int literal_num;
    StronglyConnectedComponents scc;

    TwoSAT(int V) : literal_num(V), scc(2 * V) {}

    // x, y: index
    // flag_x, flag_y: literal's value
    void add(int x, bool flag_x, int y, bool flag_y) noexcept {
        scc.add_edge(x + literal_num * flag_x, y + literal_num * !flag_y);
        scc.add_edge(y + literal_num * flag_y, x + literal_num * !flag_x);        
    }

    bool run() noexcept {
        scc.run();
        return satisfy();
    }

    bool satisfy() noexcept {
        for (int i = 0; i < literal_num; i++) {
            if (scc.cmp[i] == scc.cmp[i + literal_num]) return false;
        }
        return true;
    }

    vector<int> dump() noexcept {
        vector<int> res(literal_num);
        for (int i = 0; i < literal_num; i++) {
            res[i] = scc.cmp[i] > scc.cmp[i + literal_num];
        }
        return res;
    }
};
