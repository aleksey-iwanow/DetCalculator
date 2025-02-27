#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "matrix.h"
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <algorithm> // Для std::all_of
#include <string>
#include <cctype> // Для std::isdigit

// Объявление функции преобразования строки в числовое представление
std::string stringToDigit(const std::string& input);

// Объявление функции обратного вызова при изменении ячейки таблицы
void onCellChanged(int, int);

// Конструктор главного окна приложения
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // Инициализация указателя интерфейса
    , matrix(3, 3), currentType(CurrentType::DETERMINITION) // Инициализация объекта матрицы размером 3x3
{
    ui->setupUi(this); // Настройка пользовательского интерфейса
    initTable(); // Инициализация таблицы
    swapPanel(ui->panelKorni, ui->panelDet);
    // Подключение сигнала изменения ячейки таблицы к слоту
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, [this](int row, int col) {
        onCellChanged(row, col); // Вызов функции обратного вызова при изменении ячейки
    });

    // Подключение кнопки расчета детерминанта к соответствующему обработчику
    connect(ui->calcDet, &QPushButton::clicked, this, [=] {
        auto res = matrix.calculateDeterminantOfMatrix(); // Расчет детерминанта матрицы
        ui->detEdit->setText(QString::number(res)); // Вывод результата в текстовое поле
    });

    connect(ui->calcKorni, &QPushButton::clicked, this, [=] {
        auto res = matrix.calculateRootsOfMatrix();
        QString out = " : ";
        for (auto &el : res){
            out += QString::number(el) + " : ";
        }
        ui->korniEdit->setText(out); // Вывод результата в текстовое поле
    });

    connect(ui->selectDet, &QPushButton::clicked, this, [=] {
        if (currentType == CurrentType::DETERMINITION) return;
        currentType = CurrentType::DETERMINITION;
        changeCol(-1);
        swapPanel(ui->panelKorni, ui->panelDet);
    });

    connect(ui->selectKorni, &QPushButton::clicked, this, [=] {
        if (currentType == CurrentType::ROOTS) return;
        currentType = CurrentType::ROOTS;
        changeCol(1);
        swapPanel(ui->panelDet, ui->panelKorni);
    });

    // Подключение кнопки добавления столбца к соответствующему обработчику
    connect(ui->addCol, &QPushButton::clicked, this, [=] {
        changeCol(1); // Добавление столбца
        // Временное изменение количества строк, чтобы сохранить квадратную форму матрицы
        changeRow(1); 
    });

    // Подключение кнопки удаления столбца к соответствующему обработчику
    connect(ui->removeCol, &QPushButton::clicked, this, [=] {
        changeCol(-1); // Удаление столбца
        // Временное изменение количества строк, чтобы сохранить квадратную форму матрицы
        changeRow(-1);
    });

    // Подключение кнопки добавления строки к соответствующему обработчику
    connect(ui->addRow, &QPushButton::clicked, this, [=] {
        // Временное изменение количества столбцов, чтобы сохранить квадратную форму матрицы
        changeCol(1);
        changeRow(1); // Добавление строки
    });

    // Подключение кнопки удаления строки к соответствующему обработчику
    connect(ui->removeRow, &QPushButton::clicked, this, [=] {
        // Временное изменение количества столбцов, чтобы сохранить квадратную форму матрицы
        changeCol(-1);
        changeRow(-1); // Удаление строки
    });
}

// Метод для автоматической настройки размеров ячеек таблицы
void MainWindow::adjustTable() {
    ui->tableWidget->resizeRowsToContents(); // Автоматическое изменение высоты строк
    ui->tableWidget->resizeColumnsToContents(); // Автоматическое изменение ширины столбцов
}

void MainWindow::swapPanel(QWidget* panelDis, QWidget* panelAct){
    panelDis->hide();
    panelAct->show();
}

// Метод для изменения количества строк в таблице
void MainWindow::changeRow(int k) {
    int r = matrix.getRows(); // Получение текущего количества строк
    if (r + k <= 0) return; // Проверка на недопустимое количество строк
    matrix.resizeRows(k); // Изменение размера матрицы
    r += k; // Обновление количества строк
    ui->tableWidget->setRowCount(r); // Установка нового количества строк в таблице
    if (k > 0) { // Если добавляются новые строки
        for (int c = 0; c < matrix.getCols(); c++) { // Цикл по всем новым ячейкам
            ui->tableWidget->setItem(r - 1, c, new QTableWidgetItem("0")); // Инициализация новых ячеек нулевыми значениями
        }
    }
    adjustTable(); // Корректировка размеров ячеек
}

// Метод для изменения количества столбцов в таблице
void MainWindow::changeCol(int k) {
    int c = matrix.getCols(); // Получение текущего количества столбцов
    if (c + k <= 0) return; // Проверка на недопустимое количество столбцов
    matrix.resizeColumns(k); // Изменение размера матрицы
    c += k; // Обновление количества столбцов
    ui->tableWidget->setColumnCount(c); // Установка нового количества столбцов в таблице
    if (k > 0) { // Если добавляются новые столбцы
        for (int r = 0; r < matrix.getRows(); r++) { // Цикл по всем новым ячейкам
            ui->tableWidget->setItem(r, c - 1, new QTableWidgetItem("0")); // Инициализация новых ячеек нулевыми значениями
        }
    }
    adjustTable(); // Корректировка размеров ячеек
}

// Метод инициализации таблицы
void MainWindow::initTable() {
    auto r = matrix.getRows(); // Получение количества строк матрицы
    auto c = matrix.getCols(); // Получение количества столбцов матрицы
    ui->tableWidget->setRowCount(r); // Установка количества строк в таблице
    ui->tableWidget->setColumnCount(c); // Установка количества столбцов в таблице

    for (int y = 0; y < r; y++) { // Цикл по строкам
        for (int x = 0; x < c; x++) { // Цикл по столбцам
            ui->tableWidget->setItem(y, x, new QTableWidgetItem(QString::number(matrix.get(y, x)))); // Заполнение ячеек значениями из матрицы
        }
    }
    adjustTable(); // Корректировка размеров ячеек
}

// Слот для обработки изменения содержимого ячейки таблицы
void MainWindow::onCellChanged(int row, int col) {
    QTableWidgetItem *item = ui->tableWidget->item(row, col); // Получение измененного элемента
    if (item) { // Проверка существования элемента
        QString text = item->text(); // Получение текста из ячейки
        auto newText = stringToDigit(text.toStdString()); // Преобразование текста в числовой формат
        item->setText(QString::fromStdString(newText)); // Установка преобразованного текста обратно в ячейку
        ui->tableWidget->resizeRowsToContents(); // Корректировка высоты строк
        matrix.setElement(row, col, text.toInt()); // Обновление значения в объекте матрицы
    }
}

// Функция преобразования строки в числовое представление
std::string stringToDigit(const std::string& input) {
    std::string result; // Результирующая строка
    std::copy_if(input.begin(), input.end(), std::back_inserter(result), [](char c) {
        return std::isdigit(c) || c == '-' || c == '.'; // Оставляем только цифры, знаки минус и точка
    });
    if (result == "") // Если строка пустая, заменяем её на "0"
        return "0";
    return result; // Возвращаем преобразованную строку
}

// Деструктор главного окна
MainWindow::~MainWindow() {
    delete ui; // Освобождение ресурсов интерфейса
}
