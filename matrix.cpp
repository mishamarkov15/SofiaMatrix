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

    Matrix &Matrix::operator=(Matrix &&other) {
        if (this == &other) {
            return *this;
        }
        delete[] m_ptr;
        m_ptr = other.m_ptr;
        m_capacity = other.m_capacity;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        other.m_ptr = nullptr;
        other.m_capacity = 0;
        other.m_rows = 0;
        other.m_cols = 0;
        return *this;
    }

    Matrix::Matrix(const std::initializer_list<std::initializer_list<double>> &list) :
            m_ptr(nullptr),
            m_rows(list.size()),
            m_cols(list.begin()->size()) {
        m_capacity = pow(2, ceil(log2(m_rows * m_cols)));
        m_ptr = new double[m_capacity];
        int k = 0;
        for (const auto &line: list) {
            for (const auto &x: line) {
                m_ptr[k++] = x;
            }
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

    const Matrix Matrix::operator+(const Matrix &other) const {
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

    const Matrix Matrix::operator-(const Matrix &other) const {
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
        size_t new_size = m_rows * other.m_cols;
        size_t new_capacity = pow(2, ceil(log2(new_size)));
        double *res = new double[new_size]{};
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < other.m_cols; ++j) {
                for (size_t k = 0; k < m_cols; ++k) {
                    res[i * other.m_cols + j] += m_ptr[i * m_rows + k] * other.m_ptr[k * other.m_cols + j];
                }
            }
        }
        delete[] m_ptr;
        m_ptr = new double[new_capacity];
        for (size_t i = 0; i < new_size; ++i) {
            m_ptr[i] = res[i];
        }
        delete[] res;
        m_capacity = new_capacity;
        m_cols = other.m_cols;
        return *this;
    }

    const Matrix Matrix::operator*(const Matrix &other) const {
        if (m_cols != other.m_rows) {
            throw std::runtime_error("Матрицы не совместимые");
        }
        Matrix tmp(*this);
        tmp *= other;
        return tmp;
    }

    Matrix &Matrix::operator*=(double other) {
        for (size_t i = 0; i < m_rows * m_cols; ++i) {
            m_ptr[i] *= other;
        }
        return *this;
    }

    const Matrix Matrix::operator*(double other) const {
        Matrix tmp(*this);
        tmp *= other;
        return tmp;
    }

    double &Matrix::operator()(size_t i, size_t j) {
        return m_ptr[i * m_cols + j];
    }

    const double &Matrix::operator()(size_t i, size_t j) const {
        return m_ptr[i * m_cols + j];
    }

    bool Matrix::operator==(const Matrix &other) const noexcept {
        if (m_cols != other.m_cols || m_rows != other.m_rows || m_capacity != other.m_capacity) {
            return false;
        }
        for (size_t i = 0; i < m_rows * m_cols; ++i) {
            if (!areSame(m_ptr[i], other.m_ptr[i])) {
                return false;
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix &other) const noexcept {
        return !(*this == other);
    }

    double Matrix::trace() const {
        if (m_rows != m_cols) {
            throw std::runtime_error("У не квадратной матрицы нельзя посчитать след");
        }
        double res = 0.0;
        for (size_t i = 0, j = 0; i < m_rows; ++i, ++j) {
            res += m_ptr[i * m_cols + j];
        }
        return res;
    }

    const Matrix operator*(double lhs, const Matrix &rhs) {
        return rhs * lhs;
    }

    const Matrix Matrix::getMinor(size_t row, size_t col) const {
        const size_t new_rows = m_rows - 1;
        const size_t new_cols = m_cols - 1;
        Matrix new_matrix(new_rows, new_cols);
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < m_cols; ++j) {
                if (!(i == row || j == col)) {
                    new_matrix(i - (i > row ? 1 : 0), j - (j > col ? 1 : 0)) = m_ptr[i * m_cols + j];
                }
            }
        }
        return new_matrix;
    }

    double Matrix::det() const {
        if (m_cols != m_rows) {
            throw std::runtime_error("Нельзя посчитать определитель у не квадратной матрицы");
        } else if (m_cols == 1) {
            return m_ptr[0];
        } else if (m_cols == 2) {
            return m_ptr[0] * m_ptr[3] - m_ptr[1] * m_ptr[2];
        } else {
            double res = 0.0;
            for (size_t i = 0; i < m_cols; ++i) {
                res += m_ptr[i] * (i % 2 == 0 ? 1 : -1) * getMinor(0, i).det();
            }
            return res;
        }
    }

    void swap(double *mat, size_t row1, size_t row2, size_t col) {
        for (size_t i = 0; i < col; i++) {
            double temp = mat[row1 * col + i];
            mat[row1 * col + i] = mat[row2 * col + i];
            mat[row2 * col + i] = temp;
        }
    }

    int rankOfMatrix(double *mat, size_t R, size_t C) {
        int rank = C;

        for (int row = 0; row < rank; row++) {
            if (!areSame(mat[row * C + row], 0.0)) {
                for (int col = 0; col < R; col++) {
                    if (col != row) {
                        double mult = mat[col * C + row] /
                                      mat[row * C + row];
                        for (int i = 0; i < rank; i++)
                            mat[col * C + i] -= mult * mat[row * C + i];
                    }
                }
            } else {
                bool reduce = true;

                for (int i = row + 1; i < R; i++) {
                    if (!areSame(mat[i * C + row], 0)) {
                        swap(mat, row, i, rank);
                        reduce = false;
                        break;
                    }
                }
                if (reduce) {
                    rank--;

                    for (int i = 0; i < R; i++)
                        mat[i * C + row] = mat[i * C + rank];
                }
                row--;
            }
        }
        return rank;
    }

    int Matrix::rank() const {
        size_t size = m_rows * m_cols;
        double *tmp = new double[size];
        for (size_t i = 0; i < size; ++i) {
            tmp[i] = m_ptr[i];
        }
        int res = rankOfMatrix(tmp, m_rows, m_cols);
        delete[] tmp;
        return res;
    }

    Matrix::Matrix(Matrix &&other) : m_ptr(other.m_ptr), m_capacity(other.m_capacity), m_rows(other.m_rows),
                                     m_cols(other.m_cols) {
        other.m_ptr = nullptr;
        other.m_capacity = 0;
        other.m_rows = 0;
        other.m_cols = 0;
    }

    std::ostream &operator<<(std::ostream &out, const Matrix &rhs) {
        int width = rhs.findMaxLengthNumber();
        for (size_t i = 0; i < rhs.m_rows; ++i) {
            out << "|";
            for (size_t j = 0; j < rhs.m_cols; ++j) {
                out << std::setw(width) << rhs.m_ptr[i * rhs.m_cols + j]
                    << (j + 1 < rhs.m_cols ? " " : "");
            }
            out << "|\n";
        }
        return out;
    }

    size_t Matrix::rows() const noexcept {
        return m_rows;
    }

    size_t Matrix::cols() const noexcept {
        return m_cols;
    }

    Matrix transpose(const Matrix &rhs) noexcept {
        Matrix res(rhs.cols(), rhs.rows());
        for (size_t i = 0; i < rhs.rows(); ++i) {
            for (size_t j = 0; j < rhs.cols(); ++j) {
                res(j, i) = rhs(i, j);
            }
        }
        return res;
    }

    Matrix power(const Matrix &lhs, int rhs) noexcept {
        Matrix res(lhs);
        for (int i = 1; i < rhs; ++i) {
            res *= lhs;
        }
        return res;
    }

    int Matrix::findMaxLengthNumber() const noexcept {
        int max = -1;
        for (size_t i = 0; i < m_rows * m_cols; ++i) {
            int length = digitsCount(m_ptr[i]);
            if (length > max) max = length;
        }
        return max;
    }

    int digitsCount(double number) {
        int numberInt = std::abs(static_cast<int>(number));
        int count = number > 0 ? 0 : 1;
        while (numberInt > 0) {
            ++count;
            numberInt /= 10;
        }
        return count;
    }

    bool areSame(double a, double b) {
        return fabs(a - b) < EPSILON;
    }

    double Matrix::norm() const {
        double sum = 0.0;
        for (size_t i = 0; i < m_cols * m_rows; ++i) {
            sum += m_ptr[i] * m_ptr[i];
        }
        return sqrt(sum);
    }

    Matrix getCofactor(const Matrix& vect) {
        if (vect.rows() != vect.cols()) {
            throw std::runtime_error("Матрица не квадратная");
        }

        Matrix solution(vect.rows(), vect.cols());
        Matrix subVect(vect.rows() - 1, vect.cols() - 1);

        for(std::size_t i = 0; i < vect.rows(); i++) {
            for(std::size_t j = 0; j < vect.cols(); j++) {

                int p = 0;
                for(size_t x = 0; x < vect.rows(); x++) {
                    if(x == i) {
                        continue;
                    }
                    int q = 0;

                    for(size_t y = 0; y < vect.rows(); y++) {
                        if(y == j) {
                            continue;
                        }

                        subVect(p, q) = vect(x, y);
                        q++;
                    }
                    p++;
                }
                solution(i, j) = pow(-1, i + j) * subVect.det();
            }
        }
        return solution;
    }

    Matrix invert(const Matrix &rhs) {
        if (rhs.rows() != rhs.cols()) {
            throw std::runtime_error("Матрица не квадратная. Посчитать обратную невозможно.");
        }

        double det = rhs.det();

        if (det == 0) {
            throw std::runtime_error("Детерминант равен нулю. Не существует обратной матрицы.");
        }

        double d = 1.0 / det;
        Matrix solution = transpose(getCofactor(rhs));

        for (size_t i = 0; i < solution.rows(); i++) {
            for (size_t j = 0; j < solution.cols(); j++) {
                solution(i, j) *= d;
            }
        }

        return solution;
    }

    const Matrix Matrix::operator-() const noexcept {
        Matrix res(*this);
        for (size_t i = 0; i < res.m_cols * res.m_rows; ++i) {
            res.m_ptr[i] = -res.m_ptr[i];
        }
        return res;
    }

}