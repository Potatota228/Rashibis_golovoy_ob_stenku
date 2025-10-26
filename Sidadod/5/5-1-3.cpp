#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <Windows.h>
#include <cstdlib>
using namespace std;
using namespace chrono;

// ������� ��� ��������� �������
void setupConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

// ����� ��� ������ � ������� ��������
class BitArray {
private:
    vector<unsigned char> bits;
    size_t maxValue;
    
public:
    BitArray(size_t maxVal) : maxValue(maxVal) {
        // ��������� ����������� ���������� ����
        size_t bytesNeeded = (maxValue + 7) / 8;
        bits.resize(bytesNeeded, 0);
    }
    
    // ���������� ��� � ������� value
    void setBit(size_t value) {
        if (value <= maxValue) {
            size_t byteIndex = value / 8;
            size_t bitIndex = value % 8;
            bits[byteIndex] |= (1 << bitIndex);
        }
    }
    
    // ��������� ���������� �� ��� � ������� value
    bool getBit(size_t value) const {
        if (value <= maxValue) {
            size_t byteIndex = value / 8;
            size_t bitIndex = value % 8;
            return (bits[byteIndex] & (1 << bitIndex)) != 0;
        }
        return false;
    }
    
    // �������� ������ ������� � ������
    size_t getSizeInBytes() const {
        return bits.size();
    }
    
    // �������� ������������ ��������
    size_t getMaxValue() const {
        return maxValue;
    }
};

// �������� ��������� �����
void createTestFile(const string& filename, size_t count, size_t maxValue) {
    cout << "�������� ��������� �����..." << endl;
    
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������ �������� �����!" << endl;
        return;
    }
    
    // ��������� ��������� �����
    random_device rd;
    mt19937 gen(rd()); //��������� ��������������� �����
    uniform_int_distribution<size_t> dis(1000000, maxValue); //����������� ������������� � ���������
    
    // ���������� set ��� ��������� ����������
    vector<bool> used(maxValue + 1, false); //������������ �������������� �����
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
    cout << "���� ������: " << count << " �����" << endl;
}

// ������� 3.� - ���������� ����� � ������� �������
void task3a() {
    cout << "=== ������� 3.� - ���������� ����� ===" << endl;
    
    const size_t MAX_VALUE = 9999999;  // ������������ 7-������� �����
    const size_t MAX_NUMBERS = 1000000; // ������������ ���������� ����� ��� �����
    
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    
    // ��������� ������������ ������ �������� ������� ��� 1��
    const size_t MAX_MEMORY_BYTES = 1024 * 1024; // 1 �� = 1,048,576 ����
    size_t maxBits = MAX_MEMORY_BYTES * 8; //8,388,608 ���
    size_t actualMaxValue = min(MAX_VALUE, maxBits - 1); //8,388,608
    
    cout << "������������ �������� ��� 1�� ������: " << actualMaxValue << endl;
    
    // ���������� ���������� ����� ��� �����
    size_t testCount;
    cout << "������� ���������� ����� ��� ����� (�� " << MAX_NUMBERS << "): ";
    cin >> testCount;
    
    if (testCount > MAX_NUMBERS) {
        testCount = MAX_NUMBERS;
        cout << "����������� ������������ ��������: " << testCount << endl;
    }
    
    // �������� ��������� �����
    createTestFile(inputFile, testCount, actualMaxValue);
    
    // ������ ������ ������� ����������
    auto startTime = high_resolution_clock::now();
    
    // �������� �������� �������
    BitArray bitArray(actualMaxValue);
    
    // ������ ����� � ���������� �������� �������
    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cout << "������ �������� �������� �����!" << endl;
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
    
    cout << "��������� �����: " << numbersRead << endl;
    
    // ������ ��������������� ����� � �������� ����
    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cout << "������ �������� ��������� �����!" << endl;
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
    
    // ��������� ������ �������
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);
    
    cout << "�������� ��������������� �����: " << sortedCount << endl;
    cout << "����� ����������: " << duration.count() << " ��" << endl;
    cout << "����� ����������: " << duration.count() / 1000.0 << " �" << endl;
    cout << "������ �������� �������: " << bitArray.getSizeInBytes() << " ����" << endl;
    cout << "������ �������� �������: " << bitArray.getSizeInBytes() / 1024.0 << " ��" << endl;
}

