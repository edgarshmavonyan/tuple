
template<size_t N, typename... Rest>
class TupleElements;


template<size_t N, typename T1, typename... T_rest>
class TupleElements<N, T1, T_rest...>:
        public TupleElements<N - 1, T_rest...> {
public:
    typedef T1 _type;
};

template<>
class TupleElements<0>{
public:
};

template<typename... elements>
class Tuple;

template<typename T1, typename... T_rest>
class Tuple<T1, T_rest...>:
    public Tuple<T_rest...> {
protected:
    T1 _value;
public:
    Tuple(): _value() {
        std::cout << "ntuple" << std::endl;
    }

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



/**
template<size_t idx, typename... T_rest>
constexpr auto get(const Tuple<T_rest...>& tuple) {

}

template<typename T1, typename... T_rest>
constexpr auto get<0, T1, T_rest...>(const Tuple<T1, T_rest...>& tuple) {
    return tuple.getValue();
}
template<size_t idx, typename T1, typename... T_rest>
constexpr auto get(const Tuple<T1, T_rest...>& tuple) {
    return (idx == 0 ? tuple.getValue(): get<idx - 1, T_rest...>(Tuple<T_rest...>(tuple)));
}


template<size_t idx, typename T1, typename... T_rest>
constexpr auto get<idx, T1, T_rest...>(const Tuple<T1, T_rest...>& tuple) {
    return get<idx - 1>(static_cast<Tuple<T_rest...> >(tuple));
}
**/
/**
template<typename Ret, typename... T_rest>
Ret get(size_t idx, Tuple<T_rest...> tuple);

template<typename Ret>
Ret get(size_t idx, Tuple<> tuple) {}

template<typename Ret, typename T1, typename... T_rest>
Ret get(size_t idx, Tuple<T1, T_rest...> tuple) {
    if (idx == 0)
        return tuple.getValue();
    else
        return get<T_rest...>(idx - 1, static_cast<Tuple<T_rest...> >(tuple));
};
**/

template<size_t idx, typename T1, typename... T_rest>
TupleElements<idx, T1, T_rest...>::_type kek() {
    if (idx == 0)
        return
}