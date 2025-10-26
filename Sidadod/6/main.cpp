#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <regex>
#include <Windows.h>

using namespace std;
using namespace chrono;

// ============================================================
// ��������� ������
// ============================================================

// ��������� ������ �����
struct Book {
    long long isbn;        // ISBN - 12-������� ����� (����)
    char author[50];       // �����
    char title[100];       // ��������
    
    Book() : isbn(0) {
        author[0] = '\0';
        title[0] = '\0';
    }
    
    Book(long long i, const string& a, const string& t) : isbn(i) {
        strncpy(author, a.c_str(), sizeof(author) - 1);
        author[sizeof(author) - 1] = '\0';
        strncpy(title, t.c_str(), sizeof(title) - 1);
        title[sizeof(title) - 1] = '\0';
    }
};

// ��������� �������� ���-�������
struct HashElement {
    long long key;        // ���� (ISBN �����)
    int recordNumber;     // ����� ������ � �����
    bool isOccupied;      // ������ ������
    bool isDeleted;       // ������ ���� �������
    
    HashElement() : key(0), recordNumber(-1), isOccupied(false), isDeleted(false) {}
};

// ��������� ���-�������
struct HashTable {
    vector<HashElement> table;
    int size;
    int count;
    double loadFactor;
    
    HashTable(int tableSize) {
        size = tableSize;
        count = 0;
        loadFactor = 0.0;
        table.resize(size);
    }
};

// ��������� ��� ���������� � ����
struct PriceInfo {
    string original;
    double value;
    string currency;
    int position;
};

// ============================================================
// ���-�������: �������
// ============================================================

int hash1(long long key, int tableSize) {
    return key % tableSize;
}

