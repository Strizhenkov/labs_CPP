#include <iostream>
#include <vector>

template<typename T>
class round_buffer {
protected:
    T *data_;
    size_t end_, start_, start_cup, end_cup;

public:
    explicit round_buffer(size_t size, const T &value = 0)
    : data_(new T[100 + size + 100]), end_(100 + size - 1), start_(100), start_cup(0), end_cup(size + 200) {
        for (size_t i = start_; i <= end_; i++)
            data_[i] = value;
    }

    ~round_buffer() {
        delete[] data_;
    }

    round_buffer &operator=(round_buffer const &second) {
        if (&second != this) {
            start_ = second.start_;
            end_ = second.end_;
            start_cup = second.start_cup;
            end_cup = second.end_cup;
            data_ = new T[second.end_cup];
            std::cout << start_ << ' ' << end_ << ' ' << start_cup << ' ' << end_cup << '\n';
            for (size_t i = second.start_cup; i < second.end_cup; i++)
                data_[i] = second.data_[i];
        }
        return *this;
    }

    size_t size() {
        return end_ - start_ + 1;
    }

    void show() {
        for (size_t i = start_; i <= end_; i++) {
            std::cout << data_[i] << ' ';
        }
        std::cout << '\n';
    }

    T &operator[](size_t pos) {
        return data_[pos + start_];
    }

    void add_end(const T &value) {
        if (start_ != end_) {
            end_++;
        }
        data_[end_] = value;
        if (end_cup - end_ < 10) {
            resize();
        }
    }

    void add_start(const T &value) {
        if (start_ != end_) {
            start_--;
        }
        data_[start_] = value;
        if (start_ - start_cup < 10) {
            resize();
        }
    }

    void pop_end() {
        data_[end_] = 0;
        if (start_ != end_) {
            end_--;
        }
    }

    void pop_start() {
        data_[start_] = 0;
        if (start_ != end_) {
            start_++;
        }
    }

    class Iterator {
    public:
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr, pointer ptrEnd, pointer ptrStart) :
                ptr_(ptr), ptrEnd_(ptrEnd), ptrStart_(ptrStart) {}

        reference operator*() const {
            return *ptr_;
        }

        Iterator &operator++() {
            ptr_++;
            if (ptr_ == ptrEnd_) {
                ptr_ = ptrStart_;
            }
            return *this;
        }

        Iterator operator++(int) {
            return ++(*this);
        }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.ptr_ == b.ptr_;
        };
        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.ptr_ != b.ptr_;
        };

    private:
        pointer ptr_;
        pointer ptrEnd_, ptrStart_;
    };

    Iterator begin() {
        return Iterator(&data_[start_], &data_[end_ - start_ + 1], &data_[0]);
    }

    Iterator end() {
        return Iterator(&data_[end_ + 1], &data_[end_ - start_ + 1], &data_[0]);
    }

    void resize() {
        T *new_data_ = new T[100 + end_cup + 100];
        start_ += 100;
        end_ += 100;
        end_cup += 200;
        for (size_t i = start_; i <= end_; i++) {
            new_data_[i] = data_[i - 100];
        }
        delete[] data_;
        data_ = new T[100 + end_cup + 100];
        for (size_t i = start_cup; i < end_cup; i++) {
            data_[i] = new_data_[i];
        }
    }
};

bool my_pred(int x) {
    return x < 5;
}

bool group_pred(int x) {
    return (x < 10 || x > 15);
}

void bool_show(bool b) {
    if (b) {
        std::cout << "True\n";
    } else {
        std::cout << "False\n";
    }
}

template<typename T, typename Pred>
bool all_of(T begin, T end, Pred pred) {
    while (begin != end) {
        std::cout << *begin << '\n';
        if (!pred(*begin)) {
            return false;
        }
        begin++;
    }
    return true;
}

template<typename T, typename Pred>
bool any_of(T begin, T end, Pred pred) {
    while (begin != end) {
        if (pred(*begin)) {
            return true;
        }
        begin++;
    }
    return false;
}

template<typename T, typename Pred>
bool none_of(T begin, T end, Pred pred) {
    while (begin != end) {
        if (pred(*begin)) {
            return false;
        }
        begin++;
    }
    return true;
}

template<typename T, typename Pred>
bool one_of(T begin, T end, Pred pred) {
    int flag = 0;
    while (begin != end) {
        if (pred(*begin)) {
            flag++;
        }
        begin++;
    }
    if (flag == 1)
        return true;
    else
        return false;
}

template<typename T>
bool is_sorted(T begin, T end, char c) {
    if (c == '>') {
        while (begin++ != end) {
            if (*begin <= *(begin++)) {
                return false;
            }
            begin++;
        }
    } else {
        while (begin++ != end) {
            if (*begin >= *(begin++)) {
                return false;
            }
            begin++;
        }
    }
    return true;
}

template<typename T, typename Pred>
bool is_partitioned(T begin, T end, Pred pred) {
    while (begin != end) {
        if (!pred(*begin)) {
            return false;
        }
        begin++;
    }
    return true;
}

template<typename T, typename U>
int find_not(T begin, T end, const U &value) {
    int flag = 0;
    while (begin != end) {
        if (*begin != value) {
            return flag;
        }
        begin++;
        flag++;
    }
    return -1;
}

template<typename T, typename U>
int find_backwards(T &array, const U &element) {
    int flag = -1; int count = 0;
    for (auto elem : array) {
        if (elem == element) {
            flag = count;
        }
        count++;
    }
    return flag;
}

int main() {
    round_buffer<int> buffer(1, 25);
    buffer.add_end(89);
    buffer.add_end(110);
    bool_show(is_sorted(buffer.begin(), buffer.end(), '>'));
    std::cout << buffer.size();
}