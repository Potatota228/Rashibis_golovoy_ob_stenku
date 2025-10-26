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
// СТРУКТУРЫ ДАННЫХ
// ============================================================

// Структура записи книги
struct Book {
    long long isbn;        // ISBN - 12-значное число (ключ)
    char author[50];       // Автор
    char title[100];       // Название
    
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

// Структура элемента хеш-таблицы
struct HashElement {
    long long key;        // Ключ (ISBN книги)
    int recordNumber;     // Номер записи в файле
    bool isOccupied;      // Ячейка занята
    bool isDeleted;       // Ячейка была удалена
    
    HashElement() : key(0), recordNumber(-1), isOccupied(false), isDeleted(false) {}
};

// Структура хеш-таблицы
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

// Структура для информации о цене
struct PriceInfo {
    string original;
    double value;
    string currency;
    int position;
};

// ============================================================
// ХЕШ-ТАБЛИЦА: ФУНКЦИИ
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
            cout << "Требуется рехеширование! Коэффициент заполнения: " << ht.loadFactor << endl;
        }
        return false;
    }
    
    int h1 = hash1(key, ht.size);
    int h2 = hash2(key, ht.size);
    int index = h1;
    int attempt = 0;
    
    if (showIndexes) {
        cout << "Вставка ключа " << key << ": hash1=" << h1 << ", hash2=" << h2 << endl;
    }
    
    while (attempt < ht.size) {
        index = (h1 + attempt * h2) % ht.size;
        
        if (showIndexes) {
            cout << "  Попытка " << attempt << ": индекс " << index;
        }
        
        if (!ht.table[index].isOccupied || ht.table[index].isDeleted) {
            ht.table[index].key = key;
            ht.table[index].recordNumber = recordNum;
            ht.table[index].isOccupied = true;
            ht.table[index].isDeleted = false;
            ht.count++;
            updateLoadFactor(ht);
            
            if (showIndexes) {
                cout << " - успешно вставлен" << endl;
            }
            return true;
        }
        
        if (ht.table[index].key == key && !ht.table[index].isDeleted) {
            if (showIndexes) {
                cout << " - ключ уже существует" << endl;
            }
            return false;
        }
        
        if (showIndexes) {
            cout << " - занято (коллизия)" << endl;
        }
        
        attempt++;
    }
    
    cout << "Таблица переполнена!" << endl;
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
    
    cout << "Рехеширование: старый размер = " << oldHt.size 
         << ", новый размер = " << newSize << endl;
    
    HashTable newHt(newSize);
    
    for (int i = 0; i < oldHt.size; i++) {
        if (oldHt.table[i].isOccupied && !oldHt.table[i].isDeleted) {
            insertKey(newHt, oldHt.table[i].key, oldHt.table[i].recordNumber);
        }
    }
    
    return newHt;
}

void printHashTable(const HashTable& ht) {
    cout << "\n=== Хеш-таблица ===" << endl;
    cout << "Размер: " << ht.size << ", Элементов: " << ht.count 
         << ", Коэффициент заполнения: " << fixed << setprecision(3) << ht.loadFactor << endl;
    
    int printed = 0;
    for (int i = 0; i < ht.size && printed < 10; i++) {
        if (ht.table[i].isOccupied && !ht.table[i].isDeleted) {
            cout << "[" << i << "] ISBN: " << ht.table[i].key 
                 << ", Запись №" << ht.table[i].recordNumber << endl;
            printed++;
        }
    }
    if (ht.count > 10) {
        cout << "... и еще " << (ht.count - 10) << " элементов" << endl;
    }
    cout << "==================\n" << endl;
}

// ============================================================
// РАБОТА С ФАЙЛАМИ
// ============================================================

const string BINARY_FILE = "books.bin";