// ������� 3.� - ����������� ������ ������ �������� �������
void task3b() {
    cout << "\n=== ������� 3.� - ����������� ������ ������ ===" << endl;
    
    // ��������� �������� �������
    vector<size_t> testSizes = {
        100,          // 100 �����
        1000,         // 1 ������
        10000,        // 10 �����
        100000,       // 100 �����
        1000000,      // 1 �������
        8388608,      // 1 �� � ����� (1024*1024*8)
        10000000      // 10 ���������
    };
    
    cout << "\n������ ���������� � ������ ��� ��������� ��������:" << endl;
    cout << "����. ��������\t����\t\t��\t\t��" << endl;
    cout << "----------------------------------------------" << endl;
    
    for (size_t maxVal : testSizes) {
        BitArray testArray(maxVal);
        size_t bytes = testArray.getSizeInBytes();
        double kb = bytes / 1024.0;
        double mb = kb / 1024.0;
        
        cout << maxVal << "\t\t" << bytes << "\t\t" 
             << kb << "\t" << mb << endl;
    }
    
    // ����������� ������������� ���������� ����� ��� 1��
    const size_t MAX_MEMORY = 1024 * 1024; // 1 ��
    size_t maxNumbersFor1MB = MAX_MEMORY * 8; // ������ ��� ����� ������������ ���� �����
    
    cout << "\n��� ����������� � 1 ��:" << endl;
    cout << "������������ �������� �����: " << maxNumbersFor1MB - 1 << endl;
    cout << "������������ ���������� ��������� �����: " << maxNumbersFor1MB << endl;
    
    // ������������ ���� � 1��
    BitArray array1MB(maxNumbersFor1MB - 1);
    cout << "�������� ������ �������� ������� ��� 1��: " << array1MB.getSizeInBytes() << " ����" << endl;
    
    // ���� ������������������ ������� � �����
    cout << "\n���� ������������������ �������� � ������:" << endl;
    
    auto start = high_resolution_clock::now();
    
    // ��������� ������� 100-�� ����
    for (size_t i = 0; i < maxNumbersFor1MB; i += 100) {
        array1MB.setBit(i);
    }
    
    auto middle = high_resolution_clock::now();
    
    // �������� ������� ����
    size_t setBitsCount = 0;
    for (size_t i = 0; i < maxNumbersFor1MB; i++) {
        if (array1MB.getBit(i)) {
            setBitsCount++;
        }
    }
    
    auto end = high_resolution_clock::now();
    
    auto setTime = duration_cast<microseconds>(middle - start);
    auto readTime = duration_cast<microseconds>(end - middle);
    
    cout << "����� ��������� �����: " << setTime.count() << " ���" << endl;
    cout << "����� ������ ���� �����: " << readTime.count() << " ���" << endl;
    cout << "������� ������������� �����: " << setBitsCount << endl;
}

// ������������ � ��������� ������
void demonstrateSmallExample() {
    cout << "\n=== ������������ �� ����� ������� ===" << endl;
    
    // ������� ��������� �������� ����
    string demoInput = "demo_input.txt";
    string demoOutput = "demo_output.txt";
    
    // ���������� ��������� ����� � ����
    ofstream demoFile(demoInput);
    vector<int> demoNumbers = {1000015, 1000003, 1000027, 1000001, 1000099, 1000050};
    
    cout << "�������� �����: ";
    for (int num : demoNumbers) {
        demoFile << num << "\n";
        cout << num << " ";
    }
    cout << endl;
    demoFile.close();
    
    // ����������
    const size_t DEMO_MAX = 1000100;
    BitArray demoBitArray(DEMO_MAX);
    
    // ������ � ��������� �����
    ifstream inFile(demoInput);
    size_t num;
    while (inFile >> num) {
        demoBitArray.setBit(num);
    }
    inFile.close();
    
    // ������ ����������
    ofstream outFile(demoOutput);
    cout << "��������������� �����: ";
    for (size_t i = 0; i <= DEMO_MAX; i++) {
        if (demoBitArray.getBit(i)) {
            outFile << i << "\n";
            cout << i << " ";
        }
    }
    cout << endl;
    outFile.close();
    
    cout << "������ �������� �������: " << demoBitArray.getSizeInBytes() << " ����" << endl;
}

int main() {
    setupConsole();
    
    int choice;
    
    while (true) {
        cout << "\n=== ���� ===" << endl;
        cout << "1. ������� 3.� - ���������� �������� �����" << endl;
        cout << "2. ������� 3.� - ������ ������ ������" << endl;
        cout << "3. ������������ �� ����� �������" << endl;
        cout << "0. �����" << endl;
        cout << "�������� �����: ";
        
        cin >> choice;
        
        switch (choice) {
            case 1: task3a(); break;
            case 2: task3b(); break;
            case 3: demonstrateSmallExample(); break;
            case 0: return 0;
            default: cout << "�������� �����!" << endl;
        }
    }
    
    return 0;
}