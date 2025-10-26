#include <iostream>
#include <vector>
#include <bitset>
#include <Windows.h>
using namespace std;

// ������� ��� ��������� �������
void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

// ������� 2.� - ���������� �� 8 ����� (0-7) � ������� unsigned char
void task2a() {
    cout << "=== ������� 2.� - ���������� �� 8 ����� (0-7) ===" << endl;
    
    vector<int> numbers; //������ ��� �������� ��������� �����
    int n, num;
    
    cout << "������� ���������� ����� (�� 8): ";
    cin >> n;
    
    if (n > 8) {
        cout << "������� ����� �����! �������� 8." << endl;
        return;
    }
    
    cout << "������� ����� �� 0 �� 7: ";
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num < 0 || num > 7) {
            cout << "����� " << num << " ��� ��������� [0-7]!" << endl;
            return;
        }
        numbers.push_back(num);
    }
    
    cout << "�������� �����: ";
    for (int x : numbers) cout << x << " ";
    cout << endl;
    
    // �������� �������� �������
    unsigned char bitArray = 0;
    
    // ��������� ����� ��� ������� �����
    for (int num : numbers) {
        bitArray |= (1 << num);  // ������������� ��� � ������� num. �������� ���������� ��� � �������������
    }
    
    cout << "������� ������: " << bitset<8>(bitArray) << endl;
    
    // ���������� ��������������� �����
    cout << "��������������� �����: ";
    for (int i = 0; i < 8; i++) {
        if (bitArray & (1 << i)) {  // ��������� ���������� �� ��� i
            cout << i << " ";
        }
    }
    cout << endl << endl;
}

// ������� 2.� - ���������� �� 64 ����� (0-63) � ������� unsigned long long
void task2b() {
    cout << "=== ������� 2.� - ���������� �� 64 ����� (0-63) ===" << endl;
    
    vector<int> numbers;
    int n, num;
    
    cout << "������� ���������� ����� (�� 64): ";
    cin >> n;
    
    if (n > 64) {
        cout << "������� ����� �����! �������� 64." << endl;
        return;
    }
    
    cout << "������� ����� �� 0 �� 63: ";
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num < 0 || num > 63) {
            cout << "����� " << num << " ��� ��������� [0-63]!" << endl;
            return;
        }
        numbers.push_back(num);
    }
    
    cout << "�������� �����: ";
    for (int x : numbers) cout << x << " ";
    cout << endl;
    
    // �������� �������� �������
    unsigned long long bitArray = 0;
    
    // ��������� ����� ��� ������� �����
    for (int num : numbers) {
        bitArray |= (1ULL << num);  // ������������� ��� � ������� num
    }
    
    cout << "������� ������ (64 ����): " << bitset<64>(bitArray) << endl;
    
    // ���������� ��������������� �����
    cout << "��������������� �����: ";
    for (int i = 0; i < 64; i++) {
        if (bitArray & (1ULL << i)) {  // ��������� ���������� �� ��� i
            cout << i << " ";
        }
    }
    cout << endl << endl;
}

// ������� 2.� - ���������� 64 ����� � ������� ������� unsigned char
void task2c() {
    cout << "=== ������� 2.� - ���������� 64 ����� ����� ������ unsigned char ===" << endl;
    
    vector<int> numbers;
    int n, num;
    
    cout << "������� ���������� ����� (�� 64): ";
    cin >> n;
    
    if (n > 64) {
        cout << "������� ����� �����! �������� 64." << endl;
        return;
    }
    
    cout << "������� ����� �� 0 �� 63: ";
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num < 0 || num > 63) {
            cout << "����� " << num << " ��� ��������� [0-63]!" << endl;
            return;
        }
        numbers.push_back(num);
    }
    
    cout << "�������� �����: ";
    for (int x : numbers) cout << x << " ";
    cout << endl;
    
    // �������� ������� ������� ����� (8 ���� = 64 ����)
    const int ARRAY_SIZE = 8;  // 8 ���� * 8 ��� = 64 ����
    unsigned char bitArray[ARRAY_SIZE] = {0};
    
    // ��������� ����� ��� ������� �����
    for (int num : numbers) {
        int byteIndex = num / 8;      // ���������� ������ �����
        int bitIndex = num % 8;       // ���������� ������� ���� � �����
        bitArray[byteIndex] |= (1 << bitIndex);
    }
    
    // ����� �������� �������
    cout << "������� ������ (8 ����): ";
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << bitset<8>(bitArray[i]) << " ";
    }
    cout << endl;
    
    // ���������� ��������������� �����
    cout << "��������������� �����: ";
    for (int i = 0; i < 64; i++) {
        int byteIndex = i / 8;
        int bitIndex = i % 8;
        if (bitArray[byteIndex] & (1 << bitIndex)) {
            cout << i << " ";
        }
    }
    cout << endl << endl;
}

// ������������ � ���������������
void demonstration() {
    cout << "=== ������������ ���� ������� ===" << endl;
    
    // ���� ��� ������� 2.�
    cout << "\n���� 2.� - ����� {1, 0, 5, 7, 2, 4}:" << endl;
    vector<int> demo1 = {1, 0, 5, 7, 2, 4};
    unsigned char bitArray1 = 0;
    
    for (int num : demo1) {
        bitArray1 |= (1 << num);
    }
    
    cout << "��������: ";
    for (int x : demo1) cout << x << " ";
    cout << endl;
    cout << "������� ������: " << bitset<8>(bitArray1) << endl;
    cout << "���������������: ";
    for (int i = 0; i < 8; i++) {
        if (bitArray1 & (1 << i)) cout << i << " ";
    }
    cout << endl;
    
    // ���� ��� ������� 2.�
    cout << "\n���� 2.� - ����� {15, 3, 45, 63, 0, 32}:" << endl;
    vector<int> demo2 = {15, 3, 45, 63, 0, 32};
    unsigned long long bitArray2 = 0;
    
    for (int num : demo2) {
        bitArray2 |= (1ULL << num);
    }
    
    cout << "��������: ";
    for (int x : demo2) cout << x << " ";
    cout << endl;
    cout << "���������������: ";
    for (int i = 0; i < 64; i++) {
        if (bitArray2 & (1ULL << i)) cout << i << " ";
    }
    cout << endl;
    
    // ���� ��� ������� 2.�
    cout << "\n���� 2.� - ��� �� ����� ����� ������ ����:" << endl;
    unsigned char bitArray3[8] = {0};
    
    for (int num : demo2) {
        int byteIndex = num / 8;
        int bitIndex = num % 8;
        bitArray3[byteIndex] |= (1 << bitIndex);
    }
    
    cout << "���������������: ";
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
        cout << "\n=== ���� ===" << endl;
        cout << "1. ������� 2.� (�� 8 �����, 0-7)" << endl;
        cout << "2. ������� 2.� (�� 64 �����, 0-63, long long)" << endl;
        cout << "3. ������� 2.� (�� 64 �����, ������ char)" << endl;
        cout << "4. ������������ ���� �������" << endl;
        cout << "0. �����" << endl;
        cout << "�������� �����: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1: task2a(); break;
            case 2: task2b(); break;
            case 3: task2c(); break;
            case 4: demonstration(); break;
            case 0: return 0;
            default: cout << "�������� �������� �����" << endl;
        }
    }
    
    return 0;
}