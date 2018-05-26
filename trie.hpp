const int NONE = -1;

struct Trie {
    const static int CHAR_NUM = 26;
    const static char FIRST_CHAR = 'a';

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
};
