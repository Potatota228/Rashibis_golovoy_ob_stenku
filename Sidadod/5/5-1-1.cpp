#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset> //��� ������ � ������� ������������
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    cout << "=== ������� 1a: �������� ������� ===" << endl;
    
    // ������ �� �������
    unsigned char x = 255;  // 11111111
    unsigned char maska = 1; // 00000001
    cout << "�������� x = " << (int)x << " (��������: " << bitset<8>(x) << ")" << endl;
    
    x = x & (~(maska << 4)); // ������������� 5-� ��� � 0
    cout << "��������� x = " << (int)x << " (��������: " << bitset<8>(x) << ")" << endl;
    
    // �� ������ ��������� x
    cout << "\n�������� �� ������ ���������:" << endl;
    unsigned char test_values[] = {170, 85, 31, 0}; // 10101010, 01010101, 00011111, 00000000
    
    for(int i = 0; i < 4; i++) {
        unsigned char original = test_values[i];
        unsigned char result = original & (~(maska << 4));
        cout << "x = " << (int)original << " (" << bitset<8>(original) << ") -> " 
             << (int)result << " (" << bitset<8>(result) << ")" << endl;
    }
    
    cout << "\n=== ������� 1�: ��������� 7-�� ���� � 1 ===" << endl;
    
    // ��� ��������� 7-�� ���� � ������� ���������� OR � ������
    unsigned char x2 = 25; // ������ �����
    unsigned char maska2 = 1;
    
    cout << "�������� x = " << (int)x2 << " (��������: " << bitset<8>(x2) << ")" << endl;
    
    x2 = x2 | (maska2 << 6); // ������������� 7-� ��� � ������� (����� �� 6, ��� ��� ���� ���������� � 0)
    cout << "��������� x = " << (int)x2 << " (��������: " << bitset<8>(x2) << ")" << endl;
    
    cout << "\n=== ������� 1�: ���������� �������� 1* ===" << endl;
    
    // ������������ ������ ��������� �� �������� 1*
    cout << "\n������������ ���������:" << endl;
    unsigned int demo_x = 25;
    const int demo_n = sizeof(int) * 8; // ���������� ����� � int
    unsigned int demo_mask = (1 << (demo_n - 1));
    
    cout << "����� " << demo_x << " � �������� ����: ";
    for (int i = 1; i <= demo_n; i++) {
        cout << ((demo_x & demo_mask) >> (demo_n - i));
        demo_mask = demo_mask >> 1;
        if (i % 4 == 0 && i < demo_n) cout << " "; // ����������� ��� ��������
    }
    cout << endl;
    
    system("pause");
    return 0;
}