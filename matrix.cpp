#include "matrix.h"
#include <iostream>
#include <vector>
#include <cmath>


Matrix::Matrix() : Matrix::Matrix(1, 1) { };

Matrix::Matrix(int rows, int columns) :
    rows(rows), columns(columns), elements(rows, std::vector<double>(columns)) { }

void Matrix::setElement(int r, int c, double value){
    if (r >= 0 && r < rows && c >= 0 && c < columns) {
        elements[r][c] = value;
    } else {
        throw std::out_of_range("Invalid index");
    }
    display();
}

double Matrix::get(int row, int col){
    return elements[row][col];
}

void Matrix::resizeMatrix(int new_rows, int new_cols){
    elements.resize(new_rows);
    resizeColumns();
}

int Matrix::getRows(){
    return rows;
}

int Matrix::getCols(){
    return columns;
}

void Matrix::display(){
    for (int y = 0; y < rows; y++){
        for (int x = 0; x < columns; x++){
            std::cout << elements[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::resizeRows(int k){
    rows += k;
    if (k > 0)
        elements.push_back(std::vector<double>(columns));
    else
        elements.pop_back();
}

void Matrix::resizeColumns(int k){
    columns += k;
    for (auto &row : elements) {
        row.resize(columns);
    }
}

double Matrix::funcDet(std::vector<std::vector<double> > elms){
    int r = elms.size();
    int c = elms[0].size();

    if (r == 1 && c == 1)
        return elms[0][0];
    else if (r == 2 && c == 2)
        return elms[0][0]*elms[1][1] - elms[1][0]*elms[0][1];
    else{
        double result{};
        for (int i = 0; i < c; i++){
            double el = elms[0][i];
            std::vector<std::vector<double>> newChildMatrix{};
            for (int j = 1; j < r; j++){
                std::vector<double> rowVector;

                for (int i2 = 0; i2 < c; i2++){
                    if (i2 == i) continue;
                    rowVector.push_back(elms[j][i2]);
                }
                newChildMatrix.push_back(rowVector);
            }
            result += el * std::pow(-1, 2+i) * funcDet(newChildMatrix);
        }
        return result;
    }
    return NAN;
}

double Matrix::calculateDeterminantOfMatrix(){
    return funcDet(elements);
}

Matrix::~Matrix() {
    // деструктор
}
