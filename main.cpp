/*
 * Программа для работы с двумерными массивами (матрицами)
 * Реализует основные операции над матрицами:
 * - ввод/вывод матриц
 * - арифметические операции (сложение, умножение)
 * - транспонирование
 * - вычисление определителя
 * - поиск максимума/минимума
 * - работа с файлами
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include <windows.h>

using namespace std;

// Максимальный размер матрицы
const int MAX_SIZE = 10;

// Глобальные переменные для хранения матриц
double matrix1[MAX_SIZE][MAX_SIZE];
double matrix2[MAX_SIZE][MAX_SIZE];
double resultMatrix[MAX_SIZE][MAX_SIZE];
int rows1 = 0, cols1 = 0;  // Размеры первой матрицы
int rows2 = 0, cols2 = 0;  // Размеры второй матрицы
int rowsR = 0, colsR = 0;  // Размеры результирующей матрицы

// Прототипы функций
void showMenu();
void inputMatrixManual(double mat[][MAX_SIZE], int &rows, int &cols, int num);
void inputMatrixRandom(double mat[][MAX_SIZE], int &rows, int &cols, int num);
void printMatrix(double mat[][MAX_SIZE], int rows, int cols, const char* name);
void addMatrices();
void subtractMatrices();
void multiplyMatrices();
void multiplyByScalar(int num);
void transposeMatrix(int num);
double calculateDeterminant(double mat[][MAX_SIZE], int n);
void findMinMax(int num);
void findRowColSums(int num);
void saveMatrixToFile(int num);
void loadMatrixFromFile(int num);
void copyMatrix(double src[][MAX_SIZE], double dst[][MAX_SIZE], int rows, int cols);
void swapRows(int num);
void swapCols(int num);

int main() {
    // Настройка консоли для вывода русских символов (UTF-8)
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    
    int choice;
    bool running = true;
    
    cout << "========================================" << endl;
    cout << "  Программа для работы с матрицами" << endl;
    cout << "========================================" << endl;
    
    while (running) {
        showMenu();
        cout << "Ваш выбор: ";
        cin >> choice;
        
        // Проверка корректности ввода
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка: введите число!" << endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                inputMatrixManual(matrix1, rows1, cols1, 1);
                break;
            case 2:
                inputMatrixManual(matrix2, rows2, cols2, 2);
                break;
            case 3:
                inputMatrixRandom(matrix1, rows1, cols1, 1);
                break;
            case 4:
                inputMatrixRandom(matrix2, rows2, cols2, 2);
                break;
            case 5:
                if (rows1 > 0) printMatrix(matrix1, rows1, cols1, "Матрица 1");
                else cout << "Матрица 1 не задана!" << endl;
                break;
            case 6:
                if (rows2 > 0) printMatrix(matrix2, rows2, cols2, "Матрица 2");
                else cout << "Матрица 2 не задана!" << endl;
                break;
            case 7:
                addMatrices();
                break;
            case 8:
                subtractMatrices();
                break;
            case 9:
                multiplyMatrices();
                break;
            case 10:
                multiplyByScalar(1);
                break;
            case 11:
                multiplyByScalar(2);
                break;
            case 12:
                transposeMatrix(1);
                break;
            case 13:
                transposeMatrix(2);
                break;
            case 14:
                // Вычисление определителя матрицы 1
                if (rows1 > 0 && rows1 == cols1) {
                    double det = calculateDeterminant(matrix1, rows1);
                    cout << "Определитель матрицы 1: " << det << endl;
                } else if (rows1 == 0) {
                    cout << "Матрица 1 не задана!" << endl;
                } else {
                    cout << "Матрица должна быть квадратной!" << endl;
                }
                break;
            case 15:
                // Вычисление определителя матрицы 2
                if (rows2 > 0 && rows2 == cols2) {
                    double det = calculateDeterminant(matrix2, rows2);
                    cout << "Определитель матрицы 2: " << det << endl;
                } else if (rows2 == 0) {
                    cout << "Матрица 2 не задана!" << endl;
                } else {
                    cout << "Матрица должна быть квадратной!" << endl;
                }
                break;
            case 16:
                findMinMax(1);
                break;
            case 17:
                findMinMax(2);
                break;
            case 18:
                findRowColSums(1);
                break;
            case 19:
                findRowColSums(2);
                break;
            case 20:
                swapRows(1);
                break;
            case 21:
                swapCols(1);
                break;
            case 22:
                saveMatrixToFile(1);
                break;
            case 23:
                saveMatrixToFile(2);
                break;
            case 24:
                loadMatrixFromFile(1);
                break;
            case 25:
                loadMatrixFromFile(2);
                break;
            case 0:
                running = false;
                cout << "Завершение программы..." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
        
        if (running) {
            cout << endl << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
    }
    
    return 0;
}

// Вывод меню на экран
void showMenu() {
    cout << endl;
    cout << "============== МЕНЮ ==============" << endl;
    cout << "--- Ввод матриц ---" << endl;
    cout << "1.  Ввод матрицы 1 вручную" << endl;
    cout << "2.  Ввод матрицы 2 вручную" << endl;
    cout << "3.  Заполнить матрицу 1 случайными числами" << endl;
    cout << "4.  Заполнить матрицу 2 случайными числами" << endl;
    cout << "--- Вывод матриц ---" << endl;
    cout << "5.  Показать матрицу 1" << endl;
    cout << "6.  Показать матрицу 2" << endl;
    cout << "--- Арифметические операции ---" << endl;
    cout << "7.  Сложение матриц" << endl;
    cout << "8.  Вычитание матриц" << endl;
    cout << "9.  Умножение матриц" << endl;
    cout << "10. Умножение матрицы 1 на скаляр" << endl;
    cout << "11. Умножение матрицы 2 на скаляр" << endl;
    cout << "--- Преобразования ---" << endl;
    cout << "12. Транспонирование матрицы 1" << endl;
    cout << "13. Транспонирование матрицы 2" << endl;
    cout << "--- Вычисления ---" << endl;
    cout << "14. Определитель матрицы 1" << endl;
    cout << "15. Определитель матрицы 2" << endl;
    cout << "16. Минимум и максимум в матрице 1" << endl;
    cout << "17. Минимум и максимум в матрице 2" << endl;
    cout << "18. Суммы строк и столбцов матрицы 1" << endl;
    cout << "19. Суммы строк и столбцов матрицы 2" << endl;
    cout << "--- Перестановки ---" << endl;
    cout << "20. Поменять строки в матрице 1" << endl;
    cout << "21. Поменять столбцы в матрице 1" << endl;
    cout << "--- Работа с файлами ---" << endl;
    cout << "22. Сохранить матрицу 1 в файл" << endl;
    cout << "23. Сохранить матрицу 2 в файл" << endl;
    cout << "24. Загрузить матрицу 1 из файла" << endl;
    cout << "25. Загрузить матрицу 2 из файла" << endl;
    cout << "---" << endl;
    cout << "0.  Выход" << endl;
    cout << "==================================" << endl;
}

// Ручной ввод матрицы
void inputMatrixManual(double mat[][MAX_SIZE], int &rows, int &cols, int num) {
    cout << "Ввод матрицы " << num << endl;
    
    // Ввод размеров
    cout << "Введите количество строк (1-" << MAX_SIZE << "): ";
    cin >> rows;
    if (rows < 1 || rows > MAX_SIZE) {
        cout << "Некорректное значение! Установлено значение 3." << endl;
        rows = 3;
    }
    
    cout << "Введите количество столбцов (1-" << MAX_SIZE << "): ";
    cin >> cols;
    if (cols < 1 || cols > MAX_SIZE) {
        cout << "Некорректное значение! Установлено значение 3." << endl;
        cols = 3;
    }
    
    // Ввод элементов
    cout << "Введите элементы матрицы построчно:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "a[" << i+1 << "][" << j+1 << "] = ";
            cin >> mat[i][j];
        }
    }
    
    cout << "Матрица " << num << " успешно введена!" << endl;
    printMatrix(mat, rows, cols, num == 1 ? "Матрица 1" : "Матрица 2");
}

// Заполнение матрицы случайными числами
void inputMatrixRandom(double mat[][MAX_SIZE], int &rows, int &cols, int num) {
    cout << "Генерация матрицы " << num << endl;
    
    // Ввод размеров
    cout << "Введите количество строк (1-" << MAX_SIZE << "): ";
    cin >> rows;
    if (rows < 1 || rows > MAX_SIZE) {
        cout << "Некорректное значение! Установлено значение 3." << endl;
        rows = 3;
    }
    
    cout << "Введите количество столбцов (1-" << MAX_SIZE << "): ";
    cin >> cols;
    if (cols < 1 || cols > MAX_SIZE) {
        cout << "Некорректное значение! Установлено значение 3." << endl;
        cols = 3;
    }
    
    // Ввод диапазона значений
    int minVal, maxVal;
    cout << "Введите минимальное значение: ";
    cin >> minVal;
    cout << "Введите максимальное значение: ";
    cin >> maxVal;
    
    if (minVal > maxVal) {
        // Меняем местами если мин больше макс
        int temp = minVal;
        minVal = maxVal;
        maxVal = temp;
    }
    
    // Заполнение случайными числами
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
    
    cout << "Матрица " << num << " успешно сгенерирована!" << endl;
    printMatrix(mat, rows, cols, num == 1 ? "Матрица 1" : "Матрица 2");
}

// Вывод матрицы на экран
void printMatrix(double mat[][MAX_SIZE], int rows, int cols, const char* name) {
    cout << endl << name << " [" << rows << "x" << cols << "]:" << endl;
    
    for (int i = 0; i < rows; i++) {
        cout << "| ";
        for (int j = 0; j < cols; j++) {
            cout << setw(8) << fixed << setprecision(2) << mat[i][j] << " ";
        }
        cout << "|" << endl;
    }
}

// Сложение двух матриц
void addMatrices() {
    // Проверка наличия матриц
    if (rows1 == 0 || rows2 == 0) {
        cout << "Обе матрицы должны быть заданы!" << endl;
        return;
    }
    
    // Проверка размеров
    if (rows1 != rows2 || cols1 != cols2) {
        cout << "Матрицы должны иметь одинаковые размеры!" << endl;
        cout << "Матрица 1: " << rows1 << "x" << cols1 << endl;
        cout << "Матрица 2: " << rows2 << "x" << cols2 << endl;
        return;
    }
    
    // Выполнение сложения
    rowsR = rows1;
    colsR = cols1;
    
    for (int i = 0; i < rowsR; i++) {
        for (int j = 0; j < colsR; j++) {
            resultMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    
    cout << "Результат сложения:" << endl;
    printMatrix(matrix1, rows1, cols1, "Матрица 1");
    cout << "       +" << endl;
    printMatrix(matrix2, rows2, cols2, "Матрица 2");
    cout << "       =" << endl;
    printMatrix(resultMatrix, rowsR, colsR, "Результат");
}

// Вычитание матриц
void subtractMatrices() {
    // Проверка наличия матриц
    if (rows1 == 0 || rows2 == 0) {
        cout << "Обе матрицы должны быть заданы!" << endl;
        return;
    }
    
    // Проверка размеров
    if (rows1 != rows2 || cols1 != cols2) {
        cout << "Матрицы должны иметь одинаковые размеры!" << endl;
        return;
    }
    
    // Выполнение вычитания
    rowsR = rows1;
    colsR = cols1;
    
    for (int i = 0; i < rowsR; i++) {
        for (int j = 0; j < colsR; j++) {
            resultMatrix[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    
    cout << "Результат вычитания:" << endl;
    printMatrix(matrix1, rows1, cols1, "Матрица 1");
    cout << "       -" << endl;
    printMatrix(matrix2, rows2, cols2, "Матрица 2");
    cout << "       =" << endl;
    printMatrix(resultMatrix, rowsR, colsR, "Результат");
}

// Умножение матриц
void multiplyMatrices() {
    // Проверка наличия матриц
    if (rows1 == 0 || rows2 == 0) {
        cout << "Обе матрицы должны быть заданы!" << endl;
        return;
    }
    
    // Проверка совместимости размеров для умножения
    if (cols1 != rows2) {
        cout << "Число столбцов первой матрицы должно равняться числу строк второй!" << endl;
        cout << "Матрица 1: " << rows1 << "x" << cols1 << endl;
        cout << "Матрица 2: " << rows2 << "x" << cols2 << endl;
        return;
    }
    
    // Результирующая матрица имеет размер rows1 x cols2
    rowsR = rows1;
    colsR = cols2;
    
    // Обнуление результирующей матрицы
    for (int i = 0; i < rowsR; i++) {
        for (int j = 0; j < colsR; j++) {
            resultMatrix[i][j] = 0;
        }
    }
    
    // Выполнение умножения
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    
    cout << "Результат умножения:" << endl;
    printMatrix(matrix1, rows1, cols1, "Матрица 1");
    cout << "       *" << endl;
    printMatrix(matrix2, rows2, cols2, "Матрица 2");
    cout << "       =" << endl;
    printMatrix(resultMatrix, rowsR, colsR, "Результат");
}

// Умножение матрицы на скаляр
void multiplyByScalar(int num) {
    double scalar;
    double (*mat)[MAX_SIZE];
    int rows, cols;
    
    // Выбор матрицы
    if (num == 1) {
        if (rows1 == 0) {
            cout << "Матрица 1 не задана!" << endl;
            return;
        }
        mat = matrix1;
        rows = rows1;
        cols = cols1;
    } else {
        if (rows2 == 0) {
            cout << "Матрица 2 не задана!" << endl;
            return;
        }
        mat = matrix2;
        rows = rows2;
        cols = cols2;
    }
    
    // Ввод скаляра
    cout << "Введите скаляр: ";
    cin >> scalar;
    
    // Вывод исходной матрицы
    printMatrix(mat, rows, cols, num == 1 ? "Исходная матрица 1" : "Исходная матрица 2");
    
    // Умножение
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] *= scalar;
        }
    }
    
    cout << "Умножение на " << scalar << ":" << endl;
    printMatrix(mat, rows, cols, "Результат");
}

// Транспонирование матрицы
void transposeMatrix(int num) {
    double temp[MAX_SIZE][MAX_SIZE];
    double (*mat)[MAX_SIZE];
    int *rows, *cols;
    
    // Выбор матрицы
    if (num == 1) {
        if (rows1 == 0) {
            cout << "Матрица 1 не задана!" << endl;
            return;
        }
        mat = matrix1;
        rows = &rows1;
        cols = &cols1;
    } else {
        if (rows2 == 0) {
            cout << "Матрица 2 не задана!" << endl;
            return;
        }
        mat = matrix2;
        rows = &rows2;
        cols = &cols2;
    }
    
    // Вывод исходной матрицы
    printMatrix(mat, *rows, *cols, "Исходная матрица");
    
    // Транспонирование во временную матрицу
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            temp[j][i] = mat[i][j];
        }
    }
    
    // Меняем размеры
    int newRows = *cols;
    int newCols = *rows;
    
    // Копируем обратно
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            mat[i][j] = temp[i][j];
        }
    }
    
    *rows = newRows;
    *cols = newCols;
    
    printMatrix(mat, *rows, *cols, "Транспонированная матрица");
}

// Вычисление определителя методом Гаусса
double calculateDeterminant(double mat[][MAX_SIZE], int n) {
    // Создаем копию матрицы для вычислений
    double temp[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j] = mat[i][j];
        }
    }
    
    double det = 1.0;
    int swapCount = 0;  // Счетчик перестановок строк
    
    // Прямой ход метода Гаусса
    for (int i = 0; i < n; i++) {
        // Поиск максимального элемента в столбце для устойчивости
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(temp[k][i]) > fabs(temp[maxRow][i])) {
                maxRow = k;
            }
        }
        
        // Если максимальный элемент равен нулю, определитель равен нулю
        if (fabs(temp[maxRow][i]) < 1e-10) {
            return 0;
        }
        
        // Перестановка строк если нужно
        if (maxRow != i) {
            for (int j = 0; j < n; j++) {
                double t = temp[i][j];
                temp[i][j] = temp[maxRow][j];
                temp[maxRow][j] = t;
            }
            swapCount++;
        }
        
        // Приведение к верхнетреугольному виду
        for (int k = i + 1; k < n; k++) {
            double factor = temp[k][i] / temp[i][i];
            for (int j = i; j < n; j++) {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }
    
    // Определитель - произведение диагональных элементов
    for (int i = 0; i < n; i++) {
        det *= temp[i][i];
    }
    
    // Учет знака при перестановках
    if (swapCount % 2 == 1) {
        det = -det;
    }
    
    return det;
}

// Поиск минимума и максимума в матрице
void findMinMax(int num) {
    double (*mat)[MAX_SIZE];
    int rows, cols;
    
    // Выбор матрицы
    if (num == 1) {
        if (rows1 == 0) {
            cout << "Матрица 1 не задана!" << endl;
            return;
        }
        mat = matrix1;
        rows = rows1;
        cols = cols1;
    } else {
        if (rows2 == 0) {
            cout << "Матрица 2 не задана!" << endl;
            return;
        }
        mat = matrix2;
        rows = rows2;
        cols = cols2;
    }
    
    printMatrix(mat, rows, cols, num == 1 ? "Матрица 1" : "Матрица 2");
    
    // Инициализация первым элементом
    double minVal = mat[0][0];
    double maxVal = mat[0][0];
    int minRow = 0, minCol = 0;
    int maxRow = 0, maxCol = 0;
    
    // Поиск мин и макс
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] < minVal) {
                minVal = mat[i][j];
                minRow = i;
                minCol = j;
            }
            if (mat[i][j] > maxVal) {
                maxVal = mat[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
    
    cout << endl;
    cout << "Минимальный элемент: " << minVal;
    cout << " (позиция: [" << minRow+1 << "][" << minCol+1 << "])" << endl;
    cout << "Максимальный элемент: " << maxVal;
    cout << " (позиция: [" << maxRow+1 << "][" << maxCol+1 << "])" << endl;
}

// Вычисление сумм строк и столбцов
void findRowColSums(int num) {
    double (*mat)[MAX_SIZE];
    int rows, cols;
    
    // Выбор матрицы
    if (num == 1) {
        if (rows1 == 0) {
            cout << "Матрица 1 не задана!" << endl;
            return;
        }
        mat = matrix1;
        rows = rows1;
        cols = cols1;
    } else {
        if (rows2 == 0) {
            cout << "Матрица 2 не задана!" << endl;
            return;
        }
        mat = matrix2;
        rows = rows2;
        cols = cols2;
    }
    
    printMatrix(mat, rows, cols, num == 1 ? "Матрица 1" : "Матрица 2");
    
    // Суммы строк
    cout << endl << "Суммы элементов по строкам:" << endl;
    for (int i = 0; i < rows; i++) {
        double sum = 0;
        for (int j = 0; j < cols; j++) {
            sum += mat[i][j];
        }
        cout << "  Строка " << i+1 << ": " << sum << endl;
    }
    
    // Суммы столбцов
    cout << endl << "Суммы элементов по столбцам:" << endl;
    for (int j = 0; j < cols; j++) {
        double sum = 0;
        for (int i = 0; i < rows; i++) {
            sum += mat[i][j];
        }
        cout << "  Столбец " << j+1 << ": " << sum << endl;
    }
    
    // Сумма всех элементов
    double totalSum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            totalSum += mat[i][j];
        }
    }
    cout << endl << "Общая сумма всех элементов: " << totalSum << endl;
}

// Перестановка строк в матрице
void swapRows(int num) {
    double (*mat)[MAX_SIZE];
    int rows, cols;
    
    if (num == 1) {
        if (rows1 == 0) {
            cout << "Матрица 1 не задана!" << endl;
            return;
        }
        mat = matrix1;
        rows = rows1;
        cols = cols1;
    } else {
        if (rows2 == 0) {
            cout << "Матрица 2 не задана!" << endl;
            return;
        }
        mat = matrix2;
        rows = rows2;
        cols = cols2;
    }
    
    printMatrix(mat, rows, cols, "Исходная матрица");
    
    int row1, row2;
    cout << "Введите номер первой строки (1-" << rows << "): ";
    cin >> row1;
    cout << "Введите номер второй строки (1-" << rows << "): ";
    cin >> row2;
    
    // Проверка корректности
    if (row1 < 1 || row1 > rows || row2 < 1 || row2 > rows) {
        cout << "Некорректные номера строк!" << endl;
        return;
    }
    
    // Перевод в индексы с нуля
    row1--;
    row2--;
    
    // Перестановка
    for (int j = 0; j < cols; j++) {
        double temp = mat[row1][j];
        mat[row1][j] = mat[row2][j];
        mat[row2][j] = temp;
    }
    
    cout << "Строки " << row1+1 << " и " << row2+1 << " переставлены!" << endl;
    printMatrix(mat, rows, cols, "Результат");
}

// Перестановка столбцов в матрице
void swapCols(int num) {
    double (*mat)[MAX_SIZE];
    int rows, cols;
    
    if (num == 1) {
        if (rows1 == 0) {
            cout << "Матрица 1 не задана!" << endl;
            return;
        }
        mat = matrix1;
        rows = rows1;
        cols = cols1;
    } else {
        if (rows2 == 0) {
            cout << "Матрица 2 не задана!" << endl;
            return;
        }
        mat = matrix2;
        rows = rows2;
        cols = cols2;
    }
    
    printMatrix(mat, rows, cols, "Исходная матрица");
    
    int col1, col2;
    cout << "Введите номер первого столбца (1-" << cols << "): ";
    cin >> col1;
    cout << "Введите номер второго столбца (1-" << cols << "): ";
    cin >> col2;
    
    // Проверка корректности
    if (col1 < 1 || col1 > cols || col2 < 1 || col2 > cols) {
        cout << "Некорректные номера столбцов!" << endl;
        return;
    }
    
    // Перевод в индексы с нуля
    col1--;
    col2--;
    
    // Перестановка
    for (int i = 0; i < rows; i++) {
        double temp = mat[i][col1];
        mat[i][col1] = mat[i][col2];
        mat[i][col2] = temp;
    }
    
    cout << "Столбцы " << col1+1 << " и " << col2+1 << " переставлены!" << endl;
    printMatrix(mat, rows, cols, "Результат");
}

// Сохранение матрицы в файл
void saveMatrixToFile(int num) {
    double (*mat)[MAX_SIZE];
    int rows, cols;
    
    if (num == 1) {
        if (rows1 == 0) {
            cout << "Матрица 1 не задана!" << endl;
            return;
        }
        mat = matrix1;
        rows = rows1;
        cols = cols1;
    } else {
        if (rows2 == 0) {
            cout << "Матрица 2 не задана!" << endl;
            return;
        }
        mat = matrix2;
        rows = rows2;
        cols = cols2;
    }
    
    // Ввод имени файла
    char filename[256];
    cout << "Введите имя файла: ";
    cin >> filename;
    
    // Открытие файла для записи
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    
    // Запись размеров
    outFile << rows << " " << cols << endl;
    
    // Запись элементов
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outFile << mat[i][j];
            if (j < cols - 1) outFile << " ";
        }
        outFile << endl;
    }
    
    outFile.close();
    cout << "Матрица " << num << " успешно сохранена в файл " << filename << endl;
}

// Загрузка матрицы из файла
void loadMatrixFromFile(int num) {
    double (*mat)[MAX_SIZE];
    int *rows, *cols;
    
    if (num == 1) {
        mat = matrix1;
        rows = &rows1;
        cols = &cols1;
    } else {
        mat = matrix2;
        rows = &rows2;
        cols = &cols2;
    }
    
    // Ввод имени файла
    char filename[256];
    cout << "Введите имя файла: ";
    cin >> filename;
    
    // Открытие файла для чтения
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    
    // Чтение размеров
    int r, c;
    inFile >> r >> c;
    
    // Проверка размеров
    if (r < 1 || r > MAX_SIZE || c < 1 || c > MAX_SIZE) {
        cout << "Некорректные размеры матрицы в файле!" << endl;
        inFile.close();
        return;
    }
    
    *rows = r;
    *cols = c;
    
    // Чтение элементов
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            if (!(inFile >> mat[i][j])) {
                cout << "Ошибка чтения данных из файла!" << endl;
                *rows = 0;
                *cols = 0;
                inFile.close();
                return;
            }
        }
    }
    
    inFile.close();
    cout << "Матрица " << num << " успешно загружена из файла " << filename << endl;
    printMatrix(mat, *rows, *cols, num == 1 ? "Матрица 1" : "Матрица 2");
}

// Вспомогательная функция копирования матрицы
void copyMatrix(double src[][MAX_SIZE], double dst[][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dst[i][j] = src[i][j];
        }
    }
}
