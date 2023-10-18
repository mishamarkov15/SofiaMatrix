#include "matrix.h"

namespace linalg {
    Matrix::Matrix() : m_ptr(nullptr), m_rows(0), m_cols(0), m_capacity(0) {}

    Matrix::Matrix(size_t rows, size_t cols) : m_ptr(nullptr), m_rows(rows), m_cols(cols),
                                               m_capacity(pow(2, ceil(log2(rows * cols)))) {
        m_ptr = new double[m_capacity];
    }

    Matrix::~Matrix() {
        delete[] m_ptr;
    }

    Matrix::Matrix(const Matrix &other) {
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_capacity = other.m_capacity;

        m_ptr = new double[m_capacity];
        for (size_t i = 0; i < m_rows * m_cols; ++i) {
            m_ptr[i] = other.m_ptr[i];
        }
    }

    Matrix &Matrix::operator=(const Matrix &other) {
        if (&other == this) {
            return *this;
        }
        delete[] m_ptr;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_capacity = other.m_capacity;
        m_ptr = new double[m_capacity];
        for (size_t i = 0; i < m_rows * m_cols; ++i) {
            m_ptr[i] = other.m_ptr[i];
        }
        return *this;
    }

    Matrix::Matrix(const std::initializer_list<std::initializer_list<double>> &list) :
            m_ptr(nullptr),
            m_rows(list.size()),
            m_cols(list.begin()->size()) {
        m_capacity = pow(2, ceil(log2(m_rows * m_cols)));
        m_ptr = new double [m_capacity];
        int k = 0;
        for (const auto& line : list) {
            for (const auto& x : line) {
                m_ptr[k++] = x;
            }
        }
    }

    // TODO: переделать под std::ostream
    void Matrix::show() const {
        for (size_t i = 0, k = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < m_cols; ++j) {
                std::cout << m_ptr[k++] << ' ';
            }
            std::cout << '\n';
        }
    }

    Matrix &Matrix::operator+=(const Matrix &other) {
        if (m_rows != other.m_rows || m_cols != other.m_cols) {
            throw std::runtime_error("Нельзя складывать матрицы разных размеров");
        }
        for (size_t i = 0; i < m_cols * m_rows; ++i) {
            m_ptr[i] += other.m_ptr[i];
        }
        return *this;
    }

    Matrix Matrix::operator+(const Matrix &other) const {
        if (m_rows != other.m_rows || m_cols != other.m_cols) {
            throw std::runtime_error("Нельзя складывать матрицы разных размеров");
        }
        Matrix res(*this);
        res += other;
        return res;
    }

    Matrix &Matrix::operator-=(const Matrix &other) {
        if (m_rows != other.m_rows || m_cols != other.m_cols) {
            throw std::runtime_error("Нельзя вычитать матрицы разных размеров");
        }
        for (size_t i = 0; i < m_cols * m_rows; ++i) {
            m_ptr[i] -= other.m_ptr[i];
        }
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other) const {
        if (m_rows != other.m_rows || m_cols != other.m_cols) {
            throw std::runtime_error("Нельзя вычитать матрицы разных размеров");
        }
        Matrix res(*this);
        res -= other;
        return res;
    }

    Matrix &Matrix::operator*=(const Matrix &other) {
        if (m_cols != other.m_rows) {
            throw std::runtime_error("Матрицы не совместимые");
        }
        double* res = new double[m_rows * other.m_cols]{};
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < other.m_cols; ++j) {
                for (size_t k = 0; k < m_cols; ++k) {
                    res[i * m_rows + j] += m_ptr[i * m_rows + k] * other.m_ptr[k * other.m_rows + j];
                }
            }
        }
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < other.m_cols; ++j) {
                std::cout << m_ptr[i * m_cols + j] << ' ';
            }
            std::cout << '\n';
        }
    }
}