int hash2(long long key, int tableSize) {
    int prime = tableSize - 1;
    while (prime > 1) {
        bool isPrime = true;
        for (int i = 2; i * i <= prime; i++) {
            if (prime % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) break;
        prime--;
    }
    return prime - (key % prime);
}

void updateLoadFactor(HashTable& ht) {
    ht.loadFactor = (double)ht.count / ht.size;
}

bool insertKey(HashTable& ht, long long key, int recordNum, bool showIndexes = false) {
    if (ht.loadFactor >= 0.75) {
        if (showIndexes) {
            cout << "��������� �������������! ����������� ����������: " << ht.loadFactor << endl;
        }
        return false;
    }
    
    int h1 = hash1(key, ht.size);
    int h2 = hash2(key, ht.size);
    int index = h1;
    int attempt = 0;
    
    if (showIndexes) {
        cout << "������� ����� " << key << ": hash1=" << h1 << ", hash2=" << h2 << endl;
    }
    
    while (attempt < ht.size) {
        index = (h1 + attempt * h2) % ht.size;
        
        if (showIndexes) {
            cout << "  ������� " << attempt << ": ������ " << index;
        }
        
        if (!ht.table[index].isOccupied || ht.table[index].isDeleted) {
            ht.table[index].key = key;
            ht.table[index].recordNumber = recordNum;
            ht.table[index].isOccupied = true;
            ht.table[index].isDeleted = false;
            ht.count++;
            updateLoadFactor(ht);
            
            if (showIndexes) {
                cout << " - ������� ��������" << endl;
            }
            return true;
        }
        
        if (ht.table[index].key == key && !ht.table[index].isDeleted) {
            if (showIndexes) {
                cout << " - ���� ��� ����������" << endl;
            }
            return false;
        }
        
        if (showIndexes) {
            cout << " - ������ (��������)" << endl;
        }
        
        attempt++;
    }
    
    cout << "������� �����������!" << endl;
    return false;
}

int searchKey(HashTable& ht, long long key) {
    int h1 = hash1(key, ht.size);
    int h2 = hash2(key, ht.size);
    int index = h1;
    int attempt = 0;
    
    while (attempt < ht.size) {
        index = (h1 + attempt * h2) % ht.size;
        
        if (!ht.table[index].isOccupied && !ht.table[index].isDeleted) {
            return -1;
        }
        
        if (ht.table[index].isOccupied && 
            ht.table[index].key == key && 
            !ht.table[index].isDeleted) {
            return ht.table[index].recordNumber;
        }
        
        attempt++;
    }
    
    return -1;
}

bool deleteKey(HashTable& ht, long long key) {
    int h1 = hash1(key, ht.size);
    int h2 = hash2(key, ht.size);
    int index = h1;
    int attempt = 0;
    
    while (attempt < ht.size) {
        index = (h1 + attempt * h2) % ht.size;
        
        if (!ht.table[index].isOccupied && !ht.table[index].isDeleted) {
            return false;
        }
        
        if (ht.table[index].isOccupied && 
            ht.table[index].key == key && 
            !ht.table[index].isDeleted) {
            ht.table[index].isDeleted = true;
            ht.count--;
            updateLoadFactor(ht);
            return true;
        }
        
        attempt++;
    }
    
    return false;
}

HashTable rehash(HashTable& oldHt) {
    int newSize = oldHt.size * 2;
    bool found = false;
    while (!found) {
        found = true;
        for (int i = 2; i * i <= newSize; i++) {
            if (newSize % i == 0) {
                found = false;
                newSize++;
                break;
            }
        }
    }
    
    cout << "�������������: ������ ������ = " << oldHt.size 
         << ", ����� ������ = " << newSize << endl;
    
    HashTable newHt(newSize);
    
    for (int i = 0; i < oldHt.size; i++) {
        if (oldHt.table[i].isOccupied && !oldHt.table[i].isDeleted) {
            insertKey(newHt, oldHt.table[i].key, oldHt.table[i].recordNumber);
        }
    }
    
    return newHt;
}

void printHashTable(const HashTable& ht) {
    cout << "\n=== ���-������� ===" << endl;
    cout << "������: " << ht.size << ", ���������: " << ht.count 
         << ", ����������� ����������: " << fixed << setprecision(3) << ht.loadFactor << endl;
    
    int printed = 0;
    for (int i = 0; i < ht.size && printed < 10; i++) {
        if (ht.table[i].isOccupied && !ht.table[i].isDeleted) {
            cout << "[" << i << "] ISBN: " << ht.table[i].key 
                 << ", ������ �" << ht.table[i].recordNumber << endl;
            printed++;
        }
    }
    if (ht.count > 10) {
        cout << "... � ��� " << (ht.count - 10) << " ���������" << endl;
    }
    cout << "==================\n" << endl;
}

// ============================================================
// ������ � �������
// ============================================================

const string BINARY_FILE = "books.bin";

void printBook(const Book& book) {
    if (book.isbn == 0) {
        cout << "������ �� �������\n";
    } else {
        cout << "ISBN: " << book.isbn << "\n";
        cout << "�����: " << book.author << "\n";
        cout << "��������: " << book.title << "\n";
    }
}

int getRecordCount() {
    ifstream file(BINARY_FILE, ios::binary);
    if (!file.is_open()) return 0;
    
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    file.close();
    
    return static_cast<int>(fileSize / sizeof(Book));
}

bool readRecordByNumber(int recordNum, Book& book) {
    ifstream file(BINARY_FILE, ios::binary);
    if (!file.is_open()) return false;
    
    file.seekg(recordNum * sizeof(Book));
    file.read(reinterpret_cast<char*>(&book), sizeof(Book));
    file.close();
    
    return true;
}

bool appendRecord(const Book& book) {
    ofstream file(BINARY_FILE, ios::binary | ios::app);
    if (!file.is_open()) return false;
    
    file.write(reinterpret_cast<const char*>(&book), sizeof(Book));
    file.close();
    return true;
}

bool deleteRecordByKey(long long isbn) {
    fstream file(BINARY_FILE, ios::binary | ios::in | ios::out);
    if (!file.is_open()) return false;
    
    Book book;
    bool found = false;
    streampos pos;
    
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        if (book.isbn == isbn) {
            found = true;
            pos = file.tellg();
            pos -= sizeof(Book);
            break;
        }
    }
    
    if (found) {
        book.isbn = 0;
        file.seekp(pos);
        file.write(reinterpret_cast<const char*>(&book), sizeof(Book));
    }
    
    file.close();
    return found;
}

