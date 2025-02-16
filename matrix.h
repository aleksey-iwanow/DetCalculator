#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
private:
    int rows;
    int columns;
    std::vector<std::vector<double>> elements {};

    double funcDet(std::vector<std::vector<double> >);
public:
    Matrix();
    Matrix(int, int);
    ~Matrix();

    void resizeMatrix(int new_rows, int new_cols);
    void setElement(int r, int c, double value);
    double calculateDeterminantOfMatrix();
    void display();
    int getRows();
    int getCols();
    double get(int, int);
    void resizeColumns(int k=0);
    void resizeRows(int k=0);
};

#endif // MATRIX_H
