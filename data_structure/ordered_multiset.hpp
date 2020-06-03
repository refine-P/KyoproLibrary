// [Depends on]: Treap
template<class T>
class OrderedMultiSet : public Treap< Nothing<T> > {
public:
    using Tree = Treap< Nothing<T> >;
    using Node = typename Tree::Node;

private:
    static T at(const unique_ptr<Node>& node, size_t pos) noexcept {
        if (pos < Node::size(node->lch)) return at(node->lch, pos);
        if (pos == Node::size(node->lch)) return node->val;
        return at(node->rch, pos - Node::size(node->lch) - 1);
    }

    static size_t lower_bound(const unique_ptr<Node>& node, T val) noexcept {
        if (!node) return 0;
        if (val <= node->val) return lower_bound(node->lch, val);
        return lower_bound(node->rch, val) + Node::size(node->lch) + 1;
    }

    static size_t upper_bound(const unique_ptr<Node>& node, T val) noexcept {
        if (!node) return 0;
        if (val < node->val) return upper_bound(node->lch, val);
        return upper_bound(node->rch, val) + Node::size(node->lch) + 1;
    }

    static bool contains(const unique_ptr<Node>& node, T val) noexcept {
        if (!node) return false;
        if (val == node->val) return true;
        if (val < node->val) return contains(node->lch, val);
        else return contains(node->rch, val);
    }

    // Use these function only inside
    void insert_at(size_t, const typename Tree::Tm&);
    void erase_at(size_t);

public:
    using Tree::Treap;

    // Note: https://qiita.com/matsumoto_sp/items/233503b4a31dc1f190b6
    OrderedMultiSet() = default;
    OrderedMultiSet(const vector<T>& v) : Tree::Treap(v) {
        assert(is_sorted(v.begin(), v.end()));
    }

    // Don't use these functions
    void update(size_t, size_t, const typename Tree::To&) = delete;
    typename Tree::Tm query(size_t, size_t, const typename Tree::To&) = delete;
    typename Tree::Tm get(size_t) = delete;
    void set(size_t, const typename Tree::Tm&) = delete;

    inline T at(size_t pos) noexcept {
        assert(pos < Tree::size());
        return at(Tree::root, pos);
    }

    // return position (index)
    // if val doesn't exist, return size()
    inline size_t find(T val) noexcept {
        return (contains(val) ? lower_bound(val) : Tree::size());
    }

    // return position (index)
    inline size_t lower_bound(T val) noexcept {
        return lower_bound(Tree::root, val);
    }

    // return position (index)
    inline size_t upper_bound(T val) noexcept {
        return upper_bound(Tree::root, val);
    }

    inline bool contains(T val) noexcept {
        return contains(Tree::root, val);
    }

    inline size_t count(T val) noexcept {
        return upper_bound(val) - lower_bound(val);
    }

    inline virtual void insert(T val) noexcept {
        Tree::insert_at(lower_bound(val), val);
    }

    inline void erase(T val) noexcept {
        if (!contains(val)) return;
        Tree::erase_at(lower_bound(val));
    }
};
