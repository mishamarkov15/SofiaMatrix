#include <iostream>
#include "matrix.h"

int main() {
    linalg::Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    linalg::Matrix m2 = {{9, 4, 8}, {7, 0, 1}, {6, 7, 4}};
    m1 += m2;
    m1.show();
    return 0;
}
