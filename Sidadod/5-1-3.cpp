#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <Windows.h>
#include <cstdlib>
using namespace std;
using namespace chrono;

// Функция для настройки консоли
void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

// Класс для работы с битовым массивом
class BitArray {
private:
    vector<unsigned char> bits;
    size_t maxValue;
    
public:
    BitArray(size_t maxVal) : maxValue(maxVal) {
        // Вычисляем необходимое количество байт
        size_t bytesNeeded = (maxValue + 7) / 8;
        bits.resize(bytesNeeded, 0);
    }
    
    // Установить бит в позиции value
    void setBit(size_t value) {
        if (value <= maxValue) {
            size_t byteIndex = value / 8;
            size_t bitIndex = value % 8;
            bits[byteIndex] |= (1 << bitIndex);
        }
    }
    
    // Проверить установлен ли бит в позиции value
    bool getBit(size_t value) const {
        if (value <= maxValue) {
            size_t byteIndex = value / 8;
            size_t bitIndex = value % 8;
            return (bits[byteIndex] & (1 << bitIndex)) != 0;
        }
        return false;
    }
    
    // Получить размер массива в байтах
    size_t getSizeInBytes() const {
        return bits.size();
    }
    
    // Получить максимальное значение
    size_t getMaxValue() const {
        return maxValue;
    }
};

// Создание тестового файла
void createTestFile(const string& filename, size_t count, size_t maxValue) {
    cout << "Создание тестового файла..." << endl;
    
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }
    
    // Генератор случайных чисел
    random_device rd;
    mt19937 gen(rd()); //генератор псевдослучайных чисел
    uniform_int_distribution<size_t> dis(1000000, maxValue); //рАВНОМЕРНОЕ РАСПРЕДЕЛЕНИЕ В ДИАПАЗОНЕ
    
    // Используем set для избежания дубликатов
    vector<bool> used(maxValue + 1, false); //Отслеживание использованных чисел
    size_t written = 0;
    
    while (written < count) {
        size_t num = dis(gen);
        if (!used[num]) {
            file << num << "\n";
            used[num] = true;
            written++;
        }
    }
    
    file.close();
    cout << "Файл создан: " << count << " чисел" << endl;
}

// Задание 3.а - сортировка файла с замером времени
void task3a() {
    cout << "=== Задание 3.а - Сортировка файла ===" << endl;
    
    const size_t MAX_VALUE = 9999999;  // Максимальное 7-значное число
    const size_t MAX_NUMBERS = 1000000; // Максимальное количество чисел для теста
    
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    
    // Вычисляем максимальный размер битового массива для 1МБ
    const size_t MAX_MEMORY_BYTES = 1024 * 1024; // 1 МБ = 1,048,576 байт
    size_t maxBits = MAX_MEMORY_BYTES * 8; //8,388,608 бит
    size_t actualMaxValue = min(MAX_VALUE, maxBits - 1); //8,388,608
    
    cout << "Максимальное значение для 1МБ памяти: " << actualMaxValue << endl;
    
    // Определяем количество чисел для теста
    size_t testCount;
    cout << "Введите количество чисел для теста (до " << MAX_NUMBERS << "): ";
    cin >> testCount;
    
    if (testCount > MAX_NUMBERS) {
        testCount = MAX_NUMBERS;
        cout << "Установлено максимальное значение: " << testCount << endl;
    }
    
    // Создание тестового файла
    createTestFile(inputFile, testCount, actualMaxValue);
    
    // Начало замера времени сортировки
    auto startTime = high_resolution_clock::now();
    
    // Создание битового массива
    BitArray bitArray(actualMaxValue);
    
    // Чтение файла и заполнение битового массива
    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cout << "Ошибка открытия входного файла!" << endl;
        return;
    }
    
    size_t number;
    size_t numbersRead = 0;
    while (inFile >> number && numbersRead < testCount) {
        if (number <= actualMaxValue) {
            bitArray.setBit(number);
            numbersRead++;
        }
    }
    inFile.close();
    
    cout << "Прочитано чисел: " << numbersRead << endl;
    
    // Запись отсортированных чисел в выходной файл
    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cout << "Ошибка создания выходного файла!" << endl;
        return;
    }
    
    size_t sortedCount = 0;
    for (size_t i = 0; i <= actualMaxValue; i++) {
        if (bitArray.getBit(i)) {
            outFile << i << "\n";
            sortedCount++;
        }
    }
    outFile.close();
    
    // Окончание замера времени
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);
    
    cout << "Записано отсортированных чисел: " << sortedCount << endl;
    cout << "Время сортировки: " << duration.count() << " мс" << endl;
    cout << "Время сортировки: " << duration.count() / 1000.0 << " с" << endl;
    cout << "Размер битового массива: " << bitArray.getSizeInBytes() << " байт" << endl;
    cout << "Размер битового массива: " << bitArray.getSizeInBytes() / 1024.0 << " КБ" << endl;
}

