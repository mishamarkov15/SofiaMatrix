#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

namespace linalg {
// TODO: noexcept
    class Matrix {
    public:
        Matrix();

        Matrix(const std::initializer_list<std::initializer_list<double>> &list);

        explicit Matrix(size_t rows, size_t cols = 1);

        Matrix(const Matrix &other); // copy-constructor

        Matrix(const Matrix &&other); // Разобрать

        void push_back(double value);

        void show() const;

        ~Matrix();

        Matrix &operator=(const Matrix &other); // Не делали

        Matrix &operator=(const Matrix &&other); // move operator=

        Matrix &operator+=(const Matrix& other);

        Matrix operator+(const Matrix& other) const;

        Matrix &operator-=(const Matrix& other);

        Matrix operator-(const Matrix& other) const;

    private:
        double *m_ptr;
        size_t m_capacity;
        size_t m_rows;
        size_t m_cols;
    };
}

#endif MATRIX_H