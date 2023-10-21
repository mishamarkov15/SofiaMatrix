#include <iostream>
#include "matrix.h"

int main() {
    linalg::Matrix m1 = {{6, -7, 4}, {0, 3, 9}, {8, -2, 4}};
    std::cout << linalg::invert(m1);
    return 0;
}
