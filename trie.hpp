template<const int CHAR_NUM = 26, const char FIRST_CHAR = 'a', const int NONE = -1>
struct Trie {
    struct Node {
        bool word_exists;
        int idxs[CHAR_NUM]; // idxs[c - FIRST_CHAR]: 次の文字がcであるNodeの場所(treeのindex)
        Node() : word_exists(false) {
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
        tree[cur].word_exists = true;
    }

    bool find(const string& s) {
        int cur = 0;
        for (char c : s) {
            if (tree[cur].idxs[c - FIRST_CHAR] == NONE) {
                return false;
            }
            cur = tree[cur].idxs[c - FIRST_CHAR];
        }
        return tree[cur].word_exists;
    }
};
