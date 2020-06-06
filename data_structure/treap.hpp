template<class U = ll, class V = U>
struct Nothing {
    using Tm = U;
    using To = V;
    static Tm merge(const Tm& x, const Tm& y) { return unit(); }
    static To op_merge(const To& x, const To& y) { return op_unit(); }
    static Tm apply(const Tm& vm, const To& vo, size_t seg_len) { return vm; }
    static constexpr Tm unit() { return Tm(0); }
    static constexpr To op_unit() { return To(0); }
};

// [Related]: monoid_op
// https://www.slideshare.net/iwiwi/2-12188757
// https://tubo28.me/compprog/algorithm/treap/
// https://ei1333.github.io/luzhiled/snippets/structure/rbst.html
// https://qiita.com/tubo28/items/f058582e457f6870a800
template <class MonoidOp = Nothing<> >
class Treap {
public:
    using Tm = typename MonoidOp::Tm;
    using To = typename MonoidOp::To;

private:
    inline static unsigned int randxor() noexcept {
        static unsigned int x=123456789,y=362436069,z=521288629,w=88675123;
        unsigned int t;
        t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
    }

public:
    struct Node {
        unsigned int pri;
        size_t sz;
        Tm val, sum;
        To lazy;
        unique_ptr<Node> lch, rch;

        Node(const Tm& x) : pri(randxor()), sz(1), val(x), sum(x), lazy(MonoidOp::op_unit()) {}

        static constexpr size_t size(const unique_ptr<Node>& node) noexcept {
            return (!node ? 0 : node->sz);
        }

        static constexpr Tm getSum(const unique_ptr<Node>& node) noexcept {
            return (!node ? MonoidOp::unit() : node->sum);
        }
    };

private:
    inline static unique_ptr<Node>& update(unique_ptr<Node>& node) noexcept {
        node->sz = Node::size(node->lch) + Node::size(node->rch) + 1;
        node->sum = MonoidOp::merge(MonoidOp::merge(Node::getSum(node->lch), node->val), Node::getSum(node->rch));
        return node;
    }

    inline static unique_ptr<Node>& push(unique_ptr<Node>& node) noexcept {
        if (node->lazy == MonoidOp::op_unit()) return update(node);

        node->val = MonoidOp::apply(node->val, node->lazy, 1);

        if (node->lch) {
            node->lch->lazy = MonoidOp::op_merge(node->lch->lazy, node->lazy);
            node->lch->sum = MonoidOp::apply(node->lch->sum, node->lazy, Node::size(node->lch));
        }

        if (node->rch) {
            node->rch->lazy = MonoidOp::op_merge(node->rch->lazy, node->lazy);
            node->rch->sum = MonoidOp::apply(node->rch->sum, node->lazy, Node::size(node->rch));
        }

        node->lazy = MonoidOp::op_unit();
        return update(node);
    }

    // split into [0, pos), [pos, size(node))
    static pair< unique_ptr<Node>, unique_ptr<Node> > split(unique_ptr<Node> node, size_t pos) noexcept {
        if (!node) return pair< unique_ptr<Node>, unique_ptr<Node> >();

        assert(pos <= Node::size(node));

        push(node);
        if (pos <= Node::size(node->lch)) {
            auto p = split(move(node->lch), pos);
            node->lch = move(p.second);
            return {move(p.first), move(update(node))};
        } else {
            auto p = split(move(node->rch), pos - Node::size(node->lch) - 1);
            node->rch = move(p.first);
            return {move(update(node)), move(p.second)};
        }
    }

    static unique_ptr<Node> merge(unique_ptr<Node> nodeL, unique_ptr<Node> nodeR) noexcept {
        if (!nodeR) return nodeL;
        if (!nodeL) return nodeR;

        if (nodeL->pri > nodeR->pri) {
            push(nodeL);
            nodeL->rch = merge(move(nodeL->rch), move(nodeR));
            return move(update(nodeL));
        } else {
            push(nodeR);
            nodeR->lch = merge(move(nodeL), move(nodeR->lch));
            return move(update(nodeR));
        }
    }

