template<const int CHAR_NUM = 26, const char FIRST_CHAR = 'a'>
struct Trie {
    static const int NONE;

    struct Node {
        bool leaf;
        int idxs[CHAR_NUM];
        Node() {
            leaf = false;
            fill(idxs, idxs + CHAR_NUM, NONE);
        };
    };

    vector<Node> tree;

    Trie() {
        tree.emplace_back();
    }

    void insert(const string& s) {
        int cur = 0;
        for (char c : s) {
            if (tree[cur].idxs[c - FIRST_CHAR] == NONE) {
                tree[cur].idxs[c - FIRST_CHAR] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].idxs[c - FIRST_CHAR];
        }
        tree[cur].leaf = true;
    }

    bool find(const string& s) {
        int cur = 0;
        for (char c : s) {
            if (tree[cur].idxs[c - FIRST_CHAR] == NONE) {
                return false;
            }
            cur = tree[cur].idxs[c - FIRST_CHAR];
        }
        return tree[cur].leaf;
    }

    int dfs(int cur, int K) {
        int res = K + 1;
        for (int i = 0; i < CHAR_NUM; i++) {
            if (tree[cur].idxs[i] == NONE) continue;
            int hoge = dfs(tree[cur].idxs[i], K);
            if (hoge >= K) continue;
            res = min(res, hoge + 1);
        }
        if (res > K) res = 0;
        return res;
    }
};

// 定数の定義はこう書かないとなぜかエラーが出る
template<const int CHAR_NUM, const char FIRST_CHAR>
const int Trie<CHAR_NUM, FIRST_CHAR>::NONE = -1;
