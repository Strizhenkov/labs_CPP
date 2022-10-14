#include <iostream>
#include <polynomial.h>

using namespace std;

int main() {
    constexpr int value = 3;
    constexpr int size = 3;
    constexpr int array[] = {10, 20, 1};


    cout << polynomial(size, array) << '\n';
    constexpr int res = polynomial(size, array).solve(value);
    cout << "f(" << value << ") = " << res;
}