bool linearSearchByISBN(long long isbn, Book& book) {
    ifstream file(BINARY_FILE, ios::binary);
    if (!file.is_open()) return false;
    
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        if (book.isbn == isbn && book.isbn != 0) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

void createBinaryFromText(const string& textFileName) {
    ifstream textFile(textFileName);
    ofstream binaryFile(BINARY_FILE, ios::binary);
    
    if (!textFile.is_open() || !binaryFile.is_open()) {
        cout << "������ �������� ������" << endl;
        return;
    }
    
    string line;
    while (getline(textFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        
        if (pos1 == string::npos || pos2 == string::npos) continue;
        
        Book book;
        book.isbn = stoll(line.substr(0, pos1));
        
        string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string title = line.substr(pos2 + 1, pos3 - pos2 - 1);
        
        strncpy(book.author, author.c_str(), sizeof(book.author) - 1);
        book.author[sizeof(book.author) - 1] = '\0';
        
        strncpy(book.title, title.c_str(), sizeof(book.title) - 1);
        book.title[sizeof(book.title) - 1] = '\0';
        
        binaryFile.write(reinterpret_cast<const char*>(&book), sizeof(book));
    }
    
    textFile.close();
    binaryFile.close();
}

// ============================================================
// ���������� ������ ����� ���-�������
// ============================================================

HashTable buildHashTableFromFile() {
    int recordCount = getRecordCount();
    int tableSize = recordCount * 2;
    
    bool found = false;
    while (!found) {
        found = true;
        for (int i = 2; i * i <= tableSize; i++) {
            if (tableSize % i == 0) {
                found = false;
                tableSize++;
                break;
            }
        }
    }
    
    HashTable ht(tableSize);
    
    cout << "�������� ���-������� �� �����..." << endl;
    cout << "������� � �����: " << recordCount << ", ������ �������: " << tableSize << endl;
    
    ifstream file(BINARY_FILE, ios::binary);
    if (!file.is_open()) {
        cout << "������ �������� �����" << endl;
        return ht;
    }
    
    Book book;
    int recordNum = 0;
    
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        if (book.isbn != 0) {
            insertKey(ht, book.isbn, recordNum);
        }
        recordNum++;
    }
    
    file.close();
    
    cout << "���-������� �������. ���������: " << ht.count << endl;
    
    return ht;
}

bool addBookWithHash(HashTable& ht, const Book& book) {
    if (searchKey(ht, book.isbn) != -1) {
        cout << "����� � ISBN " << book.isbn << " ��� ����������!" << endl;
        return false;
    }
    
    int recordNum = getRecordCount();
    
    if (!appendRecord(book)) {
        return false;
    }
    
    if (ht.loadFactor >= 0.75) {
        cout << "����������� �������������..." << endl;
        ht = rehash(ht);
    }
    
    if (!insertKey(ht, book.isbn, recordNum)) {
        cout << "������ ���������� � ���-�������" << endl;
        return false;
    }
    
    cout << "����� ���������. ISBN: " << book.isbn << ", ������ �" << recordNum << endl;
    return true;
}

bool findBookByISBN(HashTable& ht, long long isbn, Book& book) {
    int recordNum = searchKey(ht, isbn);
    
    if (recordNum == -1) {
        return false;
    }
    
    if (!readRecordByNumber(recordNum, book)) {
        return false;
    }
    
    if (book.isbn == 0) {
        return false;
    }
    
    return true;
}

bool deleteBookByISBN(HashTable& ht, long long isbn) {
    if (!deleteKey(ht, isbn)) {
        cout << "����� � ISBN " << isbn << " �� ������� � ���-�������" << endl;
        return false;
    }
    
    if (!deleteRecordByKey(isbn)) {
        cout << "������ �������� �� �����" << endl;
        return false;
    }
    
    cout << "����� � ISBN " << isbn << " ������� �������" << endl;
    return true;
}

double measureHashSearch(HashTable& ht, long long isbn) {
    Book book;
    auto start = high_resolution_clock::now();
    findBookByISBN(ht, isbn, book);
    auto end = high_resolution_clock::now();
    duration<double, micro> elapsed = end - start;
    return elapsed.count();
}

double measureLinearSearch(long long isbn) {
    Book book;
    auto start = high_resolution_clock::now();
    linearSearchByISBN(isbn, book);
    auto end = high_resolution_clock::now();
    duration<double, micro> elapsed = end - start;
    return elapsed.count();
}

void compareSearchPerformance(HashTable& ht) {
    cout << "\n========== ��������� ������������������ ==========" << endl;
    
    int recordCount = getRecordCount();
    
    if (recordCount == 0) {
        cout << "���� ����!" << endl;
        return;
    }
    
    Book firstBook, middleBook, lastBook;
    
    readRecordByNumber(0, firstBook);
    readRecordByNumber(recordCount / 2, middleBook);
    readRecordByNumber(recordCount - 1, lastBook);
    
    cout << "\n���������� ������� � �����: " << recordCount << endl;
    cout << "\n������������ ������:" << endl;
    cout << "------------------------------------------------" << endl;
    
    cout << "\n1. ������ ������ (ISBN: " << firstBook.isbn << ")" << endl;
    double hashTime1 = measureHashSearch(ht, firstBook.isbn);
    double linearTime1 = measureLinearSearch(firstBook.isbn);
    cout << "   ���-�������:    " << fixed << setprecision(2) << hashTime1 << " ���" << endl;
    cout << "   �������� �����: " << linearTime1 << " ���" << endl;
    cout << "   ���������:      " << (linearTime1 / hashTime1) << "x" << endl;
    
    cout << "\n2. ������� ������ (ISBN: " << middleBook.isbn << ")" << endl;
    double hashTime2 = measureHashSearch(ht, middleBook.isbn);
    double linearTime2 = measureLinearSearch(middleBook.isbn);
    cout << "   ���-�������:    " << hashTime2 << " ���" << endl;
    cout << "   �������� �����: " << linearTime2 << " ���" << endl;
    cout << "   ���������:      " << (linearTime2 / hashTime2) << "x" << endl;
    
    cout << "\n3. ��������� ������ (ISBN: " << lastBook.isbn << ")" << endl;
    double hashTime3 = measureHashSearch(ht, lastBook.isbn);
    double linearTime3 = measureLinearSearch(lastBook.isbn);
    cout << "   ���-�������:    " << hashTime3 << " ���" << endl;
    cout << "   �������� �����: " << linearTime3 << " ���" << endl;
    cout << "   ���������:      " << (linearTime3 / hashTime3) << "x" << endl;
    
    cout << "\n------------------------------------------------" << endl;
    cout << "�����: ����� ������� ����� ���-������� ��������" << endl;
    cout << "��������� ��� ���� ������� (O(1))," << endl;
    cout << "� �� ����� ��� �������� ����� ������� �� ������� (O(n))." << endl;
    cout << "==================================================\n" << endl;
}

void createLargeTestFile(int numRecords) {
    cout << "�������� ��������� ����� � " << numRecords << " ��������..." << endl;
    
    ofstream testFile("books_test.txt");
    
    string authors[] = {"������� �.�.", "����������� �.�.", "������ �.�.", 
                       "�������� �.�.", "����� �.�.", "�������� �.�.",
                       "������ �.�.", "��������� �.�.", "������� �.�.", "������� �.�."};
    
    string titles[] = {"����� � ���", "������������ � ���������", "������� ������",
                      "������ � ���������", "�������� ���", "���� � ����",
                      "������� ����", "����� ������ �������", "����� ���", "������"};
    
    srand(time(0));
    
    for (int i = 0; i < numRecords; i++) {
        long long isbn = 978000000000LL + i;
        string author = authors[rand() % 10];
        string title = titles[rand() % 10];
        int year = 1800 + rand() % 224;
        
        testFile << isbn << "," << author << "," << title << "," << year << "\n";
    }
    
    testFile.close();
    cout << "���� ������." << endl;
}

// ============================================================
// ��������� ������ � ������ (���)
// ============================================================

vector<int> computePrefixFunction(const string& pattern) {
    int m = pattern.length();
    vector<int> pi(m, 0);
    
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        
        if (pattern[i] == pattern[j]) {
            j++;
        }
        
        pi[i] = j;
    }
    
    return pi;
}

