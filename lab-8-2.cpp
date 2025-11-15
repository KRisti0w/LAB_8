#include <iostream>
#include <cstddef>

struct Matrix {
    int** data_ = nullptr;
    size_t n_ = 0u; // столбцы
    size_t m_ = 0u; // строки
};

// Создает заполненную нулями матрицу n x m
void Construct(Matrix& out, size_t n, size_t m) {
    out.n_ = n;
    out.m_ = m;
    out.data_ = new int*[m];
    for (size_t i = 0; i < m; i++) {
        out.data_[i] = new int[n]();
    }
}

// Освобождает выделенную память
void Destruct(Matrix& in) {
    if (in.data_) {
        for (size_t i = 0; i < in.m_; i++) {
            delete[] in.data_[i];
        }
        delete[] in.data_;
        in.data_ = nullptr;
    }
    in.n_ = 0;
    in.m_ = 0;
}

// Создает копию матрицы
Matrix Copy(const Matrix& matrix) {
    Matrix result;
    Construct(result, matrix.n_, matrix.m_);
    for (size_t i = 0; i < matrix.m_; i++) {
        for (size_t j = 0; j < matrix.n_; j++) {
            result.data_[i][j] = matrix.data_[i][j];
        }
    }
    return result;
}

// Сумма двух матриц
Matrix Add(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return Matrix{};
    }

    Matrix result;
    Construct(result, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; i++) {
        for (size_t j = 0; j < a.n_; j++) {
            result.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        }
    }
    return result;
}

// Разность двух матриц
Matrix Sub(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return Matrix{};
    }

    Matrix result;
    Construct(result, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; i++) {
        for (size_t j = 0; j < a.n_; j++) {
            result.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        }
    }
    return result;
}

// Произведение двух матриц
Matrix Mult(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.m_) {
        return Matrix{};
    }

    Matrix result;
    Construct(result, b.n_, a.m_);
    for (size_t i = 0; i < a.m_; i++) {
        for (size_t j = 0; j < b.n_; j++) {
            result.data_[i][j] = 0;
            for (size_t k = 0; k < a.n_; k++) {
                result.data_[i][j] += a.data_[i][k] * b.data_[k][j];
            }
        }
    }
    return result;
}

// Транспонирование матрицы
void Transposition(Matrix& matrix) {
    Matrix temp;
    Construct(temp, matrix.m_, matrix.n_);
    for (size_t i = 0; i < matrix.m_; i++) {
        for (size_t j = 0; j < matrix.n_; j++) {
            temp.data_[j][i] = matrix.data_[i][j];
        }
    }
    Destruct(matrix);
    matrix = temp;
}

// Сравнение двух матриц
bool operator==(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return false;
    }
    for (size_t i = 0; i < a.m_; i++) {
        for (size_t j = 0; j < a.n_; j++) {
            if (a.data_[i][j] != b.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Функция для печати матрицы
void PrintMatrix(const Matrix& matrix) {
    std::cout << "Matrix " << matrix.m_ << "x" << matrix.n_ << ":\n";
    for (size_t i = 0; i < matrix.m_; i++) {
        for (size_t j = 0; j < matrix.n_; j++) {
            std::cout << matrix.data_[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

int main() {
    // Тест 1: Создание и копирование
    std::cout << "Test 1: Create and Copy" << std::endl;
    Matrix m1;
    Construct(m1, 2, 2);
    m1.data_[0][0] = 1; m1.data_[0][1] = 2;
    m1.data_[1][0] = 3; m1.data_[1][1] = 4;

    std::cout << "Original matrix:";
    PrintMatrix(m1);

    Matrix m2 = Copy(m1);
    std::cout << "Copy matrix:";
    PrintMatrix(m2);

    // Тест 2: Сложение
    std::cout << "Test 2: Addition" << std::endl;
    Matrix sum = Add(m1, m2);
    std::cout << "Sum of the matrices:";
    PrintMatrix(sum);

    // Тест 3: Вычитание
    std::cout << "Test 3: Subtraction" << std::endl;
    Matrix diff = Sub(m1, m2);
    std::cout << "Matrix difference:";
    PrintMatrix(diff);

    // Тест 4: Умножение
    std::cout << "Test 4: Multiplication" << std::endl;
    Matrix m3;
    Construct(m3, 3, 2);
    m3.data_[0][0] = 1; m3.data_[0][1] = 2; m3.data_[0][2] = 3;
    m3.data_[1][0] = 4; m3.data_[1][1] = 5; m3.data_[1][2] = 6;

    Matrix m4;
    Construct(m4, 2, 3);
    m4.data_[0][0] = 7; m4.data_[0][1] = 8;
    m4.data_[1][0] = 9; m4.data_[1][1] = 10;
    m4.data_[2][0] = 11; m4.data_[2][1] = 12;

    std::cout << "Matrix A:";
    PrintMatrix(m3);
    std::cout << "Matrix B:";
    PrintMatrix(m4);

    Matrix product = Mult(m3, m4);
    std::cout << "Product A x B:";
    PrintMatrix(product);

    // Тест 5: Транспонирование
    std::cout << "Test 5: Transposition" << std::endl;
    std::cout << "Before transposition:";
    PrintMatrix(m3);
    Transposition(m3);
    std::cout << "After transposing:";
    PrintMatrix(m3);

    // Тест 6: Сравнение
    std::cout << "Test 6: Comparison" << std::endl;
    std::cout << "m1 == m2: " << (m1 == m2 ? "true" : "false") << std::endl;
    std::cout << "m1 == m3: " << (m1 == m3 ? "true" : "false") << std::endl;

    // Освобождение памяти
    Destruct(m1);
    Destruct(m2);
    Destruct(m3);
    Destruct(m4);
    Destruct(sum);
    Destruct(diff);
    Destruct(product);

    return 0;
}