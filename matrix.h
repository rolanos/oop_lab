#pragma once
#include"number.h"

class Matrix {

private:
    int dimension;

    number** matrix;

    void createMatrixWithDimension(int n);

public:
    // Перегрузка оператора присваивания
    Matrix& operator=(const Matrix& other);
    //Конструктор класса по умолчанию
    Matrix();
    //Конструктор класса для инициализации матрицы
    Matrix(int n);
    //Деструктор класса
    ~Matrix();
    //Ввод элементов в матрицу
    void inputValue(number value, int row, int column);
    //Вычисление детерминанта
    number calculateDetermenant();
    //Получение транспонированной матрицы
    Matrix calculateTranspose();
    //Получить ранг матрицы
    int getRank();
    //Получить размерность матрицы
    int getDimension();
    //Вывод матрицы
    void print();

    number& operator() (const int i, const int j);

};