int KMPSearch(const string& text, const string& pattern, bool showProcess = false) {
    int n = text.length();
    int m = pattern.length();
    
    if (m == 0) return 0;
    if (m > n) return -1;
    
    vector<int> pi = computePrefixFunction(pattern);
    
    if (showProcess) {
        cout << "\n�������-������� ��� ������� \"" << pattern << "\":" << endl;
        for (int i = 0; i < m; i++) {
            cout << "pi[" << i << "] = " << pi[i] << " ";
        }
        cout << "\n" << endl;
    }
    
    int j = 0;
    int comparisons = 0;
    
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
            comparisons++;
        }
        
        comparisons++;
        
        if (text[i] == pattern[j]) {
            j++;
        }
        
        if (j == m) {
            if (showProcess) {
                cout << "������� ��������� �� �������: " << (i - m + 1) << endl;
                cout << "���������� ���������: " << comparisons << endl;
            }
            return i - m + 1;
        }
    }
    
    if (showProcess) {
        cout << "������� �� ������" << endl;
        cout << "���������� ���������: " << comparisons << endl;
    }
    
    return -1;
}

int findMaxPrefixInString(const string& a, const string& b, bool showProcess = false) {
    if (a.empty()) return 0;
    
    if (showProcess) {
        cout << "\n========== ����� ������������� �������� ==========" << endl;
        cout << "������ a: \"" << a << "\"" << endl;
        cout << "������ b: \"" << b << "\"" << endl;
        cout << "===================================================\n" << endl;
    }
    
    int maxLen = min(a.length(), b.length());
    
    for (int len = maxLen; len >= 1; len--) {
        string prefix = a.substr(0, len);
        
        if (showProcess) {
            cout << "��������� ������� ����� " << len << ": \"" << prefix << "\"" << endl;
        }
        
        int pos = KMPSearch(b, prefix, false);
        
        if (pos != -1) {
            if (showProcess) {
                cout << "? ������ �� ������� " << pos << " � ������ b" << endl;
                cout << "\n������������ ����� ��������: " << len << endl;
            }
            return len;
        } else {
            if (showProcess) {
                cout << "? �� ������ � ������ b" << endl;
            }
        }
    }
    
    if (showProcess) {
        cout << "\n�� ���� ������� �� ������ (���������: 0)" << endl;
    }
    
    return 0;
}

