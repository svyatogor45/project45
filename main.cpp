// ============================================
// Программа: Система учета студентов и их оценок
// Автор: Студент группы ИТ-21
// Дата: 2024
// Описание: Консольное приложение для ведения
//           учета студентов и их успеваемости
// ============================================

#include <iostream>  // для ввода-вывода (cin, cout)
#include <string>    // для работы со строками
#include <vector>    // для динамических массивов
#include <fstream>   // для работы с файлами
#include <iomanip>   // для форматирования вывода
#include <limits>    // для очистки буфера ввода
#include <windows.h> // для поддержки русского языка в консоли

using namespace std; // чтобы не писать std:: перед каждой командой

// ============================================
// Структура для хранения данных об одном студенте
// ============================================
struct Student {
    int id;              // уникальный номер студента
    string fullName;     // ФИО студента
    string group;        // номер группы
    int mathGrade;       // оценка по математике (1-5)
    int physicsGrade;    // оценка по физике (1-5)
    int programmingGrade;// оценка по программированию (1-5)
};

// ============================================
// Глобальные переменные
// ============================================
vector<Student> students;  // массив для хранения всех студентов
int nextId = 1;           // счетчик для генерации ID
const string FILE_NAME = "students.txt"; // имя файла для сохранения

// ============================================
// Прототипы функций (объявляем заранее)
// ============================================
void showMenu();
void addStudent();
void showAllStudents();
void searchStudent();
void editStudent();
void deleteStudent();
void calculateAverages();
void saveToFile();
void loadFromFile();
void clearInput();
int getValidGrade(const string& subject);
void showStudentDetails(const Student& s);
void pause();

// ============================================
// Главная функция - точка входа в программу
// ============================================
int main() {
    // Настраиваем консоль для корректного отображения русского языка
    SetConsoleCP(65001);       // кодировка ввода UTF-8
    SetConsoleOutputCP(65001); // кодировка вывода UTF-8
    
    // Пробуем загрузить данные из файла при запуске
    loadFromFile();
    
    int choice; // переменная для хранения выбора пользователя
    
    // Главный цикл программы - работает пока пользователь не выберет выход
    do {
        showMenu(); // показываем меню
        
        cout << "Введите номер действия: ";
        cin >> choice;
        
        // Проверяем, не ввел ли пользователь букву вместо цифры
        if (cin.fail()) {
            clearInput();
            cout << "\n[!] Ошибка: введите число от 0 до 8!\n";
            pause();
            continue; // возвращаемся к началу цикла
        }
        
        // Обрабатываем выбор пользователя с помощью switch
        switch (choice) {
            case 1:
                addStudent();      // добавить нового студента
                break;
            case 2:
                showAllStudents(); // показать всех студентов
                break;
            case 3:
                searchStudent();   // найти студента
                break;
            case 4:
                editStudent();     // редактировать студента
                break;
            case 5:
                deleteStudent();   // удалить студента
                break;
            case 6:
                calculateAverages(); // посчитать средние баллы
                break;
            case 7:
                saveToFile();      // сохранить в файл
                break;
            case 8:
                loadFromFile();    // загрузить из файла
                break;
            case 0:
                // Сохраняем данные перед выходом
                saveToFile();
                cout << "\n=== Данные сохранены. До свидания! ===\n";
                break;
            default:
                // Если пользователь ввел неправильное число
                cout << "\n[!] Неверный выбор! Попробуйте снова.\n";
                pause();
        }
        
    } while (choice != 0); // цикл продолжается пока не введут 0
    
    return 0; // программа завершилась успешно
}

// ============================================
// Функция отображения главного меню
// ============================================
void showMenu() {
    // Очищаем экран (работает в Windows)
    system("cls");
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗\n";
    cout << "║     СИСТЕМА УЧЕТА СТУДЕНТОВ И ИХ ОЦЕНОК        ║\n";
    cout << "╠════════════════════════════════════════════════╣\n";
    cout << "║  1. Добавить нового студента                   ║\n";
    cout << "║  2. Показать всех студентов                    ║\n";
    cout << "║  3. Найти студента                             ║\n";
    cout << "║  4. Редактировать данные студента              ║\n";
    cout << "║  5. Удалить студента                           ║\n";
    cout << "║  6. Рассчитать средние баллы                   ║\n";
    cout << "║  7. Сохранить данные в файл                    ║\n";
    cout << "║  8. Загрузить данные из файла                  ║\n";
    cout << "║  0. Выход из программы                         ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
    cout << "\n";
    cout << "Всего студентов в базе: " << students.size() << "\n\n";
}