void printBook(const Book& book) {
    if (book.isbn == 0) {
        cout << "Запись не найдена\n";
    } else {
        cout << "ISBN: " << book.isbn << "\n";
        cout << "Автор: " << book.author << "\n";
        cout << "Название: " << book.title << "\n";
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
        cout << "Ошибка открытия файлов" << endl;
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
// УПРАВЛЕНИЕ ФАЙЛОМ ЧЕРЕЗ ХЕШ-ТАБЛИЦУ
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
    
    cout << "Создание хеш-таблицы из файла..." << endl;
    cout << "Записей в файле: " << recordCount << ", Размер таблицы: " << tableSize << endl;
    
    ifstream file(BINARY_FILE, ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
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
    
    cout << "Хеш-таблица создана. Элементов: " << ht.count << endl;
    
    return ht;
}

bool addBookWithHash(HashTable& ht, const Book& book) {
    if (searchKey(ht, book.isbn) != -1) {
        cout << "Книга с ISBN " << book.isbn << " уже существует!" << endl;
        return false;
    }
    
    int recordNum = getRecordCount();
    
    if (!appendRecord(book)) {
        return false;
    }
    
    if (ht.loadFactor >= 0.75) {
        cout << "Выполняется рехеширование..." << endl;
        ht = rehash(ht);
    }
    
    if (!insertKey(ht, book.isbn, recordNum)) {
        cout << "Ошибка добавления в хеш-таблицу" << endl;
        return false;
    }
    
    cout << "Книга добавлена. ISBN: " << book.isbn << ", Запись №" << recordNum << endl;
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
        cout << "Книга с ISBN " << isbn << " не найдена в хеш-таблице" << endl;
        return false;
    }
    
    if (!deleteRecordByKey(isbn)) {
        cout << "Ошибка удаления из файла" << endl;
        return false;
    }
    
    cout << "Книга с ISBN " << isbn << " успешно удалена" << endl;
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
    cout << "\n========== СРАВНЕНИЕ ПРОИЗВОДИТЕЛЬНОСТИ ==========" << endl;
    
    int recordCount = getRecordCount();
    
    if (recordCount == 0) {
        cout << "Файл пуст!" << endl;
        return;
    }
    
    Book firstBook, middleBook, lastBook;
    
    readRecordByNumber(0, firstBook);
    readRecordByNumber(recordCount / 2, middleBook);
    readRecordByNumber(recordCount - 1, lastBook);
    
    cout << "\nКоличество записей в файле: " << recordCount << endl;
    cout << "\nТестирование поиска:" << endl;
    cout << "------------------------------------------------" << endl;
    
    cout << "\n1. ПЕРВАЯ ЗАПИСЬ (ISBN: " << firstBook.isbn << ")" << endl;
    double hashTime1 = measureHashSearch(ht, firstBook.isbn);
    double linearTime1 = measureLinearSearch(firstBook.isbn);
    cout << "   Хеш-таблица:    " << fixed << setprecision(2) << hashTime1 << " мкс" << endl;
    cout << "   Линейный поиск: " << linearTime1 << " мкс" << endl;
    cout << "   Ускорение:      " << (linearTime1 / hashTime1) << "x" << endl;
    
    cout << "\n2. СРЕДНЯЯ ЗАПИСЬ (ISBN: " << middleBook.isbn << ")" << endl;
    double hashTime2 = measureHashSearch(ht, middleBook.isbn);
    double linearTime2 = measureLinearSearch(middleBook.isbn);
    cout << "   Хеш-таблица:    " << hashTime2 << " мкс" << endl;
    cout << "   Линейный поиск: " << linearTime2 << " мкс" << endl;
    cout << "   Ускорение:      " << (linearTime2 / hashTime2) << "x" << endl;
    
    cout << "\n3. ПОСЛЕДНЯЯ ЗАПИСЬ (ISBN: " << lastBook.isbn << ")" << endl;
    double hashTime3 = measureHashSearch(ht, lastBook.isbn);
    double linearTime3 = measureLinearSearch(lastBook.isbn);
    cout << "   Хеш-таблица:    " << hashTime3 << " мкс" << endl;
    cout << "   Линейный поиск: " << linearTime3 << " мкс" << endl;
    cout << "   Ускорение:      " << (linearTime3 / hashTime3) << "x" << endl;
    
    cout << "\n------------------------------------------------" << endl;
    cout << "ВЫВОД: Время доступа через хеш-таблицу примерно" << endl;
    cout << "одинаково для всех записей (O(1))," << endl;
    cout << "в то время как линейный поиск зависит от позиции (O(n))." << endl;
    cout << "==================================================\n" << endl;
}

void createLargeTestFile(int numRecords) {
    cout << "Создание тестового файла с " << numRecords << " записями..." << endl;
    
    ofstream testFile("books_test.txt");
    
    string authors[] = {"Толстой Л.Н.", "Достоевский Ф.М.", "Пушкин А.С.", 
                       "Булгаков М.А.", "Чехов А.П.", "Тургенев И.С.",
                       "Гоголь Н.В.", "Лермонтов М.Ю.", "Шолохов М.А.", "Набоков В.В."};
    
    string titles[] = {"Война и мир", "Преступление и наказание", "Евгений Онегин",
                      "Мастер и Маргарита", "Вишневый сад", "Отцы и дети",
                      "Мертвые души", "Герой нашего времени", "Тихий Дон", "Лолита"};
    
    srand(time(0));
    
    for (int i = 0; i < numRecords; i++) {
        long long isbn = 978000000000LL + i;
        string author = authors[rand() % 10];
        string title = titles[rand() % 10];
        int year = 1800 + rand() % 224;
        
        testFile << isbn << "," << author << "," << title << "," << year << "\n";
    }
    
    testFile.close();
    cout << "Файл создан." << endl;
}

// ============================================================
// АЛГОРИТМЫ ПОИСКА В ТЕКСТЕ (КМП)
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
        cout << "\nПрефикс-функция для образца \"" << pattern << "\":" << endl;
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
                cout << "Найдено вхождение на позиции: " << (i - m + 1) << endl;
                cout << "Количество сравнений: " << comparisons << endl;
            }
            return i - m + 1;
        }
    }
    
    if (showProcess) {
        cout << "Образец не найден" << endl;
        cout << "Количество сравнений: " << comparisons << endl;
    }
    
    return -1;
}

