#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <vector>
using namespace std;


struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node(char c, int f) {
        ch = c;
        freq = f;
        left = NULL;
        right = NULL;
    }
};


struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};


void buildCodes(Node* root, string code, map<char, string>& codes) {
    if (root == NULL) {
        return;
    }
    
    
    if (root->left == NULL && root->right == NULL) {
        codes[root->ch] = code;
        return;
    }
    
    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}


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
    
    
    priority_queue<Node*, vector<Node*>, CompareNode> pq;
    for (auto p : freqMap) {
        pq.push(new Node(p.first, p.second));
    }
    
    
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    
    Node* root = pq.top();
    
    
    map<char, string> codes;
    if (freqMap.size() == 1) {
        
        codes[root->ch] = "0";
    } else {
        buildCodes(root, "", codes);
    }
    
    
    cout << "\nТаблица кодов Хаффмана:\n";
    cout << "Символ\tЧастота\tКод\n";
    for (auto p : freqMap) {
        cout << "'" << p.first << "'\t" << p.second << "\t" << codes[p.first] << endl;
    }
    
    
    string encoded = "";
    for (char ch : text) {
        encoded += codes[ch];
    }
    
    
    ofstream output(outputFile, ios::binary);
    
    
    int tableSize = freqMap.size();
    output.write((char*)&tableSize, sizeof(int));
    
    
    for (auto p : codes) {
        output.write(&p.first, sizeof(char));
        int codeLen = p.second.length();
        output.write((char*)&codeLen, sizeof(int));
        output.write(p.second.c_str(), codeLen);
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
    
    cout << "=== Сжатие методом Хаффмана ===\n";
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