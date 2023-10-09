#include <iostream>

namespace linalg {
// TODO: std::initializer_list
    class Matrix {
    public:
        Matrix();

        explicit Matrix(size_t rows, size_t cols = 1);

//        Matrix(double **matrix, size_t rows, size_t cols);

        Matrix(const Matrix &other); // copy-constructor

        Matrix(const Matrix &&other); // Разобрать

        ~Matrix();

        Matrix &operator=(const Matrix &other); // Не делали

        Matrix &operator=(const Matrix &&other); // move operator=

    private:
        double *m_ptr;
        // TODO: переделать под capacity
        size_t m_rows; // unsigned long long int: 0...18 000 000 000 000 000 000
        size_t m_cols;
    };

    Matrix::Matrix() : m_ptr(nullptr), m_rows(0), m_cols(0) {}

    Matrix::Matrix(size_t rows, size_t cols) : m_ptr(new double[rows * cols]), m_rows(rows), m_cols(cols) {}

//    Matrix::Matrix(double **matrix, size_t rows, size_t cols) : m_ptr(new double [rows * cols]), m_rows(rows), m_cols(cols) {
//        size_t curr_index = 0;
//        for (size_t i = 0; i < rows; ++i) {
//            for (size_t j = 0; j < cols; ++j) {
//                m_ptr[curr_index] = matrix[i][j];
//                ++curr_index;
//            }
//        }
//    }

    Matrix::~Matrix() {
        delete[] m_ptr;
    }

    Matrix::Matrix(const Matrix &other) {
        m_rows = other.m_rows;
        m_cols = other.m_cols;

        m_ptr = new double [m_rows * m_cols];
        for (size_t i = 0; i < m_rows * m_cols; ++i) {
                m_ptr[i] = other.m_ptr[i];
        }
    }

    Matrix &Matrix::operator=(const Matrix &other) {
        delete [] m_ptr;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_ptr = new double [m_rows * m_cols];
        for (size_t i = 0; i < m_rows * m_cols; ++i) {
            m_ptr[i] = other.m_ptr[i];
        }
        return *this;
    }
}

int main() {
    return 0;
}
