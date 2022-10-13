#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

class point {
private:
    double x_;
    double y_;

public:
    point() {
        x_ = 0;
        y_ = 0;
    }

    double x() const {
        return x_;
    }
    double y() const {
        return y_;
    }

    void print() const {
        cout << x_ << " " << y_;
    }

    point(double x, double y) : x_(x), y_(y) {}

    point(point &copy) {
        x_ = copy.x_;
        y_ = copy.y_;
    }

    point &operator=(const point &copy) = default;

    double distance(point &second_point) const {
        return sqrt(pow((x_ - second_point.x_), 2) + pow((y_ - second_point.y_), 2));
    }
};

class polyline {
protected:
    int size_;
    point dots[1000];

public:
    polyline() {
        size_ = 0;
    }

    polyline(int size, point input_dots[]) {
        size_ = size;
        for (int i = 0; i < size; i++) {
            dots[i] = input_dots[i];
        }
    }

    polyline(polyline &copy) {
        size_ = copy.size_;
        for (int i = 0; i < size_; i++) {
            dots[i] = copy.dots[i];
        }
    }

    polyline &operator=(const polyline &copy) {
        size_ = copy.size_;
        for (int i = 0; i < size_; i++) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }

    void print_size() const {
        cout << size_;
    }

    void print_dots() const {
        for (int i = 0; i < size_; i++) {
            dots[i].print();
            cout << "\n";
        }
    }

    double length() {
        double ans = 0;
        for (int i = 0; i < size_ - 1; i++) {
            ans += dots[i].distance(dots[i + 1]);
        }
        return ans;
    }
};

class closed_polyline : public polyline {
public:
    closed_polyline () {
        size_ = 0;
    }

    closed_polyline(int size, point input_dots[]) {
        size_ = size;
        if (size_ < 2) {
            exit(1);
        }
        for (int i = 0; i < size_; i++) {
            dots[i] = input_dots[i];
        }
    }

    closed_polyline(closed_polyline &copy) {
        size_ = copy.size_;
        for (int i = 0; i < size_; ++i) {
            dots[i] = copy.dots[i];
        }
    }

    closed_polyline &operator=(const closed_polyline &copy) {
        size_ = copy.size_;
        for (int i = 0; i < size_; ++i) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }

    double perimeter() {
        double ans = 0;
        for (int i = 0; i < size_ - 1; i++) {
            ans += dots[i].distance(dots[i + 1]);
        }
        ans += dots[size_ - 1].distance(dots[0]);
        return ans;
    }
};

class polygon : public closed_polyline {
public:
    polygon() {
        size_ = 0;
    }

    polygon(int size, point input_dots[]) {
        size_ = size;
        if (size_ < 3) {
            exit(1);
        }
        for (int i = 0; i < size_; i++) {
            dots[i] = input_dots[i];
        }

    }

    polygon(polygon &copy) {
        size_ = copy.size_;
        for (int i = 0; i < size_; i++) {
            dots[i] = copy.dots[i];
        }
    }

    polygon &operator=(const polygon &copy) {
        size_ = copy.size_;
        for (int i = 0; i < size_; i++) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }
};

class triangle : public polygon {
public:
    triangle() {
        size_ = 0;
    }

    triangle(point input_dots[]) {
        size_ = 3;
        for (int i = 0; i < 3; i++) {
            dots[i] = input_dots[i];
        }
    }

    triangle(triangle &copy) {
        size_ = copy.size_;
        for (int i = 0; i < 3; i++) {
            dots[i] = copy.dots[i];
        }
    }

    triangle &operator=(triangle &copy) {
        size_ = copy.size_;
        for (int i = 0; i < 3; i++) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }

    double area() {
        double ans = 0;
        double side1 = dots[0].distance(dots[1]);
        double side2 = dots[1].distance(dots[2]);
        double side3 = dots[2].distance(dots[0]);
        double half_perimeter = (side1 + side2 + side3) / 2;
        ans = sqrt(half_perimeter * (half_perimeter - side1) * (half_perimeter - side2) * (half_perimeter - side3));
        return ans;
    }
};
class trapezoid : public polygon {
protected:
    static bool check_grounds(point p1, point p2, point p3, point p4){
        double ground1x = p1.x() - p2.x();
        double ground2x = p3.x() - p3.x();
        double ground1y = p1.y() - p2.y();
        double ground2y = p3.y() - p4.y();
        if ((ground1x * ground2x + ground1y * ground2y) / (sqrt(pow(ground1x, 2) + sqrt(pow(ground1y,2))) * (pow(ground1x, 2) + sqrt(pow(ground1y,2)))) == -1) {
            return true;
        }
        else {
            return false;
        }
    }
public:
    trapezoid() {
        size_ = 0;
    }

    trapezoid(point input_dots[]) {
        size_ = 4;
        for (int i = 0; i < 4; i++) {
            dots[i] = input_dots[i];
        }
        if (!check_grounds(dots[0], dots[1], dots[2], dots[3])) {
            exit(2);
        }
    }

    trapezoid(trapezoid &copy) {
        size_ = copy.size_;
        for (int i = 0; i < 4; i++) {
            dots[i] = copy.dots[i];
        }
    }

    trapezoid &operator=(trapezoid &copy) {
        size_ = copy.size_;
        for (int i = 0; i < 4; i++) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }

    double area() {
        double ans = 0;
        double side1 = dots[0].distance(dots[1]);
        double side2 = dots[1].distance(dots[2]);
        double side3 = dots[2].distance(dots[3]);
        double side4 = dots[3].distance(dots[0]);
        double half_perimeter = (side1 + side2 + side3 + side4) / 2;
        ans = sqrt((half_perimeter - side4) * (half_perimeter - side1) * (half_perimeter - side2) * (half_perimeter - side3));
        return ans;
    }
};

class regular_polygon : public polygon {
public:
    regular_polygon() {
        size_ = 0;
    }

    regular_polygon(int size, point input_dots[]) {
        size_ = size;
        for (int i = 0; i < size; i++) {
            dots[i] = input_dots[i];
        }
    }

    regular_polygon(regular_polygon &copy) {
        size_ = copy.size_;
        for (int i = 0; i < size_; ++i) {
            dots[i] = copy.dots[i];
        }
    }

    regular_polygon &operator=(const regular_polygon &copy) {
        size_ = copy.size_;
        for (int i = 0; i < size_; ++i) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }

    double area() {
        double ans = 0;
        double side = dots[0].distance(dots[1]);
        ans = size_ * pow(side, 2) * (1 / tan(3.141592653589793 / size_)) / 4;
        return  ans;
    }
};

class polynomial {
private:
    vector<double> coefficients;

public:
    polynomial() {
        coefficients.push_back(0);
    }

    double &operator[](int index) {
        return coefficients[index];
    }

    void print() {
        unsigned int cur_pow = coefficients.size() - 1;
        for (double &coefficient : coefficients) {
            if (coefficient != 0) {
                if (cur_pow > 1) {
                    cout << check(coefficient) << abs(coefficient) << "x^" << cur_pow;
                } else if (cur_pow == 1) {
                    cout << check(coefficient) << abs(coefficient) << 'x';

                } else {
                    cout << check(coefficient) << abs(coefficient);
                }
            }
            cur_pow--;
        }
        std::cout << '\n';
    }

    static char check (double x) {
        if (x > 0) {
            return '+';
        } else {
            return '-';
        }
    }

    polynomial(const vector<int> &input_numbers) {
        for (int input_coefficient: input_numbers) {
            coefficients.push_back(input_coefficient);
        }
    }

    polynomial &operator=(const polynomial &copy) {
        coefficients = copy.coefficients;
        return *this;
    }

    ~polynomial() = default;

    bool operator==(polynomial &second_polynomial) {
        return (coefficients == second_polynomial.coefficients);
    }

    bool operator!=(polynomial &second_polynomial) {
        return !(coefficients == second_polynomial.coefficients);
    }

    polynomial &operator*(int number) {
        for (double &coefficient: coefficients) {
            coefficient *= number;
        }
        return *this;
    };

    polynomial &operator*=(int number) {
        for (double &coefficient: coefficients) {
            coefficient *= number;
        }
        return *this;
    };


    polynomial &operator/(int number) {
        for (double &coefficient: coefficients) {
            coefficient *= number;
        }
        return *this;
    };

    polynomial &operator/=(int number) {
        for (double &coefficient: coefficients) {
            coefficient *= number;
        }
        return *this;
    };

    polynomial &operator+(const polynomial &another_pol) {
        if (coefficients.size() > another_pol.coefficients.size()) {
            for (int i = 0; i < another_pol.coefficients.size(); i++) {
                coefficients[i + coefficients.size() - another_pol.coefficients.size()] += another_pol.coefficients[i];
            }
        } else {
            for (int i = 0; i < coefficients.size(); i++) {
                coefficients[i] += another_pol.coefficients[i];
            }
        }
        return *this;
    }

    polynomial &operator+=(const polynomial &another_pol) {
        if (coefficients.size() > another_pol.coefficients.size()) {
            for (int i = 0; i < another_pol.coefficients.size(); i++) {
                coefficients[i + coefficients.size() - another_pol.coefficients.size()] += another_pol.coefficients[i];
            }
        } else {
            for (int i = 0; i < coefficients.size(); i++) {
                coefficients[i] += another_pol.coefficients[i];
            }
        }
        return *this;
    }

    polynomial &operator-(const polynomial &another_pol) {
        for (int i = 0; i < another_pol.coefficients.size(); i++) {
            coefficients[i + coefficients.size() - another_pol.coefficients.size()] -= another_pol.coefficients[i];
        }
        return *this;
    }

    polynomial &operator-=(const polynomial &another_pol) {
        for (int i = 0; i < another_pol.coefficients.size(); i++) {
            coefficients[i + coefficients.size() - another_pol.coefficients.size()] -= another_pol.coefficients[i];
        }
        return *this;
    }

    polynomial &operator<<(int k) {
        for (int i = 0; i < k; i++) {
            coefficients.push_back(0);
        }
        return *this;
    };

    polynomial &operator>>(int k) {
        for (int i = 0; i < k; i++) {
            coefficients.pop_back();
        }
        return *this;
    }
};

// Список ошибок
// 1 - Дано недостаточно точек
// 2 - У трапеции не паралельные стороны

int main() {
    point p1;
    vector<int> array1, array2;
    array1.push_back(-1);
    array1.push_back(2);
    array1.push_back(8);
    array1.push_back(2);
    array2.push_back(7);
    array2.push_back(2);
    array2.push_back(3);
    polynomial pol1(array1);
    polynomial pol2(array2);
    pol1.print();
    pol2.print();
    pol1 -= pol2;
    pol1.print();
}