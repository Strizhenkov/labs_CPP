#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>

void swap(unsigned int* x, unsigned int* y) {
    unsigned int z = *x;
    *x = *y;
    *y = z;
}

void remake(unsigned int *x, int y) {
    *x = y;
}

class side {
private:
   unsigned int side_[3][3]{};

public:
    side() {
        side_[0][0] = 0;
        side_[0][1] = 0;
        side_[0][2] = 0;
        side_[1][0] = 0;
        side_[1][1] = 0;
        side_[1][2] = 0;
        side_[2][0] = 0;
        side_[2][1] = 0;
        side_[2][2] = 0;
    }

    auto add(unsigned int i, unsigned int j) {
        return &side_[i - 1][j - 1];
    }

    void show_side() {
        for (auto & i: side_) {
            for (unsigned int j : i) {
                std::cout << j << ' ';
            }
            std::cout << '\n';
        }
    }

    void draw(unsigned int color) {
        for (auto &i : side_) {
            for (unsigned int & j : i) {
                j = color;
            }
        }
    }

    void round_turn() {
        swap(&side_[0][2], &side_[2][2]);
        swap(&side_[0][1], &side_[1][2]);
        swap(&side_[0][0], &side_[0][2]);
        swap(&side_[0][1], &side_[2][1]);
        swap(&side_[0][0], &side_[2][0]);
        swap(&side_[0][1], &side_[1][0]);
    }
};

class cube {
private:
    side sides[6];
    std::vector<unsigned int> history;

public:
    cube() {
        color_side(0, 1);
        color_side(1, 2);
        color_side(2, 3);
        color_side(3, 4);
        color_side(4, 5);
        color_side(5, 6);
    }

    void color_side(unsigned int number, unsigned int color_) {
        sides[number].draw(color_);
    }

    void show_cube() {
        for (int i = 0; i < 6; i++) {
            std::cout << "Side number " << i + 1 << "\n";
            sides[i].show_side();
        }
    }

    void generate() {
        srand(time(nullptr));
        unsigned int x = rand() % 20;
        for (int i = 1; i < x; i++) {
            unsigned int y = rand() % 18;
            history.push_back(y);
            switch (y) {
                case 0:
                    turn_mid1234();
                    history.pop_back();
                    break;
                case 1:
                    back_turn_mid1234();
                    history.pop_back();
                    break;
                case 2:
                    turn_mid1536();
                    history.pop_back();
                    break;
                case 3:
                    back_turn_mid1536();
                    history.pop_back();
                    break;
                case 4:
                    turn_mid2546();
                    history.pop_back();
                    break;
                case 5:
                    back_turn_mid2546();
                    history.pop_back();
                    break;
                case 6:
                    turn_side1();
                    history.pop_back();
                    break;
                case 7:
                    back_turn_side1();
                    history.pop_back();
                    break;
                case 8:
                    turn_side2();
                    history.pop_back();
                    break;
                case 9:
                    back_turn_side2();
                    history.pop_back();
                    break;
                case 10:
                    turn_side3();
                    history.pop_back();
                    break;
                case 11:
                    back_turn_side3();
                    history.pop_back();
                    break;
                case 12:
                    turn_side4();
                    history.pop_back();
                    break;
                case 13:
                    back_turn_side4();
                    history.pop_back();
                    break;
                case 14:
                    turn_side5();
                    history.pop_back();
                    break;
                case 15:
                    back_turn_side5();
                    history.pop_back();
                    break;
                case 16:
                    turn_side6();
                    history.pop_back();
                    break;
                case 17:
                    back_turn_side6();
                    history.pop_back();
                    break;
                default:
                    std::cout << "ERROR\n";
                    break;
            }
        }
    }

    void collect() {
        for (unsigned int elem : history) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
        while (size(history) != 0) {
            switch (history[size(history) - 1]) {
                case 0:
                    back_turn_mid1234();
                    history.pop_back();
                    break;
                case 1:
                    turn_mid1234();
                    history.pop_back();
                    break;
                case 2:
                    back_turn_mid1536();
                    history.pop_back();
                    break;
                case 3:
                    turn_mid1536();
                    history.pop_back();
                    break;
                case 4:
                    back_turn_mid2546();
                    history.pop_back();
                    break;
                case 5:
                    turn_mid2546();
                    history.pop_back();
                    break;
                case 6:
                    back_turn_side1();
                    history.pop_back();
                    break;
                case 7:
                    turn_side1();
                    history.pop_back();
                    break;
                case 8:
                    back_turn_side2();
                    history.pop_back();
                    break;
                case 9:
                    turn_side2();
                    history.pop_back();
                    break;
                case 10:
                    back_turn_side3();
                    history.pop_back();
                    break;
                case 11:
                    turn_side3();
                    history.pop_back();
                    break;
                case 12:
                    back_turn_side4();
                    history.pop_back();
                    break;
                case 13:
                    turn_side4();
                    history.pop_back();
                    break;
                case 14:
                    back_turn_side5();
                    history.pop_back();
                    break;
                case 15:
                    turn_side5();
                    history.pop_back();
                    break;
                case 16:
                    back_turn_side6();
                    history.pop_back();
                    break;
                case 17:
                    turn_side6();
                    history.pop_back();
                    break;
                default:
                    std::cout << "ERROR\n";
                    break;
            }
            history.pop_back();
        }
    }

