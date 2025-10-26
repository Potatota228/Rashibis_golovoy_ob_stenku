#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset> //для работы с битовым отображением
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    cout << "=== Задание 1a: Проверка примера ===" << endl;
    
    // Пример из условия
    unsigned char x = 255;  // 11111111
    unsigned char maska = 1; // 00000001
    cout << "Исходное x = " << (int)x << " (двоичное: " << bitset<8>(x) << ")" << endl;
    
    x = x & (~(maska << 4)); // Устанавливаем 5-й бит в 0
    cout << "Результат x = " << (int)x << " (двоичное: " << bitset<8>(x) << ")" << endl;
    
    // На других значениях x
    cout << "\nПроверка на других значениях:" << endl;
    unsigned char test_values[] = {170, 85, 31, 0}; // 10101010, 01010101, 00011111, 00000000
    
    for(int i = 0; i < 4; i++) {
        unsigned char original = test_values[i];
        unsigned char result = original & (~(maska << 4));
        cout << "x = " << (int)original << " (" << bitset<8>(original) << ") -> " 
             << (int)result << " (" << bitset<8>(result) << ")" << endl;
    }
    
    cout << "\n=== Задание 1б: Установка 7-го бита в 1 ===" << endl;
    
    // Для установки 7-го бита в единицу используем OR с маской
    unsigned char x2 = 25; // Пример числа
    unsigned char maska2 = 1;
    
    cout << "Исходное x = " << (int)x2 << " (двоичное: " << bitset<8>(x2) << ")" << endl;
    
    x2 = x2 | (maska2 << 6); // Устанавливаем 7-й бит в единицу (сдвиг на 6, так как биты нумеруются с 0)
    cout << "Результат x = " << (int)x2 << " (двоичное: " << bitset<8>(x2) << ")" << endl;
    
    cout << "\n=== Задание 1в: реализация листинга 1* ===" << endl;
    
    // Демонстрация работы алгоритма из листинга 1*
    cout << "\nДемонстрация алгоритма:" << endl;
    unsigned int demo_x = 25;
    const int demo_n = sizeof(int) * 8; // количество битов в int
    unsigned int demo_mask = (1 << (demo_n - 1));
    
    cout << "Число " << demo_x << " в двоичном виде: ";
    for (int i = 1; i <= demo_n; i++) {
        cout << ((demo_x & demo_mask) >> (demo_n - i));
        demo_mask = demo_mask >> 1;
        if (i % 4 == 0 && i < demo_n) cout << " "; // Разделитель для удобства
    }
    cout << endl;
    
    system("pause");
    return 0;
}