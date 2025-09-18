#include <iostream>
#include <bitset>
using namespace std;

int main() {
    setlocale(LC_ALL, "");
    cout << "=== Задание 1.a: Установка 5-го бита в 0 ===" << endl;
    
    // Основной пример из задания
    unsigned char x = 255;  // 8-разрядное двоичное число 11111111
    unsigned char maska = 1; // 1=00000001 – 8-разрядная маска
    
    cout << "x = " << (int)x << endl;
    cout << "x: " << bitset<8>(x) << endl;
    cout << endl;
    
    // Пошаговое выполнение операций
    cout << "" << (int)maska << endl;
    cout << "Двоичное представление маски: " << bitset<8>(maska) << endl;
    
    cout << "Шаг 2: Сдвигаем маску на 4 позиции влево (для 5-го бита)" << endl;
    unsigned char shifted_maska = maska << 4;
    cout << "maska << 4 = " << bitset<8>(shifted_maska) << endl;
    
    cout << "Шаг 3: Инвертируем сдвинутую маску" << endl;
    unsigned char inverted_maska = ~(maska << 4);
    cout << "~(maska << 4) = " << bitset<8>(inverted_maska) << endl;
    
    cout << "Шаг 4: Применяем операцию AND" << endl;
    x = x & (~(maska << 4)); // результат x=239
    
    cout << "Результат x = " << (int)x << endl;
    cout << "Двоичное представление результата: " << bitset<8>(x) << endl;
    cout << endl;
    
    // Проверка на других значениях
    cout << "=== Проверка на других значениях ===" << endl;
    
    unsigned char test_values[] = {0, 127, 200, 63, 31};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        unsigned char original = test_values[i];
        unsigned char result = original & (~(1 << 4));
        
        cout << "x = " << (int)original 
             << " (" << bitset<8>(original) << ") -> " 
             << (int)result 
             << " (" << bitset<8>(result) << ")" << endl;
    }
    
    return 0;
}