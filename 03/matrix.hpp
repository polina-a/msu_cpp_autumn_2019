
/*
Нужно написать класс-матрицу, тип элементов int. 
В конструкторе задается количество рядов и строк. 
Поддерживаются оперции: 
получить количество строк(rows)/столбцов(columns), 
получить конкретный элемент, 
умножить на число(*=), 
сравнение на равенство/неравенство. 

В случае ошибки выхода за границы бросать исключение:
throw std::out_of_range("")*/

#pragma once

#include <iostream>

using namespace std;

class Row {
    int *row;
    size_t n_cols;
public:
    Row(int* ptr, size_t cols);
    int& operator[](size_t j);
};

class Matrix {
    size_t n_rows;
    size_t n_cols;
    int* values;
public:
    Matrix(size_t row = 1, size_t col = 1);
    Matrix(const Matrix& m);
    ~Matrix();
    size_t getRows();
    size_t getColumns();
    Row operator[](size_t i);
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);
    Matrix& operator*=(int a);
    friend ostream& operator<<(ostream& out, const Matrix& value);
};