// ============================================
// Функция добавления нового студента
// ============================================
void addStudent() {
    system("cls");
    cout << "\n=== ДОБАВЛЕНИЕ НОВОГО СТУДЕНТА ===\n\n";
    
    Student newStudent; // создаем новую структуру студента
    
    // Присваиваем уникальный ID
    newStudent.id = nextId;
    nextId++; // увеличиваем счетчик для следующего студента
    
    // Очищаем буфер ввода перед getline
    clearInput();
    
    // Вводим ФИО
    cout << "Введите ФИО студента: ";
    getline(cin, newStudent.fullName);
    
    // Проверяем что ФИО не пустое
    if (newStudent.fullName.empty()) {
        cout << "\n[!] Ошибка: ФИО не может быть пустым!\n";
        nextId--; // откатываем ID назад
        pause();
        return;
    }
    
    // Вводим группу
    cout << "Введите номер группы: ";
    getline(cin, newStudent.group);
    
    if (newStudent.group.empty()) {
        cout << "\n[!] Ошибка: группа не может быть пустой!\n";
        nextId--;
        pause();
        return;
    }
    
    // Вводим оценки с проверкой
    cout << "\nВведите оценки (от 1 до 5):\n";
    newStudent.mathGrade = getValidGrade("Математика");
    newStudent.physicsGrade = getValidGrade("Физика");
    newStudent.programmingGrade = getValidGrade("Программирование");
    
    // Добавляем студента в массив
    students.push_back(newStudent);
    
    cout << "\n[+] Студент успешно добавлен! ID: " << newStudent.id << "\n";
    pause();
}

// ============================================
// Функция для ввода и проверки оценки
// ============================================
int getValidGrade(const string& subject) {
    int grade;
    
    // Цикл будет повторяться пока не введут правильную оценку
    while (true) {
        cout << subject << ": ";
        cin >> grade;
        
        // Проверка на ошибку ввода (если ввели не число)
        if (cin.fail()) {
            clearInput();
            cout << "[!] Введите число от 1 до 5!\n";
            continue;
        }
        
        // Проверка диапазона оценки
        if (grade >= 1 && grade <= 5) {
            return grade; // оценка правильная, возвращаем её
        } else {
            cout << "[!] Оценка должна быть от 1 до 5!\n";
        }
    }
}

// ============================================
// Функция отображения всех студентов
// ============================================
void showAllStudents() {
    system("cls");
    cout << "\n=== СПИСОК ВСЕХ СТУДЕНТОВ ===\n\n";
    
    // Проверяем, есть ли студенты в базе
    if (students.empty()) {
        cout << "[i] База данных пуста. Добавьте студентов.\n";
        pause();
        return;
    }
    
    // Выводим заголовок таблицы
    cout << left; // выравнивание по левому краю
    cout << setw(5) << "ID" 
         << setw(30) << "ФИО" 
         << setw(12) << "Группа"
         << setw(8) << "Матем"
         << setw(8) << "Физика"
         << setw(8) << "Прогр"
         << setw(10) << "Средний" << "\n";
    
    // Рисуем линию-разделитель
    cout << string(81, '-') << "\n";
    
    // Проходим по всем студентам и выводим их данные
    for (int i = 0; i < students.size(); i++) {
        // Считаем средний балл
        double avg = (students[i].mathGrade + 
                      students[i].physicsGrade + 
                      students[i].programmingGrade) / 3.0;
        
        cout << setw(5) << students[i].id
             << setw(30) << students[i].fullName
             << setw(12) << students[i].group
             << setw(8) << students[i].mathGrade
             << setw(8) << students[i].physicsGrade
             << setw(8) << students[i].programmingGrade
             << setw(10) << fixed << setprecision(2) << avg << "\n";
    }
    
    cout << string(81, '-') << "\n";
    cout << "Всего студентов: " << students.size() << "\n";
    
    pause();
}

