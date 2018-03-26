/**
template<size_t N, typename... Rest>
class Tuple;


template<size_t N, typename First, typename... Rest>
class Tuple<N, First, Rest...>:
        public Tuple<N - 1, Rest...> {
private:
    First _value;
public:
    Tuple(): _value() {
        std::cout << "ntuple" << std::endl;
    }
};

template<>
class Tuple<0> {
public:
    Tuple() {
        std::cout << "0tuple" << std::endl;
    }
};
**/

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

    Tuple(const T1& value, T_rest args...): _value(value), Tuple<T_rest...>(args...) {}
};

template<>
class Tuple<> {
public:
    Tuple() {
        std::cout << "0tuple" << std::endl;
    }
};