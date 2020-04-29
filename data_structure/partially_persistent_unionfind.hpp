//時刻t(t番目のクエリを処理した時点, 1-index)での各要素が属する集合の代表(根)を管理する
struct PartiallyPersisitentUnionFind {
    int current_time; //現在時刻(current_time番目までのクエリが処理し終わった)
    //現在時刻でのでの各要素が属する集合の代表(根)を管理する
    //もし、要素xが根であればdata[x]は負の値を取り、-data[x]はxが属する集合の大きさに等しい
    vector<int> data;
    vector<int> end_time; // 各要素が親でなくなった時刻
    vector< vector<pair<int, int> > > size_history; //各要素ごとの集合の大きさの変更履歴

    PartiallyPersisitentUnionFind(int sz) : current_time(0), data(sz, -1), end_time(sz, 1000000000), size_history(sz) {
        for (auto& v : size_history) v.emplace_back(0, -1);
    }

    bool unite(int x, int y) {
        x = find(current_time, x);
        y = find(current_time, y);
        current_time++;
        bool is_union = (x != y);
        if (is_union) {
            if (data[x] > data[y]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
            end_time[y] = current_time;
            size_history[x].emplace_back(current_time, data[x]);
        }
        return is_union;
    }

    int find(int t, int x) {
        if (t < end_time[x]) { //要素xが時刻tの時点で親を持たない
            return x;
        } else {
            return find(t, data[x]);
        }
    }

    bool same(int t, int x, int y) {
        return find(t, x) == find(t, y);
    }

    int size(int t, int x) {
        x = find(t, x);
        return -prev(lower_bound(begin(size_history[x]), end(size_history[x]), make_pair(t, 0)))->second;
    }
};
