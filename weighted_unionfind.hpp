struct WeightedUnionFind {
    //各要素が属する集合の代表(根)を管理する
    //もし、要素xが根であればdata[x]は負の値を取り、-data[x]はxが属する集合の大きさに等しい
    vector<int> data;
    vector<int> diff_weight;

    WeightedUnionFind(int sz) : data(sz, -1), diff_weight(sz, 0) {}

    // weight(y) - weight(x) = w となるように merge する
    bool unite(int x, int y, int w) {
        w += weight(x);
        w -= weight(y);
        x = find(x);
        y = find(y);
        bool is_union = (x != y);
        if (is_union) {
            if (data[x] > data[y]) {
                swap(x, y);
                w = -w;
            }
            data[x] += data[y];
            data[y] = x;
            diff_weight[y] = w;
        }
        return is_union;
    }

    int find(int x) {
        if (data[x] < 0) { //要素xが根である
            return x;
        } else {
            int par = data[x];
            data[x] = find(data[x]); //data[x]がxの属する集合の根でない場合、根になるよう更新される
            diff_weight[x] += diff_weight[par];
            return data[x];
        }
    }

    int weight(int x) {
        find(x);
        return diff_weight[x];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int diff(int x, int y) {
        return weight(y) - weight(x);
    }

    int size(int x) {
        return -data[find(x)];
    }
};
