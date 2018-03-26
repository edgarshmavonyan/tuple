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

