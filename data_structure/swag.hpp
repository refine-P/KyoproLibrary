// https://scrapbox.io/data-structures/Sliding_Window_Aggregation
template<class SemiGroup>
struct SWAG {
    using T = typename SemiGroup::T;

    struct Node {
        T val, sum;
        Node(const T& v, const T& s) : val(v), sum(s) {}
    };

    stack<Node> front_stack, back_stack;

    SWAG() {}

    bool empty() const {
        return front_stack.empty() && back_stack.empty();
    }

    size_t size() const {
        return front_stack.size() + back_stack.size();
    }

    T fold_all() {
        assert(!empty());
        if (front_stack.empty()) return back_stack.top().sum;
        else if (back_stack.empty()) return front_stack.top().sum;
        else return SemiGroup::merge(front_stack.top().sum, back_stack.top().sum);
    }

    void push(const T& x) {
        if (back_stack.empty()) {
            back_stack.emplace(x, x);
        } else {
            T sum = SemiGroup::merge(back_stack.top().sum, x);
            back_stack.emplace(x, sum);
        }
    }

    void pop() {
        assert(!empty());

        if (front_stack.empty()) {
            front_stack.emplace(back_stack.top().val, back_stack.top().val);
            back_stack.pop();

            while (!back_stack.empty()) {
                T sum = SemiGroup::merge(front_stack.top().sum, back_stack.top().val);
                front_stack.emplace(back_stack.top().val, sum);
                back_stack.pop();
            }
        }
        front_stack.pop();
    }
};

// 以下、SemiGroupの例
template <class U = ll>
struct RMQSG {
    using T = U;
    static T merge(T a, T b) { return min(a, b); }
};