int findMaxPrefixInString(const string& a, const string& b, bool showProcess = false) {
    if (a.empty()) return 0;
    
    if (showProcess) {
        cout << "\n========== ПОИСК МАКСИМАЛЬНОГО ПРЕФИКСА ==========" << endl;
        cout << "Строка a: \"" << a << "\"" << endl;
        cout << "Строка b: \"" << b << "\"" << endl;
        cout << "===================================================\n" << endl;
    }
    
    int maxLen = min(a.length(), b.length());
    
    for (int len = maxLen; len >= 1; len--) {
        string prefix = a.substr(0, len);
        
        if (showProcess) {
            cout << "Проверяем префикс длины " << len << ": \"" << prefix << "\"" << endl;
        }
        
        int pos = KMPSearch(b, prefix, false);
        
        if (pos != -1) {
            if (showProcess) {
                cout << "? Найден на позиции " << pos << " в строке b" << endl;
                cout << "\nМаксимальная длина префикса: " << len << endl;
            }
            return len;
        } else {
            if (showProcess) {
                cout << "? Не найден в строке b" << endl;
            }
        }
    }
    
    if (showProcess) {
        cout << "\nНи один префикс не найден (результат: 0)" << endl;
    }
    
    return 0;
}

// ============================================================
// РЕГУЛЯРНЫЕ ВЫРАЖЕНИЯ ДЛЯ ПОИСКА ЦЕН
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
        cout << "\n========== ПОИСК ЦЕН В ТЕКСТЕ ==========" << endl;
        if (!productName.empty()) {
            cout << "Поиск цен для товара: \"" << productName << "\"" << endl;
        }
        cout << "=========================================\n" << endl;
    }
    
    regex pricePattern1(R"(([$€???])\s*([0-9]{1,3}(?:[,.\s][0-9]{3})*(?:[,.][0-9]{1,2})?))");
    regex pricePattern2(R"(([0-9]{1,3}(?:[,.\s][0-9]{3})*(?:[,.][0-9]{1,2})?)\s*([$€???]|руб\.?|USD|EUR|usd|eur|евро|долл\.?|долларов?))");
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
                cout << "Найдено упоминание товара. Контекст:" << endl;
                cout << "\"" << searchText << "\"" << endl << endl;
            }
        } else {
            if (showProcess) {
                cout << "Товар \"" << productName << "\" не найден в тексте" << endl;
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
                cout << "Найдена цена: " << price.original 
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
                    cout << "Найдена цена: " << price.original 
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
                    cout << "Найдена цена: " << price.original 
                         << " - " << fixed << setprecision(2) << price.value 
                         << " " << price.currency << endl;
                }
            }
        } catch (...) {
        }
        
        searchStart = match.suffix().first;
    }
    
    if (showProcess) {
        cout << "\nВсего найдено цен: " << prices.size() << endl;
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
    cout << "\n========== ОЦЕНКА ПРОИЗВОДИТЕЛЬНОСТИ КМП ==========" << endl;
    cout << "| Размер текста | Время (мкс) | T(n)/n | Сложность |" << endl;
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
    
    cout << "\nТеоретическая сложность: O(n + m)" << endl;
    cout << "Практическая сложность: линейная зависимость" << endl;
}

