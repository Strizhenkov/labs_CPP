#include <iostream>

class polynomial {
private:
    const int p_size;
    const int *p_numbers;

    constexpr int pow(const int x, const int y) const {
        return y == 0 ? 1 : x * pow(x, y - 1);
    }

    constexpr int count(const int point, const int pos) const {
        return pos == 0 ? 0 : p_numbers[p_size - pos] * pow(point, p_size - pos) + count(point, pos - 1);
    }

public:
    constexpr polynomial(const int size, const int *numbers) : p_size(size), p_numbers(numbers) {}

    constexpr int solve(const int point) const {
        return count(point, p_size);
    }

    friend std::ostream &operator<<(std::ostream &answer, polynomial p) {
        answer << "f(x) = ";
        if (p.p_size > 1) {
            for (int i = p.p_size - 1; i > 1; i--)
                if (p.p_numbers[i] > 1 )
                    answer << p.p_numbers[i] << "x^" << i << " + ";
                else if (p.p_numbers[i] == 1)
                    answer << "x^" << i << " + ";
            answer << p.p_numbers[1] << "x + " << p.p_numbers[0];
        } else
            answer << p.p_numbers[0];
        return answer;
    }
};