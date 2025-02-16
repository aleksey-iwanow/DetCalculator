#include "matrix.h"
#include <iostream>
#include <vector>
#include <cmath>

// Конструктор по умолчанию, вызывающий конструктор с параметрами (1, 1).
Matrix::Matrix() : Matrix::Matrix(1, 1) {}

// Конструктор, принимающий количество строк и столбцов матрицы.
Matrix::Matrix(int rows, int columns) :
    rows(rows), // Инициализация количества строк
    columns(columns), // Инициализация количества столбцов
    elements(rows, std::vector<double>(columns)) {} // Создание двумерного вектора элементов

// Метод установки значения элемента матрицы по заданным координатам.
void Matrix::setElement(int r, int c, double value) {
    // Проверка индексов на выход за границы матрицы.
    if (r >= 0 && r < rows && c >= 0 && c < columns) {
        elements[r][c] = value; // Установка значения элемента
    } else {
        throw std::out_of_range("Invalid index"); // Исключение при выходе за пределы матрицы
    }
    display(); // Отображение текущей матрицы после изменения
}

// Метод получения значения элемента матрицы по заданным координатам.
double Matrix::get(int row, int col) {
    return elements[row][col]; // Возврат значения элемента
}

// Метод изменения размера матрицы (количества строк и столбцов).
void Matrix::resizeMatrix(int new_rows, int new_cols) {
    elements.resize(new_rows); // Изменение количества строк
    resizeColumns(); // Изменение количества столбцов
}

// Метод получения количества строк матрицы.
int Matrix::getRows() {
    return rows; // Возврат количества строк
}

// Метод получения количества столбцов матрицы.
int Matrix::getCols() {
    return columns; // Возврат количества столбцов
}

// Метод отображения матрицы на экране.
void Matrix::display() {
    for (int y = 0; y < rows; y++) { // Перебор строк
        for (int x = 0; x < columns; x++) { // Перебор столбцов
            std::cout << elements[y][x] << " "; // Вывод значения элемента
        }
        std::cout << std::endl; // Переход на новую строку после каждой строки матрицы
    }
}

// Метод добавления или удаления строк матрицы.
void Matrix::resizeRows(int k) {
    rows += k; // Увеличение или уменьшение количества строк
    if (k > 0) {
        elements.push_back(std::vector<double>(columns)); // Добавление новой строки
    } else {
        elements.pop_back(); // Удаление последней строки
    }
}

// Метод добавления или удаления столбцов матрицы.
void Matrix::resizeColumns(int k) {
    columns += k; // Увеличение или уменьшение количества столбцов
    for (auto &row : elements) { // Перебор всех строк
        row.resize(columns); // Изменение длины каждой строки
    }
}

// Рекурсивная функция для вычисления детерминанта матрицы.
double Matrix::funcDet(std::vector<std::vector<double> > elms) {
    int r = elms.size(); // Количество строк
    int c = elms[0].size(); // Количество столбцов

    if (r == 1 && c == 1) {
        return elms[0][0]; // Детерминант для матрицы 1x1
    } else if (r == 2 && c == 2) {
        return elms[0][0] * elms[1][1] - elms[1][0] * elms[0][1]; // Детерминант для матрицы 2x2
    } else {
        double result{}; // Переменная для накопления результата
        for (int i = 0; i < c; i++) {
            double el = elms[0][i]; // Элемент первой строки
            std::vector<std::vector<double>> newChildMatrix{}; // Новая подматрица
            for (int j = 1; j < r; j++) {
                std::vector<double> rowVector; // Строка новой подматрицы
                for (int i2 = 0; i2 < c; i2++) {
                    if (i2 == i) continue; // Пропускаем текущий столбец
                    rowVector.push_back(elms[j][i2]); // Заполнение строки новыми значениями
                }
                newChildMatrix.push_back(rowVector); // Добавление строки в подматрицу
            }
            result += el * std::pow(-1, 2 + i) * funcDet(newChildMatrix); // Вычисление рекурсивного шага
        }
        return result; // Возвращение накопленного результата
    }
    return NAN; // Значение NaN, если размер матрицы некорректен
}

// Метод вычисления детерминанта матрицы.
double Matrix::calculateDeterminantOfMatrix() {
    return funcDet(elements); // Вызов функции для вычисления детерминанта
}

// Деструктор класса Matrix.
Matrix::~Matrix() {
    // Здесь ничего делать не нужно, так как все ресурсы освобождаются автоматически.
}