#include <iostream>
#include "matrix.h"

int main() {
    linalg::Matrix m1 = {{1, 2},
                         {3, 4}};
    m1(1, 0) *= 2;

    const linalg::Matrix m2 = {{1, 2}, {3, 4}};
    std::cout << m2(0, 0);
    return 0;
}