// ============================================================
// ���������� ��������� ��� ������ ���
// ============================================================

double parsePrice(string priceStr) {
    priceStr.erase(remove(priceStr.begin(), priceStr.end(), ' '), priceStr.end());
    
    size_t lastComma = priceStr.rfind(',');
    size_t lastDot = priceStr.rfind('.');
    
    if (lastComma != string::npos && lastDot != string::npos) {
        if (lastComma > lastDot) {
            priceStr.erase(remove(priceStr.begin(), priceStr.end(), '.'), priceStr.end());
            replace(priceStr.begin(), priceStr.end(), ',', '.');
        } else {
            priceStr.erase(remove(priceStr.begin(), priceStr.end(), ','), priceStr.end());
        }
    } else if (lastComma != string::npos) {
        if (priceStr.length() - lastComma - 1 <= 2) {
            replace(priceStr.begin(), priceStr.end(), ',', '.');
        } else {
            priceStr.erase(remove(priceStr.begin(), priceStr.end(), ','), priceStr.end());
        }
    }
    
    return stod(priceStr);
}

vector<PriceInfo> findPricesInText(const string& text, const string& productName = "", 
                                   bool showProcess = false) {
    vector<PriceInfo> prices;
    
    if (showProcess) {
        cout << "\n========== ����� ��� � ������ ==========" << endl;
        if (!productName.empty()) {
            cout << "����� ��� ��� ������: \"" << productName << "\"" << endl;
        }
        cout << "=========================================\n" << endl;
    }
    
    regex pricePattern1(R"(([$�???])\s*([0-9]{1,3}(?:[,.\s][0-9]{3})*(?:[,.][0-9]{1,2})?))");
    regex pricePattern2(R"(([0-9]{1,3}(?:[,.\s][0-9]{3})*(?:[,.][0-9]{1,2})?)\s*([$�???]|���\.?|USD|EUR|usd|eur|����|����\.?|��������?))");
    regex pricePattern3(R"((USD|EUR|RUB|usd|eur|rub)\s*([0-9]{1,3}(?:[,.\s][0-9]{3})*(?:[,.][0-9]{1,2})?))");
    
    string searchText = text;
    int basePosition = 0;
    
    if (!productName.empty()) {
        size_t productPos = text.find(productName);
        if (productPos != string::npos) {
            size_t start = (productPos > 50) ? productPos - 50 : 0;
            size_t length = min((size_t)150, text.length() - start);
            searchText = text.substr(start, length);
            basePosition = start;
            
            if (showProcess) {
                cout << "������� ���������� ������. ��������:" << endl;
                cout << "\"" << searchText << "\"" << endl << endl;
            }
        } else {
            if (showProcess) {
                cout << "����� \"" << productName << "\" �� ������ � ������" << endl;
            }
            return prices;
        }
    }
    
    smatch match;
    string::const_iterator searchStart(searchText.cbegin());
    
    while (regex_search(searchStart, searchText.cend(), match, pricePattern1)) {
        PriceInfo price;
        price.original = match.str();
        price.currency = match[1].str();
        
        try {
            price.value = parsePrice(match[2].str());
            price.position = basePosition + distance(searchText.cbegin(), searchStart) + match.position();
            prices.push_back(price);
            
            if (showProcess) {
                cout << "������� ����: " << price.original 
                     << " - " << fixed << setprecision(2) << price.value 
                     << " " << price.currency << endl;
            }
        } catch (...) {
        }
        
        searchStart = match.suffix().first;
    }
    
    searchStart = searchText.cbegin();
    while (regex_search(searchStart, searchText.cend(), match, pricePattern2)) {
        PriceInfo price;
        price.original = match.str();
        price.currency = match[2].str();
        
        try {
            price.value = parsePrice(match[1].str());
            price.position = basePosition + distance(searchText.cbegin(), searchStart) + match.position();
            
            bool duplicate = false;
            for (const auto& p : prices) {
                if (abs(p.position - price.position) < 5) {
                    duplicate = true;
                    break;
                }
            }
            
            if (!duplicate) {
                prices.push_back(price);
                
                if (showProcess) {
                    cout << "������� ����: " << price.original 
                         << " - " << fixed << setprecision(2) << price.value 
                         << " " << price.currency << endl;
                }
            }
        } catch (...) {
        }
        
        searchStart = match.suffix().first;
    }
    
    searchStart = searchText.cbegin();
    while (regex_search(searchStart, searchText.cend(), match, pricePattern3)) {
        PriceInfo price;
        price.original = match.str();
        price.currency = match[1].str();
        
        try {
            price.value = parsePrice(match[2].str());
            price.position = basePosition + distance(searchText.cbegin(), searchStart) + match.position();
            
            bool duplicate = false;
            for (const auto& p : prices) {
                if (abs(p.position - price.position) < 5) {
                    duplicate = true;
                    break;
                }
            }
            
            if (!duplicate) {
                prices.push_back(price);
                
                if (showProcess) {
                    cout << "������� ����: " << price.original 
                         << " - " << fixed << setprecision(2) << price.value 
                         << " " << price.currency << endl;
                }
            }
        } catch (...) {
        }
        
        searchStart = match.suffix().first;
    }
    
    if (showProcess) {
        cout << "\n����� ������� ���: " << prices.size() << endl;
    }
    
    return prices;
}

