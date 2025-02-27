#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "matrix.h"
#include "currenttype.cpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Конструктор главного окна приложения
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Matrix matrix;
    void changeRow(int k);
    void changeCol(int k);
    void initTable();
    void adjustTable();
    void onCellChanged(int row, int column); // Объявляем слот

private:
    Ui::MainWindow *ui;
    CurrentType currentType;
    void swapPanel(QWidget* panelDis, QWidget* panelAct);
};
#endif // MAINWINDOW_H
