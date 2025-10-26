#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <chrono>
#include <algorithm>
#include <Windows.h>
#include <cstdlib> 
#include <iomanip>
#include <io.h>
#include <fcntl.h>

using namespace std;
using namespace chrono;
// Структура записи книги
struct Book {
    long long isbn;        // ISBN - 12-значное число (ключ)
    char author[50];       // Автор
    char title[100];       // Название
};

// Структура для таблицы смещений
struct IndexRecord {
    long long isbn;        // Ключ поиска
    streampos offset;      // Смещение в файле
};

class BookDatabase {
private:
    const size_t RECORD_SIZE = sizeof(Book);
    string binaryFileName;
    vector<IndexRecord> indexTable;
    
public:
    BookDatabase(const string& fileName) : binaryFileName(fileName) {}
    
    // ЗАДАНИЕ 1: Создание файла и заполнение данными
    
    // Предусловие: fileName - корректное имя файла, recordCount > 0
    // Постусловие: создан текстовый файл с recordCount записей
    void createTextFile(const string& fileName, int recordCount) {
        ofstream file(fileName);
        if (!file.is_open()) {
            throw runtime_error("Ошибка создания текстового файла");
        }
        
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<long long> isbnDist(100000000000LL, 999999999999LL);
        
        vector<long long> usedISBNs;
        
        vector<string> authors = {
            "Пушкин А.С.", "Толстой Л.Н.", "Достоевский Ф.М.", 
            "Чехов А.П.", "Гоголь Н.В.", "Лермонтов М.Ю.",
            "Тургенев И.С.", "Булгаков М.А.", "Шолохов М.А.", "Солженицын А.И."
        };
        
        vector<string> titles = {
            "Война и мир", "Преступление и наказание", "Евгений Онегин",
            "Мастер и Маргарита", "Анна Каренина", "Отцы и дети",
            "Герой нашего времени", "Мертвые души", "Вишневый сад", "Дядя Ваня"
        };
        
        for (int i = 0; i < recordCount; ++i) {
            long long isbn;
            do {
                isbn = isbnDist(gen);
            } while (find(usedISBNs.begin(), usedISBNs.end(), isbn) != usedISBNs.end());
            
            usedISBNs.push_back(isbn);
            
            string author = authors[i % authors.size()];
            string title = titles[i % titles.size()] + " " + to_string(i + 1);
            
            file << isbn << "|" << author << "|" << title << "\n";
        }
        
        file.close();
        cout << "Создан текстовый файл с " << recordCount << " записями\n";
    }
    
    // Предусловие: textFileName существует и содержит корректные данные
    // Постусловие: создан бинарный файл и таблица индексов
    void convertToBinary(const string& textFileName) {
        ifstream textFile(textFileName);
        ofstream binaryFile(binaryFileName, ios::binary);
        
        if (!textFile.is_open() || !binaryFile.is_open()) {
            throw runtime_error("Ошибка открытия файлов для конвертации");
        }
        
        indexTable.clear();
        string line;
        streampos offset = 0;
        
        while (getline(textFile, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            
            if (pos1 == string::npos || pos2 == string::npos) continue;
            
            Book book;
            book.isbn = stoll(line.substr(0, pos1));
            
            string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string title = line.substr(pos2 + 1);
            
            strncpy(book.author, author.c_str(), sizeof(book.author) - 1);
            book.author[sizeof(book.author) - 1] = '\0';
            
            strncpy(book.title, title.c_str(), sizeof(book.title) - 1);
            book.title[sizeof(book.title) - 1] = '\0';
            
            binaryFile.write(reinterpret_cast<const char*>(&book), sizeof(book));
            
            // Добавляем в таблицу индексов
            indexTable.push_back({book.isbn, offset});
            offset += sizeof(book);
        }
        
        textFile.close();
        binaryFile.close();
        
        cout << "Конвертация завершена. Размер записи: " << sizeof(Book) << " байт\n";
        cout << "Создана таблица индексов с " << indexTable.size() << " элементами\n";
    }
    
    // ЗАДАНИЕ 2: Линейный поиск
    
    // Предусловие: бинарный файл существует и содержит корректные данные
    // Постусловие: возвращает найденную запись или пустую запись, если не найдено
    Book linearSearch(long long searchISBN) {
        ifstream file(binaryFileName, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Ошибка открытия файла для поиска");
        }
        
        Book book;
        while (file.read(reinterpret_cast<char*>(&book), sizeof(book))) {
            if (book.isbn == searchISBN) {
                file.close();
                return book;
            }
        }
        
        file.close();
        // Возвращаем пустую запись, если не найдено
        Book emptyBook = {0, "", ""};
        return emptyBook;
    }
    
    // ЗАДАНИЕ 3: Поиск с использованием таблицы индексов (бинарный поиск)
    
    // Предусловие: таблица индексов заполнена и отсортирована
    // Постусловие: возвращает смещение записи в файле или -1, если не найдено
    streampos binarySearchInIndex(long long searchISBN) {
        // Сортируем таблицу индексов по ISBN
        sort(indexTable.begin(), indexTable.end(), 
             [](const IndexRecord& a, const IndexRecord& b) {
                 return a.isbn < b.isbn;
             });
        
        int left = 0;
        int right = indexTable.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (indexTable[mid].isbn == searchISBN) {
                return indexTable[mid].offset;
            } else if (indexTable[mid].isbn < searchISBN) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return streampos(-1); // Не найдено
    }
    
    // Предусловие: offset - корректное смещение в файле
    // Постусловие: возвращает запись, прочитанную по смещению
    Book readRecordByOffset(streampos offset) {
        ifstream file(binaryFileName, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Ошибка открытия файла для чтения по смещению");
        }
        
        file.seekg(offset);
        Book book;
        file.read(reinterpret_cast<char*>(&book), sizeof(book));
        file.close();
        
        return book;
    }
    
    // Комбинированный поиск с использованием индекса
    Book indexedSearch(long long searchISBN) {
        streampos offset = binarySearchInIndex(searchISBN);
        if (offset == streampos(-1)) {
            Book emptyBook = {0, "", ""};
            return emptyBook;
        }
        return readRecordByOffset(offset);
    }
    
    // Вспомогательные методы
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
        ifstream file(binaryFileName, ios::binary);
        if (!file.is_open()) return 0;
        
        file.seekg(0, ios::end);
        streampos fileSize = file.tellg();
        file.close();
        
        return static_cast<int>(fileSize / sizeof(Book));
    }
    