// ============================================
// Функция поиска студента
// ============================================
void searchStudent() {
    system("cls");
    cout << "\n=== ПОИСК СТУДЕНТА ===\n\n";
    
    if (students.empty()) {
        cout << "[i] База данных пуста.\n";
        pause();
        return;
    }
    
    cout << "Выберите способ поиска:\n";
    cout << "1. По ID\n";
    cout << "2. По ФИО\n";
    cout << "3. По группе\n";
    cout << "\nВаш выбор: ";
    
    int searchType;
    cin >> searchType;
    
    if (cin.fail()) {
        clearInput();
        cout << "[!] Ошибка ввода!\n";
        pause();
        return;
    }
    
    bool found = false; // флаг - нашли ли хоть одного студента
    
    if (searchType == 1) {
        // Поиск по ID
        int searchId;
        cout << "Введите ID студента: ";
        cin >> searchId;
        
        // Ищем студента с таким ID
        for (int i = 0; i < students.size(); i++) {
            if (students[i].id == searchId) {
                cout << "\n[+] Студент найден!\n";
                showStudentDetails(students[i]);
                found = true;
                break; // нашли - выходим из цикла
            }
        }
        
    } else if (searchType == 2) {
        // Поиск по ФИО (частичное совпадение)
        clearInput();
        string searchName;
        cout << "Введите ФИО или его часть: ";
        getline(cin, searchName);
        
        cout << "\nРезультаты поиска:\n";
        cout << string(50, '-') << "\n";
        
        // Ищем всех студентов, у которых ФИО содержит искомую строку
        for (int i = 0; i < students.size(); i++) {
            // Функция find ищет подстроку в строке
            if (students[i].fullName.find(searchName) != string::npos) {
                showStudentDetails(students[i]);
                cout << string(50, '-') << "\n";
                found = true;
            }
        }
        
    } else if (searchType == 3) {
        // Поиск по группе
        clearInput();
        string searchGroup;
        cout << "Введите номер группы: ";
        getline(cin, searchGroup);
        
        cout << "\nСтуденты группы " << searchGroup << ":\n";
        cout << string(50, '-') << "\n";
        
        for (int i = 0; i < students.size(); i++) {
            if (students[i].group == searchGroup) {
                showStudentDetails(students[i]);
                cout << string(50, '-') << "\n";
                found = true;
            }
        }
        
    } else {
        cout << "[!] Неверный выбор!\n";
        pause();
        return;
    }
    
    if (!found) {
        cout << "\n[!] Студенты не найдены.\n";
    }
    
    pause();
}

// ============================================
// Функция вывода подробной информации о студенте
// ============================================
void showStudentDetails(const Student& s) {
    // Считаем средний балл
    double avg = (s.mathGrade + s.physicsGrade + s.programmingGrade) / 3.0;
    
    cout << "ID: " << s.id << "\n";
    cout << "ФИО: " << s.fullName << "\n";
    cout << "Группа: " << s.group << "\n";
    cout << "Оценки:\n";
    cout << "  Математика: " << s.mathGrade << "\n";
    cout << "  Физика: " << s.physicsGrade << "\n";
    cout << "  Программирование: " << s.programmingGrade << "\n";
    cout << "Средний балл: " << fixed << setprecision(2) << avg << "\n";
}

