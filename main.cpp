#include <iostream>

// TODO: std::initializer_list
class Matrix {
public:
    Matrix();

    Matrix(size_t rows, size_t cols = 1);

    Matrix(double **matrix, size_t rows, size_t cols);

    Matrix(const Matrix &other); // Разобрать

    Matrix(const Matrix &&other); // Разобрать

    ~Matrix();

    Matrix &operator=(const Matrix &other); // Не делали

    Matrix &operator=(const Matrix &&other); // move operator=

private:
    double **m_ptr;
    size_t m_rows; // unsigned long long int: 0...18 000 000 000 000 000 000
    size_t m_cols;
};

Matrix::Matrix() : m_ptr(nullptr), m_rows(0), m_cols(0) {}

Matrix::Matrix(size_t rows, size_t cols) : m_ptr(new double *[rows]), m_rows(rows), m_cols(cols)  {
    for (size_t i = 0; i < rows; ++i) {
        m_ptr[i] = new double[cols];
    }
}

int main() {
    int* data = new int[1000000];
    delete [] data;
    return 0;
}
