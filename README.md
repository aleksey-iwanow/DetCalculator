# BasicCalculator

Простой калькулятор, реализованный на C++ с использованием библиотеки Qt для создания графического интерфейса пользователя (GUI). Этот калькулятор предназначен для расчета **определителя** (детерминанта) матрицы произвольного порядка.

## Описание

Приложение предоставляет возможность ввести элементы матрицы и рассчитать ее определитель. Пользователь может изменять размеры матрицы, добавлять или удалять строки и столбцы, а также корректировать значения элементов матрицы.

## Основные возможности

- Ввод элементов матрицы вручную.
- Автоматическая проверка введенных значений на допустимость.
- Расчет определителя матрицы любого порядка.
- Изменение размеров матрицы (добавление и удаление строк и столбцов).
- Удобный интерфейс для работы с матрицей.

## Формула для нахождения определителя

Определитель матрицы является важным понятием в линейной алгебре. Определитель матрицы $n$-го порядка обозначается как $\det(A)$ или $|A|$. Ниже приведена формула для нахождения определителя матрицы четвертого порядка:

$$
\det(A) = a_{11}a_{22}a_{33}a_{44} + a_{12}a_{23}a_{34}a_{41} + a_{13}a_{24}a_{31}a_{42} + a_{14}a_{21}a_{32}a_{43} - a_{14}a_{23}a_{32}a_{41} - a_{13}a_{22}a_{34}a_{41} - a_{12}a_{24}a_{31}a_{43} - a_{11}a_{24}a_{33}a_{42}

$$

где $a_{ij}$ — элемент матрицы $A$ на пересечении $i$-й строки и $j$-го столбца.

## Скриншоты

### Главное окно приложения

![Главное окно приложения](screenshots/main_window.png)

### Результат выполнения операции

![Результат выполнения операции](screenshots/determinant_result.png)

## Требования

Для сборки и запуска этого проекта вам потребуется:

- Компьютер с установленной операционной системой Windows, Linux или macOS.
- Компилятор C++, поддерживающий стандарт C++11 или выше.
- Библиотека Qt версии 5.x или выше.