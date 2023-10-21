#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>

namespace linalg {
    const double EPSILON = 0.0000001;

    class Matrix {
    public:
        Matrix();  // Конструктор по умолчанию

        Matrix(const std::initializer_list<std::initializer_list<double>> &list);  // Конструктор от списка инициализации

        explicit Matrix(size_t rows, size_t cols = 1);  // Конструктор от двух чисел

        Matrix(const Matrix &other); // copy-constructor

        Matrix(Matrix &&other); // Разобрать

        ~Matrix();

        Matrix &operator=(const Matrix &other); // Не делали

        Matrix &operator=(Matrix &&other); // move operator=

        Matrix &operator+=(const Matrix &other);

        const Matrix operator+(const Matrix &other) const;

        Matrix &operator-=(const Matrix &other);

        const Matrix operator-(const Matrix &other) const;

        Matrix &operator*=(const Matrix &other);

        const Matrix operator*(const Matrix &other) const;

        Matrix &operator*=(double other);

        const Matrix operator*(double other) const;

        const Matrix operator-() const noexcept;

        bool operator==(const Matrix &other) const noexcept;

        bool operator!=(const Matrix &other) const noexcept;

        double &operator()(size_t i, size_t j);

        const double &operator()(size_t i, size_t j) const;

        size_t rows() const noexcept;

        size_t cols() const noexcept;

        double trace() const;

        double det() const;

        int rank() const;

        double norm() const;

        Matrix& gauss_forward();

        Matrix& gauss_backward();

        const Matrix getMinor(size_t row, size_t col) const;

        friend std::ostream& operator<<(std::ostream& out, const Matrix& rhs);

    private:

        int findMaxLengthNumber() const noexcept;

        double *m_ptr;
        size_t m_capacity;
        size_t m_rows;
        size_t m_cols;
    };

    Matrix getCofactor(const Matrix& vect);

    Matrix invert(const Matrix& rhs);

    Matrix transpose(const Matrix& rhs) noexcept;

    Matrix power(const Matrix& lhs, int rhs) noexcept;

    int rankOfMatrix(double *mat, size_t R, size_t C);

    void swap(double *mat, size_t row1, size_t row2, size_t col);

    bool areSame(double a, double b);

    int digitsCount(double number);

    const Matrix operator*(double lhs, const Matrix &rhs);
}

#endif // MATRIX_H