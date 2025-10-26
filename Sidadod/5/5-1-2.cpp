#include <iostream>
#include <vector>
#include <bitset>
#include <Windows.h>
using namespace std;

// Функция для настройки консоли
void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

// Задание 2.а - сортировка до 8 чисел (0-7) с помощью unsigned char
void task2a() {
    cout << "=== Задание 2.а - Сортировка до 8 чисел (0-7) ===" << endl;
    
    vector<int> numbers; //Вектор для хранения введенных чисел
    int n, num;
    
    cout << "Введите количество чисел (до 8): ";
    cin >> n;
    
    if (n > 8) {
        cout << "Слишком много чисел! Максимум 8." << endl;
        return;
    }
    
    cout << "Введите числа от 0 до 7: ";
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num < 0 || num > 7) {
            cout << "Число " << num << " вне диапазона [0-7]!" << endl;
            return;
        }
        numbers.push_back(num);
    }
    
    cout << "Исходный набор: ";
    for (int x : numbers) cout << x << " ";
    cout << endl;
    
    // Создание битового массива
    unsigned char bitArray = 0;
    
    // Установка битов для каждого числа
    for (int num : numbers) {
        bitArray |= (1 << num);  // Устанавливаем бит в позиции num. Операция побитового ИЛИ с присваиванием
    }
    
    cout << "Битовый массив: " << bitset<8>(bitArray) << endl;
    
    // Извлечение отсортированных чисел
    cout << "Отсортированный набор: ";
    for (int i = 0; i < 8; i++) {
        if (bitArray & (1 << i)) {  // Проверяем установлен ли бит i
            cout << i << " ";
        }
    }
    cout << endl << endl;
}

// Задание 2.б - сортировка до 64 чисел (0-63) с помощью unsigned long long
void task2b() {
    cout << "=== Задание 2.б - Сортировка до 64 чисел (0-63) ===" << endl;
    
    vector<int> numbers;
    int n, num;
    
    cout << "Введите количество чисел (до 64): ";
    cin >> n;
    
    if (n > 64) {
        cout << "Слишком много чисел! Максимум 64." << endl;
        return;
    }
    
    cout << "Введите числа от 0 до 63: ";
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num < 0 || num > 63) {
            cout << "Число " << num << " вне диапазона [0-63]!" << endl;
            return;
        }
        numbers.push_back(num);
    }
    
    cout << "Исходный набор: ";
    for (int x : numbers) cout << x << " ";
    cout << endl;
    
    // Создание битового массива
    unsigned long long bitArray = 0;
    
    // Установка битов для каждого числа
    for (int num : numbers) {
        bitArray |= (1ULL << num);  // Устанавливаем бит в позиции num
    }
    
    cout << "Битовый массив (64 бита): " << bitset<64>(bitArray) << endl;
    
    // Извлечение отсортированных чисел
    cout << "Отсортированный набор: ";
    for (int i = 0; i < 64; i++) {
        if (bitArray & (1ULL << i)) {  // Проверяем установлен ли бит i
            cout << i << " ";
        }
    }
    cout << endl << endl;
}

// Задание 2.в - сортировка 64 чисел с помощью массива unsigned char
void task2c() {
    cout << "=== Задание 2.в - Сортировка 64 чисел через массив unsigned char ===" << endl;
    
    vector<int> numbers;
    int n, num;
    
    cout << "Введите количество чисел (до 64): ";
    cin >> n;
    
    if (n > 64) {
        cout << "Слишком много чисел! Максимум 64." << endl;
        return;
    }
    
    cout << "Введите числа от 0 до 63: ";
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num < 0 || num > 63) {
            cout << "Число " << num << " вне диапазона [0-63]!" << endl;
            return;
        }
        numbers.push_back(num);
    }
    
    cout << "Исходный набор: ";
    for (int x : numbers) cout << x << " ";
    cout << endl;
    
    // Создание массива битовых полей (8 байт = 64 бита)
    const int ARRAY_SIZE = 8;  // 8 байт * 8 бит = 64 бита
    unsigned char bitArray[ARRAY_SIZE] = {0};
    
    // Установка битов для каждого числа
    for (int num : numbers) {
        int byteIndex = num / 8;      // Определяем индекс байта
        int bitIndex = num % 8;       // Определяем позицию бита в байте
        bitArray[byteIndex] |= (1 << bitIndex);
    }
    
    // Вывод битового массива
    cout << "Битовый массив (8 байт): ";
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << bitset<8>(bitArray[i]) << " ";
    }
    cout << endl;
    
    // Извлечение отсортированных чисел
    cout << "Отсортированный набор: ";
    for (int i = 0; i < 64; i++) {
        int byteIndex = i / 8;
        int bitIndex = i % 8;
        if (bitArray[byteIndex] & (1 << bitIndex)) {
            cout << i << " ";
        }
    }
    cout << endl << endl;
}

// Демонстрация с предустановками
void demonstration() {
    cout << "=== Демонстрация всех методов ===" << endl;
    
    // Демо для задания 2.а
    cout << "\nДемо 2.а - набор {1, 0, 5, 7, 2, 4}:" << endl;
    vector<int> demo1 = {1, 0, 5, 7, 2, 4};
    unsigned char bitArray1 = 0;
    
    for (int num : demo1) {
        bitArray1 |= (1 << num);
    }
    
    cout << "Исходный: ";
    for (int x : demo1) cout << x << " ";
    cout << endl;
    cout << "Битовый массив: " << bitset<8>(bitArray1) << endl;
    cout << "Отсортированный: ";
    for (int i = 0; i < 8; i++) {
        if (bitArray1 & (1 << i)) cout << i << " ";
    }
    cout << endl;
    
    // Демо для задания 2.б
    cout << "\nДемо 2.б - набор {15, 3, 45, 63, 0, 32}:" << endl;
    vector<int> demo2 = {15, 3, 45, 63, 0, 32};
    unsigned long long bitArray2 = 0;
    
    for (int num : demo2) {
        bitArray2 |= (1ULL << num);
    }
    
    cout << "Исходный: ";
    for (int x : demo2) cout << x << " ";
    cout << endl;
    cout << "Отсортированный: ";
    for (int i = 0; i < 64; i++) {
        if (bitArray2 & (1ULL << i)) cout << i << " ";
    }
    cout << endl;
    
    // Демо для задания 2.в
    cout << "\nДемо 2.в - тот же набор через массив байт:" << endl;
    unsigned char bitArray3[8] = {0};
    
    for (int num : demo2) {
        int byteIndex = num / 8;
        int bitIndex = num % 8;
        bitArray3[byteIndex] |= (1 << bitIndex);
    }
    
    cout << "Отсортированный: ";
    for (int i = 0; i < 64; i++) {
        int byteIndex = i / 8;
        int bitIndex = i % 8;
        if (bitArray3[byteIndex] & (1 << bitIndex)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    setupConsole();
    
    int choice;
    
    while (true) {
        cout << "\n=== Меню ===" << endl;
        cout << "1. Задание 2.а (до 8 чисел, 0-7)" << endl;
        cout << "2. Задание 2.б (до 64 чисел, 0-63, long long)" << endl;
        cout << "3. Задание 2.в (до 64 чисел, массив char)" << endl;
        cout << "4. Демонстрация всех методов" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите пункт: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1: task2a(); break;
            case 2: task2b(); break;
            case 3: task2c(); break;
            case 4: demonstration(); break;
            case 0: return 0;
            default: cout << "Выберите валидное число" << endl;
        }
    }
    
    return 0;
}