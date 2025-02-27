#ifndef MATRIX_H
#define MATRIX_H
#include <QString>
#include <vector>

class Matrix
{
private:
    int rows;
    int columns;
    std::vector<std::vector<int>> elements {};

    long funcDet(const std::vector<std::vector<int>>& elms);
    std::vector<std::vector<int>> getMinor(const std::vector<std::vector<int>>& elms, int row, int col);
public:
    Matrix();
    Matrix(int, int);
    ~Matrix();
    void resizeMatrix(int new_rows, int new_cols);
    void setElement(int r, int c, int value);
    long calculateDeterminantOfMatrix();
    void display(std::vector<std::vector<int>> &els);
    void display(std::vector<int> &els);
    std::vector<double> calculateRootsOfMatrix();
    void swapElements(std::vector<std::vector<int>>& currentMatrix, const std::vector<int> &vector, int col);
    int getRows();
    int getCols();
    int get(int, int);
    void resizeColumns(int k=0);
    void resizeRows(int k=0);
};

#endif // MATRIX_H
