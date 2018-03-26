#include <iostream>
#include "tuple.h"
#include <tuple>
#include <typeinfo>
#include <vector>

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
//    Tuple<3, int, double, int> keker(2, 5.1, 3);
    Tuple<int, double, int> kek;
//    std::tuple<int, double> kekos(3, 4.2);
//    std::get<0>(kekos);
    return 0;
}