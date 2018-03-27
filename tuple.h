// the goal
template<typename... T_rest>
class Tuple;

namespace _implementation {
    // forward declaration

    // class to return the (n+1)-th type in the pack list
    template<size_t N, typename... Rest>
    class TupleElements {
        template<typename...>
        friend class Tuple;
    };

    // a class to provide partial specialization of get function (function partial specialization not allowed)
    template<size_t idx>
    class getter;
}

template<typename T1, typename... T_rest>
class Tuple<T1, T_rest...>:
    public Tuple<T_rest...> {

//    template<typename T, typename U, typename... U_rest> friend constexpr const T& get(const Tuple<U, U_rest...>& tuple);
//    template<typename T, typename U, typename... U_rest> friend constexpr T& get(Tuple<U, U_rest...>& tuple);
    template<typename U, typename... U_rest> friend constexpr const U& get(const Tuple<U_rest...>& tuple);
    template<typename U, typename... U_rest> friend constexpr U& get(Tuple<U_rest...>& tuple);
//    template<typename T> friend constexpr const T& get(const Tuple<T1, T_rest...>& tuple);

    template<size_t> friend class _implementation::getter;

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

// makeTuple function

template<typename T1, typename... T_rest>
constexpr Tuple<T1, T_rest...> makeTuple(const T1& value, T_rest... args) {
    return Tuple<T1, T_rest...>(value, args...);
}

// get forward declaration

template<size_t Idx, typename... T_rest>
constexpr typename _implementation::TupleElements<Idx, T_rest...>::_type& get(Tuple<T_rest...>& tuple);

template<size_t idx, typename... T_rest>
constexpr const typename _implementation::TupleElements<idx, T_rest...>::_type& get(const Tuple<T_rest...>& tuple);

// hiding implementation details in namespace

namespace _implementation {
    template<size_t N, typename T1, typename... T_rest>
    class TupleElements<N, T1, T_rest...>:
            public TupleElements<N - 1, T_rest...> {
    public:
        TupleElements() = delete;
        typedef typename TupleElements<N - 1, T_rest...>::_type _type;
    };

    template<typename T1, typename... T_rest>
    class TupleElements<0, T1, T_rest...>{
    public:
        TupleElements() = delete;
        typedef T1 _type;
    };

    template<size_t idx>
    class getter {

        template<size_t any> friend class _implementation::getter;

        template<size_t newIdx, typename... newT_rest>
        friend constexpr typename _implementation::TupleElements<newIdx, newT_rest...>::_type& ::get(Tuple<newT_rest...>& tuple);

        template<size_t newIdx, typename... newT_rest>
        friend constexpr const typename _implementation::TupleElements<newIdx, newT_rest...>::_type& ::get(const Tuple<newT_rest...>& tuple);

        template<typename T1, typename... T_rest>
        constexpr static typename TupleElements<idx, T1, T_rest...>::_type&
        getHelper(Tuple<T1, T_rest...>& tuple) {

            return getter<idx - 1>::getHelper(*static_cast<Tuple<T_rest...>* >(&tuple));
        }

        template<typename T1, typename... T_rest>
        constexpr static const typename  TupleElements<idx, T1, T_rest...>::_type&
        getHelper(const Tuple<T1, T_rest...>& tuple) {

            return getter<idx - 1>::getHelper(*static_cast<const Tuple<T_rest...>* >(&tuple));
        }
    public:
        getter() = delete;
    };

    template<>
    class getter<0>{

        template<size_t any> friend class getter;

        template<size_t newIdx, typename... newT_rest>
        friend constexpr typename _implementation::TupleElements<newIdx, newT_rest...>::_type& ::get(Tuple<newT_rest...>& tuple);

        template<size_t newIdx, typename... newT_rest>
        friend constexpr const typename _implementation::TupleElements<newIdx, newT_rest...>::_type& ::get(const Tuple<newT_rest...>& tuple);

        template<typename T1, typename... T_rest>
        constexpr static T1& getHelper(Tuple<T1, T_rest...>& tuple) {

            return tuple._value;
        }

        template<typename T1, typename... T_rest>
        constexpr static const T1& getHelper(const Tuple<T1, T_rest...>& tuple) {

            return tuple._value;
        }

    public:
        getter() = delete;
    };
}

// get idx function

template<size_t Idx, typename... T_rest>
constexpr typename _implementation::TupleElements<Idx, T_rest...>::_type& get(Tuple<T_rest...>& tuple) {
    return _implementation::getter<Idx>::getHelper(tuple);
}

template<size_t idx, typename... T_rest>
constexpr const typename _implementation::TupleElements<idx, T_rest...>::_type& get(const Tuple<T_rest...>& tuple) {
    return _implementation::getter<idx>::getHelper(tuple);
}

// get type function

template<typename T, typename T1, typename... T_rest>
constexpr const T& get(const Tuple<T1, T_rest...>& tuple) {
    if (std::is_same<T, T1>::value)
        return tuple._value;

    return get<T>(*static_cast<const Tuple<T_rest...>*>(&tuple));
}

template<typename T>
constexpr const T& get(const Tuple<>&) {
    return T();
}

template<typename T, typename T1, typename... T_rest>
constexpr T& get(Tuple<T1, T_rest...>& tuple) {
    if (std::is_same<T, T1>::value)
        return tuple._value;

    return get<T>(*static_cast<Tuple<T_rest...>*>(&tuple));
}

template<typename T>
constexpr T& get(Tuple<>&) {
    return T();
}