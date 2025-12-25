#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


struct Symbol {
    char ch;
    int freq;
    string code;
};

//Сравн част
bool compareFreq(Symbol a, Symbol b) {
    return a.freq > b.freq;
}

//Рекурс функц шенон фано
void shannonFano(vector<Symbol>& symbols, int start, int end, string prefix) { //Важно, используется ссылка
    if (start >= end) {
        return;
    }
    
    if (start == end - 1) {
        symbols[start].code = prefix;
        return;
    }
    
    
    int totalFreq = 0;
    for (int i = start; i < end; i++) {
        totalFreq += symbols[i].freq;
    }
    
    int halfFreq = totalFreq / 2;
    int currentSum = 0;
    int splitIndex = start;
    
    for (int i = start; i < end; i++) {
        currentSum += symbols[i].freq;
        if (currentSum >= halfFreq) {
            splitIndex = i + 1;
            break;
        }
    }
    
    
    for (int i = start; i < splitIndex; i++) {
        shannonFano(symbols, start, splitIndex, prefix + "0");
    }
    for (int i = splitIndex; i < end; i++) {
        shannonFano(symbols, splitIndex, end, prefix + "1");
    }
    
    
    for (int i = start; i < splitIndex; i++) {
        if (symbols[i].code.empty()) {
            symbols[i].code = prefix + "0";
        }
    }
    for (int i = splitIndex; i < end; i++) {
        if (symbols[i].code.empty()) {
            symbols[i].code = prefix + "1";
        }
    }
}

//Сжатие
void compress(string inputFile, string outputFile) {
    
    ifstream input(inputFile);
    string text;
    getline(input, text, '\0');
    input.close();
    
    if (text.empty()) {
        cout << "Ошибка: файл пуст!" << endl;
        return;
    }
    
    
    map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }
    
    
    vector<Symbol> symbols;
    for (auto p : freqMap) {
        Symbol s;
        s.ch = p.first;
        s.freq = p.second;
        s.code = "";
        symbols.push_back(s);
    }
    
    
    sort(symbols.begin(), symbols.end(), compareFreq);
    
    
    shannonFano(symbols, 0, symbols.size(), "");
    
    
    map<char, string> codeTable;
    cout << "\nТаблица кодов Шеннона-Фано:\n";
    cout << "Символ\tЧастота\tКод\n";
    for (Symbol s : symbols) {
        codeTable[s.ch] = s.code;
        cout << "'" << s.ch << "'\t" << s.freq << "\t" << s.code << endl;
    }
    
    
    string encoded = "";
    for (char ch : text) {
        encoded += codeTable[ch];
    }
    
    
    ofstream output(outputFile, ios::binary);
    
    
    int tableSize = symbols.size();
    output.write((char*)&tableSize, sizeof(int));
    
    
    for (Symbol s : symbols) {
        output.write(&s.ch, sizeof(char));
        int codeLen = s.code.length();
        output.write((char*)&codeLen, sizeof(int));
        output.write(s.code.c_str(), codeLen);
    }
    
    
    int encodedLen = encoded.length();
    output.write((char*)&encodedLen, sizeof(int));
    
    
    char byte = 0;
    int bitCount = 0;
    for (char bit : encoded) {
        byte = (byte << 1) | (bit - '0');
        bitCount++;
        if (bitCount == 8) {
            output.write(&byte, sizeof(char));
            byte = 0;
            bitCount = 0;
        }
    }
    if (bitCount > 0) {
        byte = byte << (8 - bitCount);
        output.write(&byte, sizeof(char));
    }
    
    output.close();
    
    
    int originalSize = text.length() * 8;
    int compressedSize = encodedLen;
    double ratio = (double)originalSize / compressedSize;
    
    cout << "\nСтатистика сжатия:\n";
    cout << "Исходный размер: " << originalSize << " бит (" << text.length() << " байт)\n";
    cout << "Сжатый размер: " << compressedSize << " бит\n";
    cout << "Коэффициент сжатия: " << ratio << ":1\n";
}

//Разжатие
void decompress(string inputFile, string outputFile) {
    ifstream input(inputFile, ios::binary);
    
    
    int tableSize;
    input.read((char*)&tableSize, sizeof(int));
    
    
    map<string, char> decodeTable;
    for (int i = 0; i < tableSize; i++) {
        char ch;
        input.read(&ch, sizeof(char));
        
        int codeLen;
        input.read((char*)&codeLen, sizeof(int));
        
        char* codeBuf = new char[codeLen + 1];
        input.read(codeBuf, codeLen);
        codeBuf[codeLen] = '\0';
        
        decodeTable[string(codeBuf)] = ch;
        delete[] codeBuf;
    }
    
    
    int encodedLen;
    input.read((char*)&encodedLen, sizeof(int));
    
    
    string encoded = "";
    char byte;
    while (input.read(&byte, sizeof(char))) {
        for (int i = 7; i >= 0; i--) {
            encoded += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    
    
    encoded = encoded.substr(0, encodedLen);
    input.close();
    
    
    string decoded = "";
    string currentCode = "";
    for (char bit : encoded) {
        currentCode += bit;
        if (decodeTable.find(currentCode) != decodeTable.end()) {
            decoded += decodeTable[currentCode];
            currentCode = "";
        }
    }
    
    
    ofstream output(outputFile);
    output << decoded;
    output.close();
    
    cout << "Файл успешно восстановлен!\n";
}

int main() {
    int choice;
    string inputFile, outputFile;
    
    cout << "=== Сжатие методом Шеннона-Фано ===\n";
    cout << "1. Сжать файл\n";
    cout << "2. Восстановить файл\n";
    cout << "Выберите действие: ";
    cin >> choice;
    
    if (choice == 1) {
        cout << "Введите имя входного файла: ";
        cin >> inputFile;
        cout << "Введите имя выходного файла: ";
        cin >> outputFile;
        compress(inputFile, outputFile);
    } else if (choice == 2) {
        cout << "Введите имя сжатого файла: ";
        cin >> inputFile;
        cout << "Введите имя выходного файла: ";
        cin >> outputFile;
        decompress(inputFile, outputFile);
    }
    
    return 0;
}