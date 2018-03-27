#include <iostream>
#include "tuple.h"
#include <tuple>
#include <typeinfo>
#include <vector>

/**
template<class T>
class TupleHelper{
    std::string st;
public:
    TupleHelper() {
        st = "You are so kek! ";
        st += std::string(typeid(T).name()) + '\n';
    }
    friend std::ostream& operator<<(std::ostream& os, const TupleHelper& t) {
        os << t.st;
        return os;
    }
};

int main() {
    Tuple<int, double, int> keker(10, 5.1, 105);
    Tuple<int, double, int> keker2(3, 1.2, 4);
    print(keker2);
    keker2 = keker;
    print(keker2);
    Tuple<int, double, int> keker3(keker2);
    print(keker3);
    return 0;
}



int main() {
    std::tuple<int, double> tp(3, 5);
    std::tuple<int, double> tp2(4, 6);
    tp.swap(tp2);
    std::cout << std::get<0>(tp) << ' ' << std::get<1>(tp) << std::endl;
    std::cout << std::get<0>(tp2) << ' ' << std::get<1>(tp2) << std::endl;

    Tuple<int, double> kek(3, 5);
    Tuple<int, double> kek2(4, 6);
    print(kek);
    print(kek2);
//    kek.swap(kek2);
//    print(kek);
//    print(kek2);
}

**/

int main() {
//    std::tuple<int, double, double, double> recognizer;
//    std::cout << std::get<3>(recognizer);
    auto kek = makeTuple(5, 4, 3, 2, 1);
    std::cout << get(3, kek) << std::endl;
    return 0;
}