string generateLargeText(int size) {
    string text;
    string words[] = {"hello", "world", "test", "pattern", "search", 
                     "algorithm", "performance", "benchmark", "data", "string"};
    
    srand(time(0));
    for (int i = 0; i < size; i++) {
        text += words[rand() % 10] + " ";
    }
    
    return text;
}

void measureKMPPerformance() {
    cout << "\n========== ������ ������������������ ��� ==========" << endl;
    cout << "| ������ ������ | ����� (���) | T(n)/n | ��������� |" << endl;
    cout << "|---------------|-------------|--------|-----------|" << endl;
    
    int sizes[] = {100000, 200000, 300000, 400000, 500000};
    string pattern = "algorithm";
    
    for (int size : sizes) {
        string text = generateLargeText(size);
        
        auto start = high_resolution_clock::now();
        KMPSearch(text, pattern, false);
        auto end = high_resolution_clock::now();
        
        auto duration = duration_cast<microseconds>(end - start).count();
        double complexity = (double)duration / size;
        
        cout << "| " << setw(13) << size 
             << " | " << setw(11) << duration 
             << " | " << setw(6) << fixed << setprecision(4) << complexity 
             << " | O(n+m)    |" << endl;
    }
    
    cout << "\n������������� ���������: O(n + m)" << endl;
    cout << "������������ ���������: �������� �����������" << endl;
}

// ============================================================
// ������������
// ============================================================

