#include <iostream>
#include "matrix.h"

int main() {
    linalg::Matrix m1 = {{1, 2},
                         {3, 4}};
    linalg::Matrix m2 = {{4, 5, 6},
                         {7, 8, 9}};
    auto res = m1 * m2;
    return 0;
}
