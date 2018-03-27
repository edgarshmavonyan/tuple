
template<size_t N, typename... Rest>
class TupleElements {
    template<typename...>
    friend class Tuple;
};


template<size_t N, typename T1, typename... T_rest>
class TupleElements<N, T1, T_rest...>:
        public TupleElements<N - 1, T_rest...> {
public:
    typedef typename TupleElements<N - 1, T_rest...>::_type _type;
};

template<typename T1, typename... T_rest>
class TupleElements<0, T1, T_rest...>{
public:
    typedef T1 _type;
};

template<typename... T_rest>
class Tuple;

template<typename T1, typename... T_rest>
class Tuple<T1, T_rest...>:
    public Tuple<T_rest...> {

    template<size_t, typename...>
    friend class getter;

protected:
    T1 _value;
public:
    Tuple(): _value() {}

    Tuple(const T1& value, T_rest... args): _value(value), Tuple<T_rest...>(args...) {}

    Tuple(const Tuple<T1, T_rest...>& other) : _value(other._value), Tuple<T_rest...>(other) {}

    // rvaluereference-constructors to implement

    Tuple<T1, T_rest...>& operator=(const Tuple<T1, T_rest...>& other) {
        _value = other._value;
        *static_cast<Tuple<T_rest...>* >(this) = static_cast<Tuple<T_rest...> >(other);
    }

    T1 getValue() const {
        return _value;
    }

    void swap(Tuple<T1, T_rest...>& other) {
        std::swap(other._value, _value);
        static_cast<Tuple<T_rest...>* >(this)->swap(*static_cast<Tuple<T_rest...>* >(&other));
    }
};

template<>
class Tuple<>{
public:
    void swap(Tuple<>& other) {}
};

template<typename... T_rest>
constexpr void print(const Tuple<T_rest...>& t);

template<typename T1, typename... T_rest>
constexpr void print(const Tuple<T1, T_rest...>& kek) {
    std::cout << kek.getValue() << ' ';
    print(Tuple<T_rest...>(kek));
};

template<>
constexpr void print<>(const Tuple<>& t) {}

template<typename T1, typename... T_rest>
constexpr Tuple<T1, T_rest...> makeTuple(const T1& value, T_rest... args) {
    return Tuple<T1, T_rest...>(value, args...);
}


template<size_t idx, typename... T_rest>
class getter {

    template<size_t newIdx, typename... newT_rest>
    friend typename TupleElements<newIdx, newT_rest...>::_type& get(Tuple<newT_rest...>& tuple);

    template<size_t newIdx, typename... newT_rest>
    friend const typename TupleElements<newIdx, newT_rest...>::_type& get(const Tuple<newT_rest...>& tuple);

};

template<>
class getter<0>{
public:
    template<size_t newIdx, typename... newT_rest>
    friend typename TupleElements<newIdx, newT_rest...>::_type& get(Tuple<newT_rest...>& tuple);

    template<size_t newIdx, typename... newT_rest>
    friend const typename TupleElements<newIdx, newT_rest...>::_type& get(const Tuple<newT_rest...>& tuple);
private:
    template<typename T1, typename... T_rest>
            constexpr static T1& getHelper(Tuple<T1, T_rest...>& tuple) {

        return tuple._value;
    }

    template<typename T1, typename... T_rest>
            constexpr static const T1& getHelper(const Tuple<T1, T_rest...>& tuple) {

        return tuple._value;
    }
};

template<size_t idx>
class getter<idx> {
public:
    template<size_t newIdx, typename... newT_rest>
    friend typename TupleElements<newIdx, newT_rest...>::_type& get(Tuple<newT_rest...>& tuple);

    template<size_t newIdx, typename... newT_rest>
    friend const typename TupleElements<newIdx, newT_rest...>::_type& get(const Tuple<newT_rest...>& tuple);
private:
    template<typename T1, typename... T_rest>
    constexpr static typename TupleElements<idx, T1, T_rest...>::_type&
        getHelper(Tuple<T1, T_rest...>& tuple) {

            return getter<idx - 1>().getHelper(*static_cast<Tuple<T_rest...>* >(&tuple));
    }

    template<typename T1, typename... T_rest>
    constexpr static const typename  TupleElements<idx, T1, T_rest...>::_type&
        getHelper(const Tuple<T1, T_rest...>& tuple) {

            return getter<idx - 1>().getHelper(*static_cast<const Tuple<T_rest...>* >(&tuple));
    }
};

template<size_t idx, typename... T_rest>
typename TupleElements<idx, T_rest...>::_type& get(Tuple<T_rest...>& tuple) {
    return getter<idx>::getHelper(tuple);
}

template<size_t idx, typename... T_rest>
const typename TupleElements<idx, T_rest...>::_type& get(const Tuple<T_rest...>& tuple) {
    return getter<idx>::get(tuple);
};