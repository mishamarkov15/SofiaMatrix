#include <iostream>

// TODO: std::initializer_list
class Matrix {
public:
    Matrix();

    explicit Matrix(size_t rows, size_t cols = 1);

    Matrix(double **matrix, size_t rows, size_t cols);

    Matrix(const Matrix &other); // copy-constructor

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

Matrix::Matrix(double **matrix, size_t rows, size_t cols) :  m_ptr(new double *[rows]), m_rows(rows), m_cols(cols) {
    for (size_t i = 0; i < rows; ++i) {
        m_ptr[i] = new double[cols];
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            m_ptr[i][j] = matrix[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (size_t i = 0; i < m_rows; ++i) {
        delete [] m_ptr[i];
    }
    delete [] m_ptr;
}

Matrix::Matrix(const Matrix &other) {
    m_rows = other.m_rows;
    m_cols = other.m_cols;

    m_ptr = new double*[m_rows];
    for (size_t i = 0; i < m_rows; ++i) {
        m_ptr[i] = new double[m_cols];
    }

    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_cols; ++j) {
            m_ptr[i][j] = other.m_ptr[i][j];
        }
    }
}


int main() {
    Matrix m1(3, 3);
    std::cout << "some code...\n";
    Matrix m2(m1);
    return 0;
}
