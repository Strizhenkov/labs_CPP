#include <gtest/gtest.h>
#include "polynomial.h"

TEST(tests, threeElements) {
    const int size = 3;
    constexpr int vec1[] = {1,1,1};
    constexpr int vec2[] = {1,2,3};
    constexpr int vec3[] = {10,20,33};
    EXPECT_EQ(polynomial(size, vec1).solve(1), 3);
    EXPECT_EQ(polynomial(size, vec2).solve(2), 17);
    EXPECT_EQ(polynomial(size, vec3).solve(3), 367);
}