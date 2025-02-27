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
    elements(rows, std::vector<int>(columns)) {} // Создание двумерного вектора элементов

// Метод установки значения элемента матрицы по заданным координатам.
void Matrix::setElement(int r, int c, int value) {
    // Проверка индексов на выход за границы матрицы.
    if (r >= 0 && r < rows && c >= 0 && c < columns) {
        elements[r][c] = value; // Установка значения элемента
    } else {
        throw std::out_of_range("Invalid index"); // Исключение при выходе за пределы матрицы
    }
}

// Метод получения значения элемента матрицы по заданным координатам.
int Matrix::get(int row, int col) {
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
void Matrix::display(std::vector<std::vector<int>> &els) {
    std::cout << "-----------------------------------" << std::endl;
    for (int y = 0; y < els.size(); y++) { // Перебор строк
        display(els[y]);
    }
}

void Matrix::display(std::vector<int> &els) {

    for (int x = 0; x < els.size(); x++) { // Перебор столбцов
        std::cout << els[x] << " "; // Вывод значения элемента
    }
    std::cout << std::endl; // Переход на новую строку после каждой строки матрицы
}


// Метод добавления или удаления строк матрицы.
void Matrix::resizeRows(int k) {
    rows += k; // Увеличение или уменьшение количества строк
    if (k > 0) {
        elements.push_back(std::vector<int>(columns)); // Добавление новой строки
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
long Matrix::funcDet(const std::vector<std::vector<int>>& elms) {
    int n = elms.size(); // Количество строк (или столбцов, предполагаем квадратную матрицу)

    if (n == 1) {
        return elms[0][0]; // Детерминант для матрицы 1x1
    } else if (n == 2) {
        return elms[0][0] * elms[1][1] - elms[1][0] * elms[0][1]; // Детерминант для матрицы 2x2
    } else {
        long result = 0; // Переменная для накопления результата
        for (int i = 0; i < n; i++) {
            long cofactor = elms[0][i] * funcDet(getMinor(elms, 0, i));
            result += (i % 2 == 0 ? cofactor : -cofactor); // Учет знака
        }
        return result; // Возвращение накопленного результата
    }
}

// Функция для получения минорной матрицы
std::vector<std::vector<int>> Matrix::getMinor(const std::vector<std::vector<int>>& elms, int row, int col) {
    int n = elms.size();
    std::vector<std::vector<int>> minor(n - 1, std::vector<int>(n - 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != row && j != col) {
                minor[i - (i > row ? 1 : 0)][j - (j > col ? 1 : 0)] = elms[i][j];
            }
        }
    }
    return minor;
}

// Метод вычисления детерминанта матрицы.
long Matrix::calculateDeterminantOfMatrix() {
    return funcDet(elements); // Вызов функции для вычисления детерминанта
}

void Matrix::swapElements(std::vector<std::vector<int>>& currentMatrix, const std::vector<int> &vector, int col){
    for (int i = 0; i < currentMatrix.size(); i++){
        currentMatrix[i][col] = vector[i];
    }
}

std::vector<double> Matrix::calculateRootsOfMatrix(){
    auto allA (elements);
    std::vector<int> allB {};
    std::vector<double> allRoots {};

    for (auto &row : allA) {
        allB.push_back(row.back());
        row.pop_back();
    }
    display(allB);
    display(allA);
    long detAllA = funcDet(allA);
    if (detAllA == 0) return allRoots;

    for (int i = 0; i < allA[0].size(); i++){
        auto currentSwapMatrix (allA);
        swapElements(currentSwapMatrix, allB, i);
        display(currentSwapMatrix);
        long currentDet = funcDet(currentSwapMatrix);
        allRoots.push_back(currentDet / detAllA);
    }
    return allRoots;
}

// Деструктор класса Matrix.
Matrix::~Matrix() {
    // Здесь ничего делать не нужно, так как все ресурсы освобождаются автоматически.
}