void testStringSearch() {
    cout << "\n??????????????????????????????????????????????????????????" << endl;
      cout << "?     ������������ ���������� ������ � ������            ?" << endl;
      cout << "?              ������� 8 - ��� � ���������               ?" << endl;
      cout << "??????????????????????????????????????????????????????????\n" << endl;
    
    cout << "\n???????????????????????????????????????????????????????" << endl;
      cout << "?  ������ 1: ����� ������������� �������� ������      ?" << endl;
      cout << "???????????????????????????????????????????????????????" << endl;
    
    cout << "\n--- ���� 1.1: ������ ������� ������ � ������ ---" << endl;
    string a1 = "abcdef";
    string b1 = "123abcdef456";
    int result1 = findMaxPrefixInString(a1, b1, true);
    cout << "���������: " << result1 << " (���������: 6)" << endl;
    
    cout << "\n--- ���� 1.2: ��������� ������� ---" << endl;
    string a2 = "abcdef";
    string b2 = "123abc456";
    int result2 = findMaxPrefixInString(a2, b2, true);
    cout << "���������: " << result2 << " (���������: 3)" << endl;
    
    cout << "\n--- ���� 1.3: ������� �� ������ ---" << endl;
    string a3 = "xyz";
    string b3 = "abcdef";
    int result3 = findMaxPrefixInString(a3, b3, true);
    cout << "���������: " << result3 << " (���������: 0)" << endl;
    
    cout << "\n--- ���� 1.4: �������� ����� ---" << endl;
    string a5 = "���������";
    string b5 = "� ���� ������ ���� ����� ���������������� � ��� ��������� ���������";
    findMaxPrefixInString(a5, b5, true);
    
    cout << "\n\n???????????????????????????????????????????????????????" << endl;
        cout << "?  ������ 2: ����� ��� �� ������ � ������             ?" << endl;
        cout << "???????????????????????????????????????????????????????" << endl;
    
    cout << "\n--- ���� 2.1: ��������� ������� ��� ---" << endl;
    string text1 = "������: ������ $2.50, ���� 45 ���., ��� �12,99, "
                   "����� 250.00 ���, ��� ?199, ���� USD 15.99";
    findPricesInText(text1, "", true);
    
    cout << "\n--- ���� 2.2: ���� � ������������� ����� ---" << endl;
    string text2 = "������� ����� $1,299.99, ������� - 45 900 ���., "
                   "������� EUR 899,50";
    findPricesInText(text2, "", true);
    
    cout << "\n--- ���� 2.3: ����� ���� ����������� ������ ---" << endl;
    string text3 = "� ��������: ������� HP �� $1,299.99, "
                   "������� Dell �� ���� $899, "
                   "������� Asus ����� 65000 ���.";
    findPricesInText(text3, "������� Dell", true);
    
    cout << "\n\n???????????????????????????????????????????????????????" << endl;
        cout << "?  ������ ������������������ ��������� ���            ?" << endl;
        cout << "???????????????????????????????????????????????????????" << endl;
    
    measureKMPPerformance();
    
    cout << "\n\n???????????????????????????????????????????????????????" << endl;
        cout << "?  ��������� ������ ������ ��������� ���              ?" << endl;
        cout << "???????????????????????????????????????????????????????" << endl;
    
    cout << "\n--- �������� ����� ---" << endl;
    string text5 = "abcabcabdabc";
    string pattern1 = "abcabd";
    cout << "�����: \"" << text5 << "\"" << endl;
    cout << "�������: \"" << pattern1 << "\"" << endl;
    KMPSearch(text5, pattern1, true);
    
    cout << "\n--- ���������� ����� ---" << endl;
    string pattern2 = "xyz";
    cout << "�����: \"" << text5 << "\"" << endl;
    cout << "�������: \"" << pattern2 << "\"" << endl;
    KMPSearch(text5, pattern2, true);
    
    cout << "\n??????????????????????????????????????????????????????????" << endl;
      cout << "?          \n������������ ������� ���������                ?" << endl;
      cout << "??????????????????????????????????????????????????????????\n" << endl;
}