// Задание 3.б - определение объема памяти битового массива
void task3b() {
    cout << "\n=== Задание 3.б - Определение объема памяти ===" << endl;
    
    // Различные тестовые размеры
    vector<size_t> testSizes = {
        100,          // 100 чисел
        1000,         // 1 тысяча
        10000,        // 10 тысяч
        100000,       // 100 тысяч
        1000000,      // 1 миллион
        8388608,      // 1 МБ в битах (1024*1024*8)
        10000000      // 10 миллионов
    };
    
    cout << "\nАнализ требований к памяти для различных размеров:" << endl;
    cout << "Макс. значение\tБайт\t\tКБ\t\tМБ" << endl;
    cout << "----------------------------------------------" << endl;
    
    for (size_t maxVal : testSizes) {
        BitArray testArray(maxVal);
        size_t bytes = testArray.getSizeInBytes();
        double kb = bytes / 1024.0;
        double mb = kb / 1024.0;
        
        cout << maxVal << "\t\t" << bytes << "\t\t" 
             << kb << "\t" << mb << endl;
    }
    
    // Определение максимального количества чисел для 1МБ
    const size_t MAX_MEMORY = 1024 * 1024; // 1 МБ
    size_t maxNumbersFor1MB = MAX_MEMORY * 8; // каждый бит может представлять одно число
    
    cout << "\nДля ограничения в 1 МБ:" << endl;
    cout << "Максимальное значение числа: " << maxNumbersFor1MB - 1 << endl;
    cout << "Максимальное количество различных чисел: " << maxNumbersFor1MB << endl;
    
    // Практический тест с 1МБ
    BitArray array1MB(maxNumbersFor1MB - 1);
    cout << "Реальный размер битового массива для 1МБ: " << array1MB.getSizeInBytes() << " байт" << endl;
    
    // Тест производительности доступа к битам
    cout << "\nТест производительности операций с битами:" << endl;
    
    auto start = high_resolution_clock::now();
    
    // Установка каждого 100-го бита
    for (size_t i = 0; i < maxNumbersFor1MB; i += 100) {
        array1MB.setBit(i);
    }
    
    auto middle = high_resolution_clock::now();
    
    // Проверка каждого бита
    size_t setBitsCount = 0;
    for (size_t i = 0; i < maxNumbersFor1MB; i++) {
        if (array1MB.getBit(i)) {
            setBitsCount++;
        }
    }
    
    auto end = high_resolution_clock::now();
    
    auto setTime = duration_cast<microseconds>(middle - start);
    auto readTime = duration_cast<microseconds>(end - middle);
    
    cout << "Время установки битов: " << setTime.count() << " мкс" << endl;
    cout << "Время чтения всех битов: " << readTime.count() << " мкс" << endl;
    cout << "Найдено установленных битов: " << setBitsCount << endl;
}

// Демонстрация с небольшим файлом
void demonstrateSmallExample() {
    cout << "\n=== Демонстрация на малом примере ===" << endl;
    
    // Создаем небольшой тестовый файл
    string demoInput = "demo_input.txt";
    string demoOutput = "demo_output.txt";
    
    // Записываем несколько чисел в файл
    ofstream demoFile(demoInput);
    vector<int> demoNumbers = {1000015, 1000003, 1000027, 1000001, 1000099, 1000050};
    
    cout << "Исходные числа: ";
    for (int num : demoNumbers) {
        demoFile << num << "\n";
        cout << num << " ";
    }
    cout << endl;
    demoFile.close();
    
    // Сортировка
    const size_t DEMO_MAX = 1000100;
    BitArray demoBitArray(DEMO_MAX);
    
    // Чтение и установка битов
    ifstream inFile(demoInput);
    size_t num;
    while (inFile >> num) {
        demoBitArray.setBit(num);
    }
    inFile.close();
    
    // Запись результата
    ofstream outFile(demoOutput);
    cout << "Отсортированные числа: ";
    for (size_t i = 0; i <= DEMO_MAX; i++) {
        if (demoBitArray.getBit(i)) {
            outFile << i << "\n";
            cout << i << " ";
        }
    }
    cout << endl;
    outFile.close();
    
    cout << "Размер битового массива: " << demoBitArray.getSizeInBytes() << " байт" << endl;
}

int main() {
    setupConsole();
    
    int choice;
    
    while (true) {
        cout << "\n=== Меню ===" << endl;
        cout << "1. Задание 3.а - Сортировка большого файла" << endl;
        cout << "2. Задание 3.б - Анализ объема памяти" << endl;
        cout << "3. Демонстрация на малом примере" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите пункт: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1: task3a(); break;
            case 2: task3b(); break;
            case 3: demonstrateSmallExample(); break;
            case 0: return 0;
            default: cout << "Неверный выбор!" << endl;
        }
    }
    
    return 0;
}