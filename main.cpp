// Программа для учета студентов и их оценок

#include <iostream>
#include <windows.h> // Для работы с русским языком в консоли
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

// Структура для хранения данных о студенте
struct Student {
    int id;              // Уникальный номер студента
    string surname;      // Фамилия
    string name;         // Имя
    string group;        // Группа
    int grades[5];       // Массив оценок (5 предметов)
    double average;      // Средний балл
};

// Глобальный вектор для хранения всех студентов
vector<Student> students;
int nextId = 1; // Счетчик для автоматической генерации ID

// Функция для настройки русского языка в консоли
void setupConsole() {
    SetConsoleCP(1251);        // Устанавливаем кодировку ввода
    SetConsoleOutputCP(1251);  // Устанавливаем кодировку вывода
}

// Функция для расчета среднего балла
double calculateAverage(int grades[5]) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += grades[i];
    }
    return sum / 5.0; // Делим на 5.0 чтобы получить дробное число
}

// Функция для добавления нового студента
void addStudent() {
    Student newStudent; // Создаем нового студента
    newStudent.id = nextId++; // Присваиваем ID и увеличиваем счетчик
    
    cout << "\n=== Добавление нового студента ===" << endl;
    
    // Вводим фамилию
    cout << "Введите фамилию: ";
    cin >> newStudent.surname;
    
    // Вводим имя
    cout << "Введите имя: ";
    cin >> newStudent.name;
    
    // Вводим группу
    cout << "Введите группу: ";
    cin >> newStudent.group;
    
    // Вводим оценки по 5 предметам
    cout << "\nВведите оценки по 5 предметам:" << endl;
    for (int i = 0; i < 5; i++) {
        do {
            cout << "Предмет " << (i + 1) << " (от 2 до 5): ";
            cin >> newStudent.grades[i];
            
            // Проверяем правильность оценки
            if (newStudent.grades[i] < 2 || newStudent.grades[i] > 5) {
                cout << "Ошибка! Оценка должна быть от 2 до 5." << endl;
            }
        } while (newStudent.grades[i] < 2 || newStudent.grades[i] > 5);
    }
    
    // Рассчитываем средний балл
    newStudent.average = calculateAverage(newStudent.grades);
    
    // Добавляем студента в список
    students.push_back(newStudent);
    
    cout << "\nСтудент успешно добавлен! ID: " << newStudent.id << endl;
}

// Функция для вывода всех студентов
void showAllStudents() {
    if (students.empty()) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }
    
    cout << "\n=== Список всех студентов ===" << endl;
    cout << string(80, '-') << endl; // Линия из 80 дефисов
    
    // Выводим заголовки таблицы
    cout << left << setw(5) << "ID" 
         << setw(15) << "Фамилия" 
         << setw(12) << "Имя" 
         << setw(10) << "Группа" 
         << setw(20) << "Оценки" 
         << setw(10) << "Средний" << endl;
    cout << string(80, '-') << endl;
    
    // Выводим данные каждого студента
    for (int i = 0; i < students.size(); i++) {
        cout << left << setw(5) << students[i].id
             << setw(15) << students[i].surname
             << setw(12) << students[i].name
             << setw(10) << students[i].group;
        
        // Выводим оценки
        for (int j = 0; j < 5; j++) {
            cout << students[i].grades[j] << " ";
        }
        
        // Выводим средний балл с двумя знаками после запятой
        cout << "     " << fixed << setprecision(2) << students[i].average << endl;
    }
    cout << string(80, '-') << endl;
}

// Функция для поиска студента по фамилии
void searchStudent() {
    if (students.empty()) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }
    
    string searchSurname;
    cout << "\nВведите фамилию для поиска: ";
    cin >> searchSurname;
    
    bool found = false; // Флаг для отслеживания найденных студентов
    
    cout << "\n=== Результаты поиска ===" << endl;
    
    // Перебираем всех студентов
    for (int i = 0; i < students.size(); i++) {
        // Сравниваем фамилии (без учета регистра не делаем для простоты)
        if (students[i].surname == searchSurname) {
            found = true;
            cout << "\nID: " << students[i].id << endl;
            cout << "ФИО: " << students[i].surname << " " << students[i].name << endl;
            cout << "Группа: " << students[i].group << endl;
            cout << "Оценки: ";
            for (int j = 0; j < 5; j++) {
                cout << students[i].grades[j] << " ";
            }
            cout << "\nСредний балл: " << fixed << setprecision(2) 
                 << students[i].average << endl;
        }
    }
    
    if (!found) {
        cout << "Студенты с фамилией \"" << searchSurname << "\" не найдены." << endl;
    }
}

