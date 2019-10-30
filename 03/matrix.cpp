#include "matrix.hpp"

Row::Row(int* ptr, size_t cols){
    row = ptr;
    n_cols = cols;
    }

int& Row::operator[](size_t j) {
    if (j >= n_cols) {
        throw out_of_range("OUT OF RANGE");
    }
    return row[j];
}

Matrix::Matrix(size_t row, size_t col){
    n_rows = row;
    n_cols = col;
    values = new int [n_rows * n_cols];
    for (size_t i = 0; i < n_rows * n_cols; i++) {
        values[i] = 0;
    }
}

Matrix::Matrix(const Matrix& m) {
    n_rows = m.n_rows;
    n_cols = m.n_cols;

    values = new int [n_rows * n_cols];

    for (size_t k = 0; k < n_rows * n_cols; k++) {
        values[k] = m.values[k];
    }
}

Matrix::~Matrix() {
    delete [] values;
}

size_t Matrix::getRows() {
    return n_rows;
}

size_t Matrix::getColumns() {
    return n_cols;
}

Row Matrix::operator[] (size_t i) {
    if (i >= n_rows) {
        throw out_of_range("OUT OF RANGE");
    }
    Row result = Row(values + i * n_cols, n_cols);
    return result;
}

bool Matrix::operator==(const Matrix& other) {
    if (n_rows != other.n_rows) {
        return false;
    }
    if (n_cols != other.n_cols) {
        return false;
    }
    for (size_t k = 0; k < n_rows * n_cols; k++) {
        if (values[k] != other.values[k]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) {
    return !(*this == other);
}

Matrix& Matrix::operator*=(int a) {
    for (size_t k = 0; k < n_rows * n_cols; k++) {
        values[k] *= a;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Matrix& value) {
    out << "n_rows = " << value.n_rows << " n_cols = "<< value.n_cols << endl;
    for (size_t i = 0; i < value.n_rows; i++) {
        for (size_t j = 0; j < value.n_cols; j++) {
            out << value.values[i * value.n_cols + j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
    return out;
}