    static void insert(unique_ptr<Node>& node, size_t pos, const Tm& val) noexcept {
        auto p = split(move(node), pos);
        auto tmp = merge(move(p.first), move(unique_ptr<Node>(new Node(val))));
        node = move(merge(move(tmp), move(p.second)));
    }

    static void erase(unique_ptr<Node>& node, size_t pos) noexcept {
        if (!node) return;

        assert(pos < Node::size(node));

        auto pr = split(move(node), pos + 1);
        auto pl = split(move(pr.first), pos);

        node = merge(move(pl.first), move(pr.second));
    }

    static void update(unique_ptr<Node>& node, size_t a, size_t b, const To& x) noexcept {
        auto p1 = split(move(node), b);
        auto p2 = split(move(p1.first), a);
        p2.second->lazy = MonoidOp::op_merge(p2.second->lazy, x);
        node = merge(merge(move(p2.first), move(push(p2.second))), move(p1.second));
    }

    static Tm query(unique_ptr<Node>& node, size_t a, size_t b) noexcept {
        auto p1 = split(move(node), b);
        auto p2 = split(move(p1.first), a);
        Tm res = Node::getSum(p2.second);
        node = merge(merge(move(p2.first), move(p2.second)), move(p1.second));
        return res;
    }

    static void set(unique_ptr<Node>& node, size_t pos, const Tm& x) {
        push(node);
        if (pos < Node::size(node->lch)) set(node->lch, pos, x);
        else if (pos == Node::size(node->lch)) node->val = x;
        else set(node->rch, pos - Node::size(node->lch) - 1, x);
        update(node);
    }

    static unique_ptr<Node> build(size_t l, size_t r, const vector<Tm>& v) {
        if (l + 1 >= r) return unique_ptr<Node>(new Node(v[l]));
        return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
    }

    static void dump(unique_ptr<Node>& node) noexcept {
        if (!node) return;

        push(node);
        dump(node->lch);
        cerr << node->val << " ";
        dump(node->rch);
    }

protected:
    unique_ptr<Node> root;

private:
    Treap(unique_ptr<Node>& node) : root(move(node)) {}

public:
    Treap() = default;
    Treap(size_t sz, const Tm& initial_value = MonoidOp::unit()) {
        vector<Tm> v(sz, initial_value);
        root = build(0, sz, v);
    }

    Treap(const vector<Tm>& v) {
        root = build(0, v.size(), v);
    }

    constexpr bool empty() const noexcept {
        return !root;
    }

    constexpr size_t size() const noexcept {
        return Node::size(root);
    }

    // // split into [0, pos), [pos, size())
    // [WARNING!!!]: Don't use this Treap after split
    inline pair< Treap, Treap > split(size_t pos) noexcept {
        auto p = split(move(root), pos);
        return {Treap(p.first), Treap(p.second)};
    }

    // merge tree from the right of this Treap
    // [WARNING!!!]: Don't use tree after merge
    inline void merge(Treap& tree) noexcept {
        root = merge(move(root), move(tree.root));
    }

    inline void insert_at(size_t pos, const Tm& val) noexcept {
        insert(root, pos, val);
    }

    inline void erase_at(size_t pos) noexcept {
        erase(root, pos);
    }

    // [a, b)
    inline void update(size_t a, size_t b, const To& x) {
        update(root, a, b, x);
    }

    // [a, b)
    inline Tm query(size_t a, size_t b) noexcept {
        return query(root, a, b);
    }

    inline Tm get(size_t pos) noexcept {
        return query(pos, pos + 1);
    }

    inline void set(size_t pos, const Tm& x) {
        set(root, pos, x);
    }

    inline void dump() noexcept {
        cerr << "Seq: ";
        dump(root);
        cerr << newl;
    }
};