// Функция для удаления студента по ID
void deleteStudent() {
    if (students.empty()) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }
    
    int deleteId;
    cout << "\nВведите ID студента для удаления: ";
    cin >> deleteId;
    
    // Ищем студента с нужным ID
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == deleteId) {
            cout << "Удаляем студента: " << students[i].surname << " " 
                 << students[i].name << endl;
            students.erase(students.begin() + i); // Удаляем из вектора
            cout << "Студент успешно удален!" << endl;
            return;
        }
    }
    
    cout << "Студент с ID " << deleteId << " не найден." << endl;
}

// Функция для сохранения данных в файл
void saveToFile() {
    ofstream file("students.txt"); // Открываем файл для записи
    
    if (!file.is_open()) {
        cout << "Ошибка при открытии файла для сохранения!" << endl;
        return;
    }
    
    // Записываем количество студентов
    file << students.size() << endl;
    
    // Записываем данные каждого студента
    for (int i = 0; i < students.size(); i++) {
        file << students[i].id << endl;
        file << students[i].surname << endl;
        file << students[i].name << endl;
        file << students[i].group << endl;
        
        // Записываем оценки
        for (int j = 0; j < 5; j++) {
            file << students[i].grades[j] << " ";
        }
        file << endl;
        
        file << students[i].average << endl;
    }
    
    file.close(); // Закрываем файл
    cout << "\nДанные успешно сохранены в файл students.txt" << endl;
}

// Функция для загрузки данных из файла
void loadFromFile() {
    ifstream file("students.txt"); // Открываем файл для чтения
    
    if (!file.is_open()) {
        cout << "\nФайл students.txt не найден. Начинаем с пустого списка." << endl;
        return;
    }
    
    students.clear(); // Очищаем текущий список
    
    int count;
    file >> count; // Читаем количество студентов
    
    // Читаем данные каждого студента
    for (int i = 0; i < count; i++) {
        Student student;
        file >> student.id;
        file >> student.surname;
        file >> student.name;
        file >> student.group;
        
        // Читаем оценки
        for (int j = 0; j < 5; j++) {
            file >> student.grades[j];
        }
        
        file >> student.average;
        
        students.push_back(student); // Добавляем студента в список
        
        // Обновляем счетчик ID
        if (student.id >= nextId) {
            nextId = student.id + 1;
        }
    }
    
    file.close(); // Закрываем файл
    cout << "\nДанные успешно загружены из файла. Загружено студентов: " << count << endl;
}

// Функция для показа статистики
void showStatistics() {
    if (students.empty()) {
        cout << "\nСписок студентов пуст!" << endl;
        return;
    }
    
    cout << "\n=== Статистика ===" << endl;
    cout << "Всего студентов: " << students.size() << endl;
    
    // Находим студента с максимальным средним баллом
    double maxAverage = students[0].average;
    int maxIndex = 0;
    
    for (int i = 1; i < students.size(); i++) {
        if (students[i].average > maxAverage) {
            maxAverage = students[i].average;
            maxIndex = i;
        }
    }
    
    cout << "\nЛучший студент:" << endl;
    cout << "ФИО: " << students[maxIndex].surname << " " 
         << students[maxIndex].name << endl;
    cout << "Средний балл: " << fixed << setprecision(2) 
         << students[maxIndex].average << endl;
    
    // Считаем общий средний балл по всем студентам
    double totalAverage = 0;
    for (int i = 0; i < students.size(); i++) {
        totalAverage += students[i].average;
    }
    totalAverage /= students.size();
    
    cout << "\nОбщий средний балл: " << fixed << setprecision(2) 
         << totalAverage << endl;
}

// Главное меню программы
void showMenu() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  СИСТЕМА УЧЕТА СТУДЕНТОВ И ОЦЕНОК     ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "1. Добавить студента" << endl;
    cout << "2. Показать всех студентов" << endl;
    cout << "3. Найти студента по фамилии" << endl;
    cout << "4. Удалить студента" << endl;
    cout << "5. Показать статистику" << endl;
    cout << "6. Сохранить данные в файл" << endl;
    cout << "7. Загрузить данные из файла" << endl;
    cout << "0. Выход" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Выберите действие: ";
}

// Главная функция программы
int main() {
    setupConsole(); // Настраиваем консоль для русского языка
    
    // Пытаемся загрузить данные при старте
    loadFromFile();
    
    int choice; // Переменная для хранения выбора пользователя
    
    // Основной цикл программы
    do {
        showMenu();
        cin >> choice;
        
        // Обрабатываем выбор пользователя
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                showAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                showStatistics();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                loadFromFile();
                break;
            case 0:
                cout << "\nСпасибо за использование программы!" << endl;
                // Автоматически сохраняем при выходе
                saveToFile();
                break;
            default:
                cout << "\nОшибка! Выберите пункт от 0 до 7." << endl;
        }
        
        // Пауза перед следующей операцией (кроме выхода)
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
            system("cls"); // Очищаем экран
        }
        
    } while (choice != 0); // Выходим когда пользователь выбрал 0
    
    return 0;
}
