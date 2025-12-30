/*
 * Курсовая работа по дисциплине "Программирование и алгоритмизация"
 * Тема: Программа для работы с текстовыми файлами
 * 
 * Программа выполняет:
 * - Чтение текстового файла
 * - Запись в текстовый файл
 * - Анализ текста (подсчет символов, слов, строк)
 */

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>

using namespace std;

// Структура для хранения результатов анализа текста
struct TextStats {
    int symbolCount;
    int wordCount;
    int lineCount;
    int spaceCount;
};

// Прототипы функций
void setupConsole();
void showMenu();
void createFile();
void readFile();
void analyzeFile();
void appendToFile();
TextStats calculateStats(const string& filename);

int main() {
    setupConsole();
    
    int choice;
    
    cout << "========================================" << endl;
    cout << "  Программа для работы с текстовыми    " << endl;
    cout << "           файлами                     " << endl;
    cout << "========================================" << endl;
    
    do {
        showMenu();
        cin >> choice;
        cin.ignore(1000, '\n');
        
        switch(choice) {
            case 1:
                createFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                analyzeFile();
                break;
            case 4:
                appendToFile();
                break;
            case 0:
                cout << "\nВыход из программы. До свидания!" << endl;
                break;
            default:
                cout << "\nОшибка! Неверный пункт меню." << endl;
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter...";
            cin.get();
            system("cls");
        }
        
    } while(choice != 0);
    
    return 0;
}

// Настройка консоли для русского языка
void setupConsole() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}
}

// Функция отображения меню
void showMenu() {
    cout << "\n----------------------------------------" << endl;
    cout << "            ГЛАВНОЕ МЕНЮ               " << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. Создать новый файл" << endl;
    cout << "2. Прочитать файл" << endl;
    cout << "3. Анализ файла" << endl;
    cout << "4. Дописать в файл" << endl;
    cout << "0. Выход" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Ваш выбор: ";
}

// Функция создания нового файла
void createFile() {
    string filename;
    string text;
    
    cout << "\n=== Создание файла ===" << endl;
    cout << "Введите имя файла (например: test.txt): ";
    getline(cin, filename);
    
    ofstream file(filename.c_str());
    
    if (!file.is_open()) {
        cout << "Ошибка! Не удалось создать файл." << endl;
        return;
    }
    
    cout << "Введите текст (пустая строка - завершить):" << endl;
    cout << ">" << endl;
    
    while (true) {
        getline(cin, text);
        if (text.empty()) {
            break;
        }
        file << text << endl;
    }
    
    file.close();
    cout << "\nФайл '" << filename << "' успешно создан!" << endl;
}

// Функция чтения файла
void readFile() {
    string filename;
    string line;
    
    cout << "\n=== Чтение файла ===" << endl;
    cout << "Введите имя файла: ";
    getline(cin, filename);
    
    ifstream file(filename.c_str());
    
    if (!file.is_open()) {
        cout << "Ошибка! Файл '" << filename << "' не найден." << endl;
        return;
    }
    
    cout << "\n--- Содержимое файла ---" << endl;
    
    while (getline(file, line)) {
        cout << line << endl;
    }
    
    cout << "--- Конец файла ---" << endl;
    
    file.close();
}

// Функция анализа файла
void analyzeFile() {
    string filename;
    
    cout << "\n=== Анализ файла ===" << endl;
    cout << "Введите имя файла: ";
    getline(cin, filename);
    
    ifstream testFile(filename.c_str());
    if (!testFile.is_open()) {
        cout << "Ошибка! Файл '" << filename << "' не найден." << endl;
        return;
    }
    testFile.close();
    
    TextStats stats = calculateStats(filename);
    
    cout << "\n======================================" << endl;
    cout << "   РЕЗУЛЬТАТЫ АНАЛИЗА" << endl;
    cout << "======================================" << endl;
    cout << "Файл: " << filename << endl;
    cout << "--------------------------------------" << endl;
    cout << "Строк:    " << stats.lineCount << endl;
    cout << "Слов:     " << stats.wordCount << endl;
    cout << "Символов: " << stats.symbolCount << endl;
    cout << "Пробелов: " << stats.spaceCount << endl;
    cout << "======================================" << endl;
}

// Функция добавления текста в файл
void appendToFile() {
    string filename;
    string text;
    
    cout << "\n=== Дополнение файла ===" << endl;
    cout << "Введите имя файла: ";
    getline(cin, filename);
    
    ifstream testFile(filename.c_str());
    if (!testFile.is_open()) {
        cout << "Ошибка! Файл '" << filename << "' не найден." << endl;
        return;
    }
    testFile.close();
    
    ofstream file(filename.c_str(), ios::app);
    
    if (!file.is_open()) {
        cout << "Ошибка! Не удалось открыть файл." << endl;
        return;
    }
    
    cout << "Введите текст (пустая строка - завершить):" << endl;
    cout << ">" << endl;
    
    while (true) {
        getline(cin, text);
        if (text.empty()) {
            break;
        }
        file << text << endl;
    }
    
    file.close();
    cout << "\nТекст добавлен!" << endl;
}

// Функция подсчета статистики
TextStats calculateStats(const string& filename) {
    TextStats stats;
    stats.symbolCount = 0;
    stats.wordCount = 0;
    stats.lineCount = 0;
    stats.spaceCount = 0;
    
    ifstream file(filename.c_str());
    string line;
    
    while (getline(file, line)) {
        stats.lineCount++;
        
        bool inWord = false;
        
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            stats.symbolCount++;
            
            if (c == ' ') {
                stats.spaceCount++;
                inWord = false;
            }
            else if (!inWord) {
                stats.wordCount++;
                inWord = true;
            }
        }
    }
    
    file.close();
    return stats;
}
