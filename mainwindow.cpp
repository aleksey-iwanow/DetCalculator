#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "matrix.h"
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <algorithm> // Для std::all_of
#include <string>
#include <cctype> // Для std::isdigit

std::string stringToDigit(const std::string& input);
void onCellChanged(int, int);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , matrix(3, 3)
{
    ui->setupUi(this);
    initTable();

    connect(ui->tableWidget, &QTableWidget::cellChanged, this, [this](int row, int col) {
        onCellChanged(row, col);
    });

    connect(ui->calcDet, &QPushButton::clicked, this, [=] {
        auto res = matrix.calculateDeterminantOfMatrix();
        ui->resultEdit->setText(QString::number(res));
    });

    connect(ui->addCol, &QPushButton::clicked, this, [=] {
        changeCol(1);
        // потому что марица должна быть N x N
        changeRow(1); //временно
    });

    connect(ui->removeCol, &QPushButton::clicked, this, [=] {
        changeCol(-1);
        // потому что марица должна быть N x N
        changeRow(-1); //временно
    });

    connect(ui->addRow, &QPushButton::clicked, this, [=] {
        changeCol(1); //временно
        // потому что марица должна быть N x N
        changeRow(1);
    });

    connect(ui->removeRow, &QPushButton::clicked, this, [=] {
        changeCol(-1); //временно
        // потому что марица должна быть N x N
        changeRow(-1);
    });

}

void MainWindow::adjustTable(){
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::changeRow(int k){
    int r = matrix.getRows();
    if (r+k <= 0) return;
    matrix.resizeRows(k);
    r+=k;
    ui->tableWidget->setRowCount(r);
    if(k > 0)
    for (int c = 0; c < matrix.getCols(); c++){
        ui->tableWidget->setItem(r-1, c, new QTableWidgetItem("0"));
    }
    adjustTable();
}

void MainWindow::changeCol(int k){
    int c = matrix.getCols();
    if (c+k <= 0) return;
    matrix.resizeColumns(k);
    c+=k;
    ui->tableWidget->setColumnCount(c);
    if(k > 0)
    for (int r = 0; r < matrix.getRows(); r++){
        ui->tableWidget->setItem(r, c-1, new QTableWidgetItem("0"));
    }
    adjustTable();
}

void MainWindow::initTable(){
    auto r = matrix.getRows();
    auto c = matrix.getCols();
    ui->tableWidget->setRowCount(r);
    ui->tableWidget->setColumnCount(c);

    for (int y = 0; y < r; y++){
        for (int x = 0; x < c; x++){
            ui->tableWidget->setItem(y, x, new QTableWidgetItem(QString::number(matrix.get(y, x))));
        }
    }
    adjustTable();
}

void MainWindow::onCellChanged(int row, int col) {
    QTableWidgetItem *item = ui->tableWidget->item(row, col);
    if (item) {
        QString text = item->text();
        auto newText = stringToDigit(text.toStdString());
        item->setText(QString::fromStdString(newText));
        ui->tableWidget->resizeRowsToContents();
        matrix.setElement(row, col, text.toDouble());
    }
}


std::string stringToDigit(const std::string& input) {
    std::string result;
    std::copy_if(input.begin(), input.end(), std::back_inserter(result), [](char c) {
        return std::isdigit(c) || c == '-' || c == '.';
    });
    if (result == "")
        return "0";
    return result;
}



MainWindow::~MainWindow()
{
    delete ui;
}
