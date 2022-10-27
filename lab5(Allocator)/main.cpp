#include <cstdlib>
#include <iostream>
#include <string>

#define MEMORY 100

template <class T>

class linear_allocator {
    typedef T value_type;

private:
    T* data;
    bool used[MEMORY / sizeof(T)]{};

public:
    linear_allocator() {
        data = (T*)malloc(MEMORY);
        for (bool &elem : used) {
            elem = false;
        }
    }

    void allocate(int k) {
        if (MEMORY >= sizeof(T) * k) {
            for (int i = 0; i <= MEMORY / sizeof(T) - k; i++) {
                int flag = 0;
                for (int j = i; j < i + k; j++) {
                    if (!used[j]) {
                        flag++;
                    }
                }
                if (flag == k) {
                    for (int j = i; j < i + k; j++) {
                        used[j] = true;
                    }
                    std::cout << k << " memory sells with size " << sizeof(T) << " were allocated from " << data + i
                              << " to " << data + i + k << '\n';
                    break;
                }
            }
        } else {
            std::cout << "Allocator have not enough memory";
        }
    }

    void deallocate(T *pos, int k) {
        for (int j = pos - data; j < pos - data + k * sizeof(T); j++) {
            used[j] = false;
        }
        std::cout << "Memory sells from " << pos << " to " << pos + k << " are now free\n";
    }
};

//0 - Выход
//1 - (k) - Выдача k ячеек (выбранного типа данных у аллокатора)
//2 - (адрес k) - Освобождение k ячеек с заданного адреса

int main() {
    typedef short T;
    linear_allocator<T> a;
    int key; int k; std::string num;
    while (true) {
        std::cin >> key;
        if (key == 0) {
            return 0;
        } else if (key == 1) {
            std::cin >> k;
            a.allocate(k);
        } else if (key == 2) {
            std::cin >> num >> k;
            long long add_int = std::stoull(num, nullptr, 16);
            T* add = reinterpret_cast<T*>(add_int);
            a.deallocate(add, k);
        }
    }
}