    bool check_total() {
        int keys[7];
        keys[0] = 9;
        keys[1] = 0; keys[2] = 0; keys[3] = 0;
        keys[4] = 0; keys[5] = 0; keys[6] = 0;
        for (auto cur_side : sides) {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 3; j++) {
                    keys[*cur_side.add(i, j)] += 1;
                }
            }
        }
        if (keys[0] == keys[1] == keys[2] == keys[3] == keys[4] == keys[5] == keys[6]) {
            return true;
        } else {
            return false;
        }
    }

    bool check_pos() {
        for (auto cur_side : sides) {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 3; j++) {
                    if (*cur_side.add(1, 1) != *cur_side.add(i, j)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void read() {
        int n1, n2, n3;
        std::fstream fin(R"(C:\Users\gstri\CLionProjects\cube\cube_status.txt)");
        for (auto & side : sides) {
            for (int j = 0; j < 3; j++) {
                fin >> n1 >> n2 >> n3;
                remake(side.add(j + 1, 1), n1);
                remake(side.add(j + 1, 2), n2);
                remake(side.add(j + 1, 3), n3);
            }
        }
        fin.close();
    }

    void write() {
        std::ofstream fout(R"(C:\Users\gstri\CLionProjects\cube\cube_status.txt)");
        for (auto & side : sides) {
            for (int j = 0; j < 3; j++) {
                fout << *side.add(j + 1, 1) << ' ' << *side.add(j + 1, 2) << ' ' << *side.add(j + 1, 3) << '\n';
            }
        }
        fout.close();
    }

    void turn_mid1234() {
        for (unsigned int i = 1; i <= 3; i++) {
            swap(sides[0].add(2, 1), sides[i].add(2, 1));
            swap(sides[0].add(2, 2), sides[i].add(2, 2));
            swap(sides[0].add(2, 3), sides[i].add(2, 3));
        }
        history.push_back(0);
    }

    void back_turn_mid1234() {
        turn_mid1234();
        turn_mid1234();
        turn_mid1234();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(1);
    }

    void turn_mid1536() {
        swap(sides[0].add(3, 2), sides[4].add(1, 2));
        swap(sides[0].add(2, 2), sides[4].add(2, 2));
        swap(sides[0].add(1, 2), sides[4].add(3, 2));
        swap(sides[0].add(3, 2), sides[2].add(3, 2));
        swap(sides[0].add(2, 2), sides[2].add(2, 2));
        swap(sides[0].add(1, 2), sides[2].add(1, 2));
        swap(sides[0].add(3, 2), sides[5].add(3, 2));
        swap(sides[0].add(2, 2), sides[5].add(2, 2));
        swap(sides[0].add(1, 2), sides[5].add(1, 2));
        history.push_back(2);
    }

    void back_turn_mid1536() {
        turn_mid1536();
        turn_mid1536();
        turn_mid1536();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(3);
    }

    void turn_mid2546() {
        swap(sides[1].add(3, 2), sides[4].add(2, 3));
        swap(sides[1].add(2, 2), sides[4].add(2, 2));
        swap(sides[1].add(1, 2), sides[4].add(2, 1));
        swap(sides[1].add(3, 2), sides[3].add(1, 2));
        swap(sides[1].add(2, 2), sides[3].add(2, 2));
        swap(sides[1].add(1, 2), sides[3].add(3, 2));
        swap(sides[1].add(3, 2), sides[5].add(2, 3));
        swap(sides[1].add(2, 2), sides[5].add(2, 2));
        swap(sides[1].add(1, 2), sides[5].add(2, 1));
        history.push_back(4);
    }

    void back_turn_mid2546() {
        turn_mid2546();
        turn_mid2546();
        turn_mid2546();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(5);
    }

    void turn_side1() {
        sides[0].round_turn();
        swap(sides[4].add(3, 1), sides[1].add(1, 1));
        swap(sides[4].add(3, 2), sides[1].add(2, 1));
        swap(sides[4].add(3, 3), sides[1].add(3, 1));
        swap(sides[4].add(3, 1), sides[5].add(1, 3));
        swap(sides[4].add(3, 2), sides[5].add(1, 2));
        swap(sides[4].add(3, 3), sides[5].add(1, 1));
        swap(sides[4].add(3, 1), sides[3].add(3, 3));
        swap(sides[4].add(3, 2), sides[3].add(2, 3));
        swap(sides[4].add(3, 3), sides[3].add(1, 3));
        history.push_back(6);
    }

    void back_turn_side1() {
        turn_side1();
        turn_side1();
        turn_side1();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(7);
    }

    void turn_side2() {
        sides[1].round_turn();
        swap(sides[4].add(1, 3), sides[2].add(1, 1));
        swap(sides[4].add(2, 3), sides[2].add(2, 1));
        swap(sides[4].add(3, 3), sides[2].add(3, 1));
        swap(sides[4].add(1, 3), sides[5].add(3, 3));
        swap(sides[4].add(2, 3), sides[5].add(2, 3));
        swap(sides[4].add(3, 3), sides[5].add(1, 3));
        swap(sides[4].add(1, 3), sides[0].add(3, 3));
        swap(sides[4].add(2, 3), sides[0].add(2, 3));
        swap(sides[4].add(3, 3), sides[0].add(1, 3));
        history.push_back(8);
    }

    void back_turn_side2() {
        turn_side2();
        turn_side2();
        turn_side2();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(9);
    }

    void turn_side3() {
        sides[2].round_turn();
        swap(sides[4].add(1, 1), sides[3].add(1, 1));
        swap(sides[4].add(1, 2), sides[3].add(2, 1));
        swap(sides[4].add(1, 3), sides[3].add(3, 1));
        swap(sides[4].add(1, 1), sides[5].add(1, 1));
        swap(sides[4].add(1, 2), sides[5].add(1, 2));
        swap(sides[4].add(1, 3), sides[5].add(1, 3));
        swap(sides[4].add(1, 1), sides[1].add(3, 3));
        swap(sides[4].add(1, 2), sides[1].add(2, 3));
        swap(sides[4].add(1, 3), sides[1].add(1, 3));
        history.push_back(10);
    }

    void back_turn_side3() {
        turn_side3();
        turn_side3();
        turn_side3();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(11);
    }

    void turn_side4() {
        sides[3].round_turn();
        swap(sides[4].add(1, 1), sides[0].add(1, 1));
        swap(sides[4].add(2, 1), sides[0].add(2, 1));
        swap(sides[4].add(3, 1), sides[0].add(3, 1));
        swap(sides[4].add(1, 1), sides[5].add(1, 1));
        swap(sides[4].add(2, 1), sides[5].add(2, 1));
        swap(sides[4].add(3, 1), sides[5].add(3, 1));
        swap(sides[4].add(1, 1), sides[2].add(3, 3));
        swap(sides[4].add(2, 1), sides[2].add(2, 3));
        swap(sides[4].add(3, 1), sides[2].add(1, 3));
        history.push_back(12);
    }

    void back_turn_side4() {
        turn_side4();
        turn_side4();
        turn_side4();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(13);
    }

    void turn_side5() {
        sides[5].round_turn();
        swap(sides[2].add(1, 3), sides[1].add(1, 3));
        swap(sides[2].add(1, 2), sides[1].add(1, 2));
        swap(sides[2].add(1, 1), sides[1].add(1, 1));
        swap(sides[2].add(1, 3), sides[0].add(1, 3));
        swap(sides[2].add(1, 2), sides[0].add(1, 2));
        swap(sides[2].add(1, 1), sides[0].add(1, 1));
        swap(sides[2].add(1, 3), sides[3].add(1, 3));
        swap(sides[2].add(1, 2), sides[3].add(1, 2));
        swap(sides[2].add(1, 1), sides[3].add(1, 1));
        history.push_back(14);
    }

    void back_turn_side5() {
        turn_side5();
        turn_side5();
        turn_side5();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(15);
    }

    void turn_side6() {
        swap(sides[0].add(3, 3), sides[3].add(3, 3));
        swap(sides[0].add(3, 2), sides[3].add(3, 2));
        swap(sides[0].add(3, 1), sides[3].add(3, 1));
        swap(sides[0].add(3, 3), sides[2].add(3, 3));
        swap(sides[0].add(3, 2), sides[2].add(3, 2));
        swap(sides[0].add(3, 1), sides[2].add(3, 1));
        swap(sides[0].add(3, 3), sides[1].add(3, 3));
        swap(sides[0].add(3, 2), sides[1].add(3, 2));
        swap(sides[0].add(3, 1), sides[1].add(3, 1));
        history.push_back(16);
    }

    void back_turn_side6() {
        turn_side6();
        turn_side6();
        turn_side6();
        history.pop_back();
        history.pop_back();
        history.pop_back();
        history.push_back(17);
    }
};

int main() {
   cube a;
   a.read();
   a.generate();
   a.show_cube();
   a.collect();
   a.show_cube();
   if (a.check_pos() + a.check_total()) {
       std::cout << "Cube is OK\n";
   } else {
       std::cout << "Error in Cube";
   }
}