// ============================================================
// ТЕСТИРОВАНИЕ
// ============================================================

void testStringSearch() {
    cout << "\n??????????????????????????????????????????????????????????" << endl;
      cout << "?     ТЕСТИРОВАНИЕ АЛГОРИТМОВ ПОИСКА В ТЕКСТЕ            ?" << endl;
      cout << "?              Вариант 8 - КМП и Регулярки               ?" << endl;
      cout << "??????????????????????????????????????????????????????????\n" << endl;
    
    cout << "\n???????????????????????????????????????????????????????" << endl;
      cout << "?  ЗАДАЧА 1: Поиск максимального префикса строки      ?" << endl;
      cout << "???????????????????????????????????????????????????????" << endl;
    
    cout << "\n--- Тест 1.1: Полный префикс входит в строку ---" << endl;
    string a1 = "abcdef";
    string b1 = "123abcdef456";
    int result1 = findMaxPrefixInString(a1, b1, true);
    cout << "Результат: " << result1 << " (ожидается: 6)" << endl;
    
    cout << "\n--- Тест 1.2: Частичный префикс ---" << endl;
    string a2 = "abcdef";
    string b2 = "123abc456";
    int result2 = findMaxPrefixInString(a2, b2, true);
    cout << "Результат: " << result2 << " (ожидается: 3)" << endl;
    
    cout << "\n--- Тест 1.3: Префикс не найден ---" << endl;
    string a3 = "xyz";
    string b3 = "abcdef";
    int result3 = findMaxPrefixInString(a3, b3, true);
    cout << "Результат: " << result3 << " (ожидается: 0)" << endl;
    
    cout << "\n--- Тест 1.4: Реальный текст ---" << endl;
    string a5 = "программа";
    string b5 = "В этом тексте есть слово программирование и еще программа полностью";
    findMaxPrefixInString(a5, b5, true);
    
    cout << "\n\n???????????????????????????????????????????????????????" << endl;
        cout << "?  ЗАДАЧА 2: Поиск цен на товары в тексте             ?" << endl;
        cout << "???????????????????????????????????????????????????????" << endl;
    
    cout << "\n--- Тест 2.1: Различные форматы цен ---" << endl;
    string text1 = "Товары: молоко $2.50, хлеб 45 руб., сыр €12,99, "
                   "масло 250.00 руб, чай ?199, кофе USD 15.99";
    findPricesInText(text1, "", true);
    
    cout << "\n--- Тест 2.2: Цены с разделителями тысяч ---" << endl;
    string text2 = "Ноутбук стоит $1,299.99, телефон - 45 900 руб., "
                   "планшет EUR 899,50";
    findPricesInText(text2, "", true);
    
    cout << "\n--- Тест 2.3: Поиск цены конкретного товара ---" << endl;
    string text3 = "В магазине: ноутбук HP за $1,299.99, "
                   "ноутбук Dell по цене $899, "
                   "ноутбук Asus стоит 65000 руб.";
    findPricesInText(text3, "ноутбук Dell", true);
    
    cout << "\n\n???????????????????????????????????????????????????????" << endl;
        cout << "?  ОЦЕНКА ПРОИЗВОДИТЕЛЬНОСТИ АЛГОРИТМА КМП            ?" << endl;
        cout << "???????????????????????????????????????????????????????" << endl;
    
    measureKMPPerformance();
    
    cout << "\n\n???????????????????????????????????????????????????????" << endl;
        cout << "?  ДЕТАЛЬНЫЙ АНАЛИЗ РАБОТЫ АЛГОРИТМА КМП              ?" << endl;
        cout << "???????????????????????????????????????????????????????" << endl;
    
    cout << "\n--- Успешный поиск ---" << endl;
    string text5 = "abcabcabdabc";
    string pattern1 = "abcabd";
    cout << "Текст: \"" << text5 << "\"" << endl;
    cout << "Образец: \"" << pattern1 << "\"" << endl;
    KMPSearch(text5, pattern1, true);
    
    cout << "\n--- Неуспешный поиск ---" << endl;
    string pattern2 = "xyz";
    cout << "Текст: \"" << text5 << "\"" << endl;
    cout << "Образец: \"" << pattern2 << "\"" << endl;
    KMPSearch(text5, pattern2, true);
    
    cout << "\n??????????????????????????????????????????????????????????" << endl;
      cout << "?          \nТЕСТИРОВАНИЕ УСПЕШНО ЗАВЕРШЕНО                ?" << endl;
      cout << "??????????????????????????????????????????????????????????\n" << endl;
}