// ============================================
// Функция редактирования данных студента
// ============================================
void editStudent() {
    system("cls");
    cout << "\n=== РЕДАКТИРОВАНИЕ СТУДЕНТА ===\n\n";
    
    if (students.empty()) {
        cout << "[i] База данных пуста.\n";
        pause();
        return;
    }
    
    cout << "Введите ID студента для редактирования: ";
    int editId;
    cin >> editId;
    
    if (cin.fail()) {
        clearInput();
        cout << "[!] Ошибка ввода!\n";
        pause();
        return;
    }
    
    // Ищем студента с таким ID
    int index = -1; // индекс найденного студента (-1 = не найден)
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == editId) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "[!] Студент с ID " << editId << " не найден!\n";
        pause();
        return;
    }
    
    // Показываем текущие данные
    cout << "\nТекущие данные студента:\n";
    showStudentDetails(students[index]);
    
    // Меню редактирования
    cout << "\nЧто редактировать?\n";
    cout << "1. ФИО\n";
    cout << "2. Группу\n";
    cout << "3. Оценку по математике\n";
    cout << "4. Оценку по физике\n";
    cout << "5. Оценку по программированию\n";
    cout << "6. Все оценки\n";
    cout << "0. Отмена\n";
    cout << "\nВаш выбор: ";
    
    int editChoice;
    cin >> editChoice;
    
    clearInput();
    
    switch (editChoice) {
        case 1: {
            cout << "Новое ФИО: ";
            getline(cin, students[index].fullName);
            cout << "[+] ФИО обновлено!\n";
            break;
        }
        case 2: {
            cout << "Новая группа: ";
            getline(cin, students[index].group);
            cout << "[+] Группа обновлена!\n";
            break;
        }
        case 3: {
            students[index].mathGrade = getValidGrade("Новая оценка по математике");
            cout << "[+] Оценка обновлена!\n";
            break;
        }
        case 4: {
            students[index].physicsGrade = getValidGrade("Новая оценка по физике");
            cout << "[+] Оценка обновлена!\n";
            break;
        }
        case 5: {
            students[index].programmingGrade = getValidGrade("Новая оценка по программированию");
            cout << "[+] Оценка обновлена!\n";
            break;
        }
        case 6: {
            cout << "Введите новые оценки:\n";
            students[index].mathGrade = getValidGrade("Математика");
            students[index].physicsGrade = getValidGrade("Физика");
            students[index].programmingGrade = getValidGrade("Программирование");
            cout << "[+] Все оценки обновлены!\n";
            break;
        }
        case 0: {
            cout << "[i] Редактирование отменено.\n";
            break;
        }
        default: {
            cout << "[!] Неверный выбор!\n";
        }
    }
    
    pause();
}

// ============================================
// Функция удаления студента
// ============================================
void deleteStudent() {
    system("cls");
    cout << "\n=== УДАЛЕНИЕ СТУДЕНТА ===\n\n";
    
    if (students.empty()) {
        cout << "[i] База данных пуста.\n";
        pause();
        return;
    }
    
    cout << "Введите ID студента для удаления: ";
    int deleteId;
    cin >> deleteId;
    
    if (cin.fail()) {
        clearInput();
        cout << "[!] Ошибка ввода!\n";
        pause();
        return;
    }
    
    // Ищем студента
    int index = -1;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == deleteId) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "[!] Студент с ID " << deleteId << " не найден!\n";
        pause();
        return;
    }
    
    // Показываем данные студента перед удалением
    cout << "\nВы собираетесь удалить:\n";
    showStudentDetails(students[index]);
    
    // Запрашиваем подтверждение
    cout << "\nВы уверены? (1 - Да, 0 - Нет): ";
    int confirm;
    cin >> confirm;
    
    if (confirm == 1) {
        // Удаляем студента из вектора
        // erase удаляет элемент по итератору (begin + индекс)
        students.erase(students.begin() + index);
        cout << "\n[+] Студент удален!\n";
    } else {
        cout << "\n[i] Удаление отменено.\n";
    }
    
    pause();
}

