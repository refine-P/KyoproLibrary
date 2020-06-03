// [Depends on]: OrderedMultiSet
template<class T>
class OrderedSet : public OrderedMultiSet<T> {
    using OMS = OrderedMultiSet<T>;

public:
    using OMS::OMS;

    inline void insert(T val) noexcept override {
        if (OMS::contains(val)) return;
        OMS::insert(val);
    }
};
