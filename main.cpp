#include <iostream>
#include "matrix.h"

int main() {
    linalg::Matrix m1 = {{6, -7}, {0, 3}};
    linalg::Matrix m2 = {{1, 2}, {6, 9}};
    std::cout << linalg::power(m1, 3);

    return 0;
}