void testFileHash() {
    cout << "\n????????????????????????????????????????????????????????" << endl;
      cout << "?   КОМПЛЕКСНОЕ ТЕСТИРОВАНИЕ РАБОТЫ С ХЕШ-ТАБЛИЦЕЙ     ?" << endl;
      cout << "????????????????????????????????????????????????????????\n" << endl;
    
    cout << "\n--- ЭТАП 1: Подготовка небольшого файла ---" << endl;
    
    ofstream testFile("books_test.txt");
    testFile << "978000000001,Толстой Л.Н.,Война и мир,1869\n";
    testFile << "978000000012,Достоевский Ф.М.,Преступление и наказание,1866\n";
    testFile << "978000000023,Пушкин А.С.,Евгений Онегин,1833\n";
    testFile << "978000000034,Булгаков М.А.,Мастер и Маргарита,1967\n";
    testFile << "978000000045,Чехов А.П.,Вишневый сад,1904\n";
    testFile << "978000000056,Тургенев И.С.,Отцы и дети,1862\n";
    testFile << "978000000067,Гоголь Н.В.,Мертвые души,1842\n";
    testFile << "978000000078,Лермонтов М.Ю.,Герой нашего времени,1840\n";
    testFile.close();
    
    createBinaryFromText("books_test.txt");
    
    cout << "\n--- ЭТАП 2: Создание хеш-таблицы из файла ---" << endl;
    HashTable ht = buildHashTableFromFile();
    printHashTable(ht);
    
    cout << "\n--- ЭТАП 3: Поиск книги по ISBN ---" << endl;
    Book foundBook;
    long long searchISBN = 978000000034;
    
    cout << "Поиск ISBN: " << searchISBN << endl;
    if (findBookByISBN(ht, searchISBN, foundBook)) {
        cout << "\nКнига найдена:" << endl;
        printBook(foundBook);
    }
    
    cout << "\n--- ЭТАП 4: Добавление новой книги ---" << endl;
    Book newBook(978000000089, "Шолохов М.А.", "Тихий Дон");
    addBookWithHash(ht, newBook);
    printHashTable(ht);
    
    cout << "\n--- ЭТАП 5: Добавление книг (с коллизиями) ---" << endl;
    Book book1(978000000090, "Набоков В.В.", "Лолита");
    Book book2(978000000101, "Солженицын А.И.", "Один день Ивана Денисовича");
    addBookWithHash(ht, book1);
    addBookWithHash(ht, book2);
    
    cout << "\n--- ЭТАП 6: Попытка добавить дубликат ---" << endl;
    Book duplicate(978000000001, "Дубликат", "Тест");
    addBookWithHash(ht, duplicate);
    
    cout << "\n--- ЭТАП 7: Удаление книги ---" << endl;
    deleteBookByISBN(ht, 978000000012);
    printHashTable(ht);
    
    cout << "\n--- ЭТАП 8: Попытка найти удаленную книгу ---" << endl;
    if (!findBookByISBN(ht, 978000000012, foundBook)) {
        cout << "Книга корректно удалена из хеш-таблицы" << endl;
    }
    
    cout << "\n--- ЭТАП 9: Заполнение таблицы до рехеширования ---" << endl;
    cout << "Текущий коэффициент заполнения: " << ht.loadFactor << endl;
    
    int counter = 200;
    while (ht.loadFactor < 0.75 && counter < 300) {
        Book tempBook(978000000000LL + counter, "Автор", "Название");
        if (!addBookWithHash(ht, tempBook)) {
            break;
        }
        counter++;
    }
    
    cout << "После заполнения:" << endl;
    cout << "Размер таблицы: " << ht.size << endl;
    cout << "Элементов: " << ht.count << endl;
    cout << "Коэффициент заполнения: " << ht.loadFactor << endl;
    
    cout << "\nДобавление книги, вызывающей рехеширование..." << endl;
    Book triggerBook(978000000300, "Триггер", "Рехеширование");
    addBookWithHash(ht, triggerBook);
    
    cout << "\nПосле рехеширования:" << endl;
    cout << "Размер таблицы: " << ht.size << endl;
    cout << "Элементов: " << ht.count << endl;
    cout << "Коэффициент заполнения: " << ht.loadFactor << endl;
    
    cout << "\n--- ЭТАП 10: Тест с большим файлом (500+ записей) ---" << endl;
    createLargeTestFile(500);
    createBinaryFromText("books_test.txt");
    
    HashTable largeHt = buildHashTableFromFile();
    
    cout << "\n--- ЭТАП 11: Сравнение производительности ---" << endl;
    compareSearchPerformance(largeHt);
    
    cout << "\n????????????????????????????????????????????????????????" << endl;
      cout << "?       КОМПЛЕКСНОЕ ТЕСТИРОВАНИЕ ЗАВЕРШЕНО             ?" << endl;
      cout << "????????????????????????????????????????????????????????\n" << endl;
}