void testFileHash() {
    cout << "\n????????????????????????????????????????????????????????" << endl;
      cout << "?   ����������� ������������ ������ � ���-��������     ?" << endl;
      cout << "????????????????????????????????????????????????????????\n" << endl;
    
    cout << "\n--- ���� 1: ���������� ���������� ����� ---" << endl;
    
    ofstream testFile("books_test.txt");
    testFile << "978000000001,������� �.�.,����� � ���,1869\n";
    testFile << "978000000012,����������� �.�.,������������ � ���������,1866\n";
    testFile << "978000000023,������ �.�.,������� ������,1833\n";
    testFile << "978000000034,�������� �.�.,������ � ���������,1967\n";
    testFile << "978000000045,����� �.�.,�������� ���,1904\n";
    testFile << "978000000056,�������� �.�.,���� � ����,1862\n";
    testFile << "978000000067,������ �.�.,������� ����,1842\n";
    testFile << "978000000078,��������� �.�.,����� ������ �������,1840\n";
    testFile.close();
    
    createBinaryFromText("books_test.txt");
    
    cout << "\n--- ���� 2: �������� ���-������� �� ����� ---" << endl;
    HashTable ht = buildHashTableFromFile();
    printHashTable(ht);
    
    cout << "\n--- ���� 3: ����� ����� �� ISBN ---" << endl;
    Book foundBook;
    long long searchISBN = 978000000034;
    
    cout << "����� ISBN: " << searchISBN << endl;
    if (findBookByISBN(ht, searchISBN, foundBook)) {
        cout << "\n����� �������:" << endl;
        printBook(foundBook);
    }
    
    cout << "\n--- ���� 4: ���������� ����� ����� ---" << endl;
    Book newBook(978000000089, "������� �.�.", "����� ���");
    addBookWithHash(ht, newBook);
    printHashTable(ht);
    
    cout << "\n--- ���� 5: ���������� ���� (� ����������) ---" << endl;
    Book book1(978000000090, "������� �.�.", "������");
    Book book2(978000000101, "���������� �.�.", "���� ���� ����� ����������");
    addBookWithHash(ht, book1);
    addBookWithHash(ht, book2);
    
    cout << "\n--- ���� 6: ������� �������� �������� ---" << endl;
    Book duplicate(978000000001, "��������", "����");
    addBookWithHash(ht, duplicate);
    
    cout << "\n--- ���� 7: �������� ����� ---" << endl;
    deleteBookByISBN(ht, 978000000012);
    printHashTable(ht);
    
    cout << "\n--- ���� 8: ������� ����� ��������� ����� ---" << endl;
    if (!findBookByISBN(ht, 978000000012, foundBook)) {
        cout << "����� ��������� ������� �� ���-�������" << endl;
    }
    
    cout << "\n--- ���� 9: ���������� ������� �� ������������� ---" << endl;
    cout << "������� ����������� ����������: " << ht.loadFactor << endl;
    
    int counter = 200;
    while (ht.loadFactor < 0.75 && counter < 300) {
        Book tempBook(978000000000LL + counter, "�����", "��������");
        if (!addBookWithHash(ht, tempBook)) {
            break;
        }
        counter++;
    }
    
    cout << "����� ����������:" << endl;
    cout << "������ �������: " << ht.size << endl;
    cout << "���������: " << ht.count << endl;
    cout << "����������� ����������: " << ht.loadFactor << endl;
    
    cout << "\n���������� �����, ���������� �������������..." << endl;
    Book triggerBook(978000000300, "�������", "�������������");
    addBookWithHash(ht, triggerBook);
    
    cout << "\n����� �������������:" << endl;
    cout << "������ �������: " << ht.size << endl;
    cout << "���������: " << ht.count << endl;
    cout << "����������� ����������: " << ht.loadFactor << endl;
    
    cout << "\n--- ���� 10: ���� � ������� ������ (500+ �������) ---" << endl;
    createLargeTestFile(500);
    createBinaryFromText("books_test.txt");
    
    HashTable largeHt = buildHashTableFromFile();
    
    cout << "\n--- ���� 11: ��������� ������������������ ---" << endl;
    compareSearchPerformance(largeHt);
    
    cout << "\n????????????????????????????????????????????????????????" << endl;
      cout << "?       ����������� ������������ ���������             ?" << endl;
      cout << "????????????????????????????????????????????????????????\n" << endl;
}

// ============================================================
// ������� ���� � MAIN
// ============================================================

void showMenu() {
    cout << "\n????????????????????????????????????????????????????????" << endl;
      cout << "?        ������������ ������ - ������� 8               ?" << endl;
      cout << "????????????????????????????????????????????????????????" << endl;
    cout << "\n�������� ������ ��� ������������:\n" << endl;

    cout << "\n1. ������������ ������ 6.1 - ���-�������" << endl;
    cout << "   � ���������� ������� ����� ���-�������" << endl;
    cout << "   � ������� �����������" << endl;
    cout << "   � ������ ������ � �����" << endl;
    
    cout << "\n2. ������������ ������ 6.2 - ����� � ������" << endl;
    cout << "   � �������� �����-������-������" << endl;
    cout << "   � ����� ������������� ��������" << endl;
    cout << "   � ����� ��� ����������� �����������" << endl;
    
    
    cout << "\n0. �����" << endl;
    
    cout << "\n��� �����: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int choice;
    bool running = true;
    
    while (running) {
        showMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                testFileHash();
                cout << "\n������� Enter ��� �����������...";
                cin.get();
                break;
                
            case 2:
                testStringSearch();
                cout << "\n������� Enter ��� �����������...";
                cin.get();
                break;
                
            case 0:
                running = false;
                cout << "\n���������� ������ ���������..." << endl;
                break;
                
            default:
                cout << "\n�������� �����! ���������� �����." << endl;
                cout << "������� Enter ��� �����������...";
                cin.get();
                break;
        }
    }
    
    return 0;
}