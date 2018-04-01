// the goal
template<typename... T_rest>
class Tuple;

// hiding implementation details in namespace
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

    // a class to provide constexpr comparing functions
    class tupleComparator;
}


template<typename T1, typename... T_rest>
class Tuple<T1, T_rest...>:
    public Tuple<T_rest...> {
public:

    template<typename...>
    friend class Tuple;

    template<typename U, typename U1, typename... U_rest>
    friend constexpr typename std::enable_if_t<std::is_same<U, U1>::value, U&>
    get(Tuple<U1, U_rest...>& tuple);
    template<typename U, typename U1, typename... U_rest>
    friend constexpr typename std::enable_if_t<!std::is_same<U, U1>::value, U&>
    get(Tuple<U1, U_rest...>& tuple);


    template<typename U, typename U1, typename... U_rest>
    friend constexpr typename std::enable_if_t<std::is_same<U, U1>::value, const U&>
    get(const Tuple<U1, U_rest...>& tuple);
    template<typename U, typename U1, typename... U_rest>
    friend constexpr typename std::enable_if_t<!std::is_same<U, U1>::value, const U&>
    get(const Tuple<U1, U_rest...>& tuple);


    template<typename U, typename U1, typename... U_rest>
    friend constexpr typename std::enable_if_t<std::is_same<U, U1>::value, U>
    get(Tuple<U1, U_rest...>&& tuple);
    template<typename U, typename U1, typename... U_rest>
    friend constexpr typename std::enable_if_t<!std::is_same<U, U1>::value, U>
    get(Tuple<U1, U_rest...>&& tuple);


    template<size_t> friend class _implementation::getter;

    friend class _implementation::tupleComparator;

protected:
    T1 _value;
public:
    constexpr Tuple(): _value() {}

    constexpr Tuple(const T1& value, T_rest... args): _value(value), Tuple<T_rest...>(args...) {}

    constexpr Tuple(const Tuple<T1, T_rest...>& other) : _value(other._value), Tuple<T_rest...>(other) {}

    // rvalue-reference constructors to implement

    template<typename U, typename... U_rest>
    Tuple<T1, T_rest...>& operator=(const Tuple<U, U_rest...>& other) {
        _value = other._value;
        *static_cast<Tuple<T_rest...>* >(this) = *static_cast<const Tuple<U_rest...>* >(&other);
    }

    void swap(Tuple<T1, T_rest...>& other) {
        std::swap(other._value, _value);
        static_cast<Tuple<T_rest...>* >(this)->swap(*static_cast<Tuple<T_rest...>* >(&other));
    }

    template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
    constexpr bool friend operator<(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

    template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
    constexpr bool friend operator==(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

    template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
    constexpr bool friend operator!=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

    template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
    constexpr bool friend operator<=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

    template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
    constexpr bool friend operator>(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

    template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
    constexpr bool friend operator>=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);
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

// comparison forward declaration

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator<(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator==(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator!=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator<=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator>(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator>=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

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

    class tupleComparator {
    private:
//        template<typename...>
//        friend class ::Tuple;
        template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
        constexpr bool friend ::operator<(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

        template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
        constexpr bool friend ::operator==(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

        template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
        constexpr bool friend ::operator!=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

        template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
        constexpr bool friend ::operator<=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

        template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
        constexpr bool friend ::operator>(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);

        template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
        constexpr bool friend ::operator>=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other);


        template<typename T, typename... T_rest, typename U, typename... U_rest>
        static constexpr bool _less(const Tuple<T, T_rest...>& first, const Tuple<U, U_rest...>& other) {

            static_assert(sizeof...(T_rest) == sizeof...(U_rest),
                            "Comparison of tuples with different sizes is prohibited.");

            return first._value < other._value || (!(other._value < first._value) && tupleComparator::_less(
                    *static_cast<const Tuple<T_rest...>*>(&first), *static_cast<const Tuple<T_rest...>*>(&other)));
        }

        template<typename T, typename U>
        static constexpr bool _less(const Tuple<T>& first, const Tuple<U>& other) {
            return first._value < other._value;
        }

        template<typename T, typename... T_rest, typename U, typename... U_rest>
        static constexpr bool _equal(const Tuple<T, T_rest...>& first, const Tuple<U, U_rest...>& other) {
            return sizeof...(T_rest) == sizeof...(U_rest) && other._value == first._value && tupleComparator::_equal(
                    *static_cast<const Tuple<T_rest...>*>(&first), *static_cast<const Tuple<T_rest...>*>(&other));
        }

        template<typename T, typename U>
        static constexpr bool _equal(const Tuple<T>& first, const Tuple<U>& other) {
            return first._value == other._value;
        }
    public:
        tupleComparator() = delete;
    };
    /**
    class tupleComparator<T, U> {
    private:
        template<typename, typename...>
        friend class tupleComparator;
        template<typename...>
        friend class Tuple;

        static constexpr bool _less(const Tuple<T>& first, const Tuple<U>& other) {
            return first._value < other._value;
        }

        static constexpr bool _equal(const Tuple<T>& first, const Tuple<U>& other) {
            return first._value == other._value;
        }
    };
     **/
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

// using compile time if statement realization
// with enable_if (in c++17 we can use "constexpr if" statement to reduce code)

template<typename T, typename T1, typename... T_rest>
constexpr typename std::enable_if_t<std::is_same<T, T1>::value, const T&>
get(const Tuple<T1, T_rest...>& tuple) {
    return tuple._value;
}
template<typename T, typename T1, typename... T_rest>
constexpr typename std::enable_if_t<!std::is_same<T, T1>::value, const T&>
get(const Tuple<T1, T_rest...>& tuple) {
    return get<T>(*static_cast<const Tuple<T_rest...>*>(&tuple));
}


template<typename T, typename T1, typename... T_rest>
constexpr typename std::enable_if_t<std::is_same<T, T1>::value, T&>
get(Tuple<T1, T_rest...>& tuple) {
    return tuple._value;
}
template<typename T, typename T1, typename... T_rest>
constexpr typename std::enable_if_t<!std::is_same<T, T1>::value, T&>
get(Tuple<T1, T_rest...>& tuple) {
    return get<T>(*static_cast<Tuple<T_rest...>*>(&tuple));
}


template<typename T, typename T1, typename... T_rest>
constexpr typename std::enable_if_t<std::is_same<T, T1>::value, T>
get(Tuple<T1, T_rest...>&& tuple) {
    return std::move(tuple._value);
}
template<typename T, typename T1, typename... T_rest>
constexpr typename std::enable_if_t<!std::is_same<T, T1>::value, T>
get(Tuple<T1, T_rest...>&& tuple) {
    return get<T>(std::move(*static_cast<Tuple<T_rest...>*>(&tuple)));
}

// tuple comparison

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator<(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other) {
    return _implementation::tupleComparator::_less(first, other);
}

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator==(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other) {
    return _implementation::tupleComparator::_equal(first, other);
}

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator!=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other) {
    return !_implementation::tupleComparator::_equal(first, other);
}

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator<=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other) {
    return _implementation::tupleComparator::_equal(first, other) || _implementation::tupleComparator::_less(first, other);
}

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator>(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other) {
    return !_implementation::tupleComparator::_equal(first, other) && !_implementation::tupleComparator::_less(first, other);
}

template<typename U1, typename... U1_rest, typename U2, typename... U2_rest>
constexpr bool operator>=(const Tuple<U1, U1_rest...>& first, const Tuple<U2, U2_rest...>& other) {
    return !_implementation::tupleComparator::_less(first, other);
}