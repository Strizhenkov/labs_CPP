#include <iostream>

using namespace std;

template<typename elem, typename... T>
elem f(elem first, T... array) {
    return first + f(array...);
}

template<typename elem>
elem f(elem value) {
    return value;
}

int main() {
    cout << f(1.125, 3, true);
    return 0;
}