// ============================================================
// ГЛАВНОЕ МЕНЮ И MAIN
// ============================================================

void showMenu() {
    cout << "\n????????????????????????????????????????????????????????" << endl;
      cout << "?        ПРАКТИЧЕСКИЕ РАБОТЫ - ВАРИАНТ 8               ?" << endl;
      cout << "????????????????????????????????????????????????????????" << endl;
    cout << "\nВыберите задачу для тестирования:\n" << endl;

    cout << "\n1. Практическая работа 6.1 - Хеш-таблицы" << endl;
    cout << "   • Управление книгами через хеш-таблицу" << endl;
    cout << "   • Двойное хеширование" << endl;
    cout << "   • Прямой доступ к файлу" << endl;
    
    cout << "\n2. Практическая работа 6.2 - Поиск в тексте" << endl;
    cout << "   • Алгоритм Кнута-Мориса-Пратта" << endl;
    cout << "   • Поиск максимального префикса" << endl;
    cout << "   • Поиск цен регулярными выражениями" << endl;
    
    
    cout << "\n0. Выход" << endl;
    
    cout << "\nВаш выбор: ";
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
                cout << "\nНажмите Enter для продолжения...";
                cin.get();
                break;
                
            case 2:
                testStringSearch();
                cout << "\nНажмите Enter для продолжения...";
                cin.get();
                break;
                
            case 0:
                running = false;
                cout << "\nЗавершение работы программы..." << endl;
                break;
                
            default:
                cout << "\nНеверный выбор! Попробуйте снова." << endl;
                cout << "Нажмите Enter для продолжения...";
                cin.get();
                break;
        }
    }
    
    return 0;
}