// ============================================
// Функция расчета средних баллов и статистики
// ============================================
void calculateAverages() {
    system("cls");
    cout << "\n=== СТАТИСТИКА И СРЕДНИЕ БАЛЛЫ ===\n\n";
    
    if (students.empty()) {
        cout << "[i] База данных пуста.\n";
        pause();
        return;
    }
    
    // Переменные для подсчета сумм
    double totalMath = 0;
    double totalPhysics = 0;
    double totalProgramming = 0;
    double totalAll = 0;
    
    int excellentCount = 0;  // отличники (средний >= 4.5)
    int goodCount = 0;       // хорошисты (средний >= 3.5)
    int satisfactoryCount = 0; // удовлетворительно (средний >= 2.5)
    int poorCount = 0;       // неудовлетворительно (средний < 2.5)
    
    // Считаем суммы и статистику
    for (int i = 0; i < students.size(); i++) {
        totalMath += students[i].mathGrade;
        totalPhysics += students[i].physicsGrade;
        totalProgramming += students[i].programmingGrade;
        
        double avg = (students[i].mathGrade + 
                      students[i].physicsGrade + 
                      students[i].programmingGrade) / 3.0;
        totalAll += avg;
        
        // Считаем количество по категориям
        if (avg >= 4.5) {
            excellentCount++;
        } else if (avg >= 3.5) {
            goodCount++;
        } else if (avg >= 2.5) {
            satisfactoryCount++;
        } else {
            poorCount++;
        }
    }
    
    int count = students.size(); // количество студентов
    
    // Выводим результаты
    cout << "Общая статистика:\n";
    cout << string(40, '-') << "\n";
    cout << "Всего студентов: " << count << "\n\n";
    
    cout << "Средние оценки по предметам:\n";
    cout << "  Математика: " << fixed << setprecision(2) << (totalMath / count) << "\n";
    cout << "  Физика: " << fixed << setprecision(2) << (totalPhysics / count) << "\n";
    cout << "  Программирование: " << fixed << setprecision(2) << (totalProgramming / count) << "\n";
    cout << "\n";
    cout << "Общий средний балл: " << fixed << setprecision(2) << (totalAll / count) << "\n\n";
    
    cout << "Распределение студентов:\n";
    cout << "  Отличники (>= 4.5): " << excellentCount << " чел.\n";
    cout << "  Хорошисты (>= 3.5): " << goodCount << " чел.\n";
    cout << "  Удовлетворительно (>= 2.5): " << satisfactoryCount << " чел.\n";
    cout << "  Неудовлетворительно (< 2.5): " << poorCount << " чел.\n";
    
    // Находим лучшего студента
    double maxAvg = 0;
    int bestIndex = 0;
    for (int i = 0; i < students.size(); i++) {
        double avg = (students[i].mathGrade + 
                      students[i].physicsGrade + 
                      students[i].programmingGrade) / 3.0;
        if (avg > maxAvg) {
            maxAvg = avg;
            bestIndex = i;
        }
    }
    
    cout << "\nЛучший студент:\n";
    cout << "  " << students[bestIndex].fullName;
    cout << " (средний балл: " << fixed << setprecision(2) << maxAvg << ")\n";
    
    pause();
}

// ============================================
// Функция сохранения данных в файл
// ============================================
void saveToFile() {
    // Открываем файл для записи
    ofstream file(FILE_NAME);
    
    // Проверяем, открылся ли файл
    if (!file.is_open()) {
        cout << "\n[!] Ошибка: не удалось открыть файл для записи!\n";
        pause();
        return;
    }
    
    // Сначала записываем значение nextId
    file << nextId << "\n";
    
    // Записываем количество студентов
    file << students.size() << "\n";
    
    // Записываем каждого студента
    for (int i = 0; i < students.size(); i++) {
        file << students[i].id << "\n";
        file << students[i].fullName << "\n";
        file << students[i].group << "\n";
        file << students[i].mathGrade << "\n";
        file << students[i].physicsGrade << "\n";
        file << students[i].programmingGrade << "\n";
    }
    
    file.close(); // закрываем файл
    
    cout << "\n[+] Данные успешно сохранены в файл " << FILE_NAME << "!\n";
    pause();
}

// ============================================
// Функция загрузки данных из файла
// ============================================
void loadFromFile() {
    // Открываем файл для чтения
    ifstream file(FILE_NAME);
    
    // Проверяем, существует ли файл
    if (!file.is_open()) {
        // Файл не найден - это нормально при первом запуске
        return;
    }
    
    // Очищаем текущий массив студентов
    students.clear();
    
    // Читаем nextId
    file >> nextId;
    
    // Читаем количество студентов
    int count;
    file >> count;
    file.ignore(); // пропускаем символ новой строки после числа
    
    // Читаем каждого студента
    for (int i = 0; i < count; i++) {
        Student s;
        
        file >> s.id;
        file.ignore(); // пропускаем перенос строки
        
        getline(file, s.fullName);
        getline(file, s.group);
        
        file >> s.mathGrade;
        file >> s.physicsGrade;
        file >> s.programmingGrade;
        file.ignore();
        
        students.push_back(s);
    }
    
    file.close();
    
    cout << "[i] Загружено студентов из файла: " << students.size() << "\n";
}

// ============================================
// Вспомогательная функция очистки буфера ввода
// ============================================
void clearInput() {
    cin.clear(); // сбрасываем флаг ошибки
    // Игнорируем все символы в буфере до конца строки
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ============================================
// Функция паузы - ждет нажатия Enter
// ============================================
void pause() {
    cout << "\nНажмите Enter для продолжения...";
    clearInput();
    cin.get(); // ждем нажатия Enter
}