    long long getRandomISBN() {
        if (indexTable.empty()) return 0;
        
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<size_t> dist(0, indexTable.size() - 1);
        
        return indexTable[dist(gen)].isbn;
    }
};

// Функция измерения времени поиска
template<typename SearchFunc>
double measureSearchTime(SearchFunc searchFunc, int iterations = 100) {
    auto start = high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        searchFunc();
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    
    return static_cast<double>(duration.count()) / iterations;
}

int main() {
    try {
        cout << "=== ПРАКТИЧЕСКАЯ РАБОТА №5 (Вариант 8) ===\n";
        cout << "Структура записи: Книга (ISBN, Автор, Название)\n";
        cout << "Размер записи: " << sizeof(Book) << " байт\n\n";

        vector<int> fileSizes = {100, 1000, 10000};

        cout << "Результаты тестирования:\n";
        cout << setw(12) << "Размер файла" << setw(20) << " Линейный поиск (мкс)"
             << setw(25) << "Поиск с индексом (мкс)" << setw(15) << "Ускорение\n";
        cout << string(70, '-') << "\n";

        for (int size : fileSizes) {
            string textFile = "books_" + to_string(size) + ".txt";
            string binaryFile = "books_" + to_string(size) + ".bin";

            BookDatabase db(binaryFile);

            // Создание и заполнение текстового файла, конвертация в бинарный
            db.createTextFile(textFile, size);
            db.convertToBinary(textFile);

            // Получаем случайный ISBN для поиска
            long long searchISBN = db.getRandomISBN();

            // Измерение времени линейного поиска
            double linearTime = measureSearchTime([&db, searchISBN]() {
                db.linearSearch(searchISBN);
            });

            // Измерение времени поиска с индексом
            double indexedTime = measureSearchTime([&db, searchISBN]() {
                db.indexedSearch(searchISBN);
            });

            double speedup = linearTime / indexedTime;

            cout << setw(12) << size << setw(20) << fixed << setprecision(2) << linearTime
                 << setw(25) << indexedTime << setw(15) << speedup << "x\n";

            // Удаляем файлы после тестирования
            if (remove(textFile.c_str()) == 0) {
                cout << "Удален текстовый файл: " << textFile << "\n";
            } else {
                cerr << "Не удалось удалить текстовый файл: " << textFile << "\n";
            }

            if (remove(binaryFile.c_str()) == 0) {
                cout << "Удален бинарный файл: " << binaryFile << "\n";
            } else {
                cerr << "Не удалось удалить бинарный файл: " << binaryFile << "\n";
            }
        }

        cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ ===\n";
        // Демонстрация на файле из 100 записей
        {
            string demoTextFile = "books_100.txt";
            string demoBinaryFile = "books_100.bin";
            BookDatabase demo(demoBinaryFile);

            demo.createTextFile(demoTextFile, 100);
            demo.convertToBinary(demoTextFile);

            long long testISBN = demo.getRandomISBN();

            cout << "\nПоиск ISBN: " << testISBN << "\n";

            cout << "\n--- Линейный поиск ---\n";
            Book result1 = demo.linearSearch(testISBN);
            demo.printBook(result1);

            cout << "\n--- Поиск с использованием индекса ---\n";
            Book result2 = demo.indexedSearch(testISBN);
            demo.printBook(result2);

            // Удаляем демонстрационные файлы
            if (remove(demoTextFile.c_str()) == 0) {
                cout << "Удален текстовый файл: " << demoTextFile << "\n";
            }
            if (remove(demoBinaryFile.c_str()) == 0) {
                cout << "Удален бинарный файл: " << demoBinaryFile << "\n";
            }
        }

        cout << "\n=== АНАЛИЗ ЭФФЕКТИВНОСТИ ===\n";
        cout << "1. Линейный поиск: O(n) - время растет линейно с размером файла\n";
        cout << "2. Поиск с индексом: O(log n) - время растет логарифмически\n";
        cout << "3. При увеличении размера файла в 10 раз, время линейного поиска\n";
        cout << "   увеличивается в ~10 раз, а индексированного - в ~3.3 раза\n";
        cout << "4. Дополнительные затраты памяти на индекс: " 
             << sizeof(IndexRecord) << " байт на запись\n";

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
