/*
 * Курсовая работа по дисциплине "Программирование и алгоритмизация"
 */

#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

using namespace std;

// Структура для хранения результатов анализа
struct TextStats {
    int symbolCount;
    int wordCount;
    int lineCount;
    int spaceCount;
};

// Прототипы функций
void showMenu();
void createFile();
void readFile();
void analyzeFile();
void appendToFile();
TextStats calculateStats(const string& filename);

int main() {
    // Настройка консоли для вывода русского текста
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    int choice;
    
    wcout << L"========================================" << endl;
    wcout << L"  Программа для работы с текстовыми    " << endl;
    wcout << L"           файлами                     " << endl;
    wcout << L"========================================" << endl;
    
    do {
        showMenu();
        wcout << L"Ваш выбор: ";
        
        // Для ввода используем обычный cin
        _setmode(_fileno(stdin), _O_TEXT);
        _setmode(_fileno(stdout), _O_TEXT);
        cin >> choice;
        cin.ignore();
        _setmode(_fileno(stdout), _O_U16TEXT);
        
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
                wcout << L"\nВыход из программы. До свидания!" << endl;
                break;
            default:
                wcout << L"\nОшибка! Неверный пункт меню." << endl;
        }
        
    } while(choice != 0);
    
    return 0;
}

void showMenu() {
    wcout << L"\n----------------------------------------" << endl;
    wcout << L"            ГЛАВНОЕ МЕНЮ               " << endl;
    wcout << L"----------------------------------------" << endl;
    wcout << L"1. Создать новый файл" << endl;
    wcout << L"2. Прочитать файл" << endl;
    wcout << L"3. Анализ файла" << endl;
    wcout << L"4. Дописать в файл" << endl;
    wcout << L"0. Выход" << endl;
    wcout << L"----------------------------------------" << endl;
}

void createFile() {
    string filename;
    string text;
    
    wcout << L"\nВведите имя файла (например: test.txt): ";
    
    _setmode(_fileno(stdout), _O_TEXT);
    getline(cin, filename);
    
    ofstream file(filename.c_str());
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    if (!file.is_open()) {
        wcout << L"Ошибка! Не удалось создать файл." << endl;
        return;
    }
    
    wcout << L"Введите текст (для завершения введите пустую строку):" << endl;
    wcout << L">" << endl;
    
    _setmode(_fileno(stdout), _O_TEXT);
    
    while (true) {
        getline(cin, text);
        if (text.empty()) {
            break;
        }
        file << text << endl;
    }
    
    file.close();
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout << L"\nФайл успешно создан!" << endl;
}

void readFile() {
    string filename;
    string line;
    
    wcout << L"\nВведите имя файла для чтения: ";
    
    _setmode(_fileno(stdout), _O_TEXT);
    getline(cin, filename);
    
    ifstream file(filename.c_str());
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    if (!file.is_open()) {
        wcout << L"Ошибка! Файл не найден." << endl;
        return;
    }
    
    wcout << L"\n--- Содержимое файла ---" << endl;
    
    _setmode(_fileno(stdout), _O_TEXT);
    
    while (getline(file, line)) {
        cout << line << endl;
    }
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout << L"--- Конец файла ---" << endl;
    
    file.close();
}

void analyzeFile() {
    string filename;
    
    wcout << L"\nВведите имя файла для анализа: ";
    
    _setmode(_fileno(stdout), _O_TEXT);
    getline(cin, filename);
    
    ifstream testFile(filename.c_str());
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    if (!testFile.is_open()) {
        wcout << L"Ошибка! Файл не найден." << endl;
        return;
    }
    testFile.close();
    
    TextStats stats = calculateStats(filename);
    
    wcout << L"\n======================================" << endl;
    wcout << L"   РЕЗУЛЬТАТЫ АНАЛИЗА ФАЙЛА" << endl;
    wcout << L"======================================" << endl;
    wcout << L"Количество строк:    " << stats.lineCount << endl;
    wcout << L"Количество слов:     " << stats.wordCount << endl;
    wcout << L"Количество символов: " << stats.symbolCount << endl;
    wcout << L"Количество пробелов: " << stats.spaceCount << endl;
    wcout << L"======================================" << endl;
}

void appendToFile() {
    string filename;
    string text;
    
    wcout << L"\nВведите имя файла для дополнения: ";
    
    _setmode(_fileno(stdout), _O_TEXT);
    getline(cin, filename);
    
    ifstream testFile(filename.c_str());
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    if (!testFile.is_open()) {
        wcout << L"Ошибка! Файл не найден." << endl;
        return;
    }
    testFile.close();
    
    ofstream file(filename.c_str(), ios::app);
    
    if (!file.is_open()) {
        wcout << L"Ошибка! Не удалось открыть файл." << endl;
        return;
    }
    
    wcout << L"Введите текст для добавления (пустая строка - завершить):" << endl;
    wcout << L">" << endl;
    
    _setmode(_fileno(stdout), _O_TEXT);
    
    while (true) {
        getline(cin, text);
        if (text.empty()) {
            break;
        }
        file << text << endl;
    }
    
    file.close();
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout << L"\nТекст успешно добавлен в файл!" << endl;
}

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
