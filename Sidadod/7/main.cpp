#include <iostream>
using namespace std;

// Структура узла дерева
struct Node {
    char data;        // Значение узла (символ)
    Node* left;       // Указатель на левого потомка
    Node* right;      // Указатель на правого потомка
};

// Класс для работы с бинарным деревом поиска
class BST {
private:
    Node* root;  // Корень дерева

    // Вспомогательная функция для вставки элемента (рекурсивная)
    Node* insertNode(Node* node, char value) {
        // Если узел пустой - создаем новый
        if (node == NULL) {
            Node* newNode = new Node;
            newNode->data = value;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }
        
        // Если значение меньше - идем влево
        if (value < node->data) {
            node->left = insertNode(node->left, value);
        }
        // Если значение больше - идем вправо
        else if (value > node->data) {
            node->right = insertNode(node->right, value);
        }
        // Если значение равно - не вставляем дубликаты
        
        return node;
    }

    // Симметричный обход (левый - корень - правый)
    void inorderTraversal(Node* node) {
        if (node != NULL) {
            inorderTraversal(node->left);      // Сначала левое поддерево
            cout << node->data << " ";          // Потом корень
            inorderTraversal(node->right);     // Потом правое поддерево
        }
    }

    // Проверка, является ли узел листом
    bool isLeaf(Node* node) {
        return (node->left == NULL && node->right == NULL);
    }

    // Найти сумму листьев
    std::string sumOfLeaves(Node* node) {
        // Если узел пустой
        if (node == NULL) {
            return 0;
        }
        
        // Если узел - лист, возвращаем его значение (ASCII-код)
        if (isLeaf(node)) {
            return std::string(1, node->data);
        }
        
        // Иначе суммируем значения из левого и правого поддеревьев
        return sumOfLeaves(node->left) + sumOfLeaves(node->right);
    }

    // Найти высоту дерева
    int heightOfTree(Node* node) {
        // Если узел пустой - высота 0
        if (node == NULL) {
            return 0;
        }
        
        // Находим высоту левого и правого поддеревьев
        int leftHeight = heightOfTree(node->left);
        int rightHeight = heightOfTree(node->right);
        
        // Высота текущего узла = максимальная высота поддеревьев + 1
        return max(leftHeight, rightHeight) + 1;
    }

    // Вспомогательная функция для вывода дерева
void printTree(Node* node, int space) {
        if (node == NULL) return;
        
        space += 5;
        printTree(node->right, space);
        
        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";
        cout << node->data << endl;
        
        printTree(node->left, space);
    }

public:
    // Конструктор
    BST() {
        root = NULL;
    }

    // Вставка элемента (публичный метод)
    void insert(char value) {
        root = insertNode(root, value);
        cout << "Элемент '" << value << "' добавлен в дерево." << endl;
    }

    // Симметричный обход (публичный метод)
    void inorder() {
        cout << "Симметричный обход дерева: ";
        if (root == NULL) {
            cout << "Дерево пусто!";
        } else {
            inorderTraversal(root);
        }
        cout << endl;
    }

    // Найти сумму значений листьев (публичный метод)
    void findSumOfLeaves() {
        if (root == NULL) {
            cout << "Дерево пусто!" << endl;
            return;
        }
        
        std::string sum = sumOfLeaves(root);
        cout << "Сумма листьев (строка): " << sum << endl;
    }

    // Найти высоту дерева (публичный метод)
    void findHeight() {
        if (root == NULL) {
            cout << "Дерево пусто! Высота = 0" << endl;
            return;
        }
        
        int height = heightOfTree(root);
        cout << "Высота дерева: " << height << endl;
    }

    // Визуализация дерева
    void display() {
        if (root == NULL) {
            cout << "Дерево пусто!" << endl;
            return;
        }
        cout << "\nВизуализация дерева (повернуто на 90°):" << endl;
        printTree(root, 10);
        cout << endl;
    }

    // Проверка, пусто ли дерево
    bool isEmpty() {
        return root == NULL;
    }
};

// Функция вывода меню
void showMenu() {
    cout << "\n========================================" << endl;
    cout << "   БИНАРНОЕ ДЕРЕВО ПОИСКА (СИМВОЛЫ)" << endl;
    cout << "========================================" << endl;
    cout << "1. Создать тестовое дерево" << endl;
    cout << "2. Вставить элемент" << endl;
    cout << "3. Симметричный обход" << endl;
    cout << "4. Найти сумму значений листьев" << endl;
    cout << "5. Найти высоту дерева" << endl;
    cout << "6. Показать дерево" << endl;
    cout << "0. Выход" << endl;
    cout << "========================================" << endl;
    cout << "Выберите действие: ";
}

int main() {
    
    BST tree;
    int choice;
    char value;

    do {
        showMenu();
        cin >> choice;
        std::string s = "HKBEFNVLFEJSLIFIVKZDBGVJJSRNLKV";

        switch (choice) {
            case 1:
                for (int i = 0; i < s.length(); ++i) {
                    char c = s[i];
                    tree.insert(c);
                }
            tree.display();
            break;

            case 2:
                cout << "Введите символ для вставки: ";
                cin >> value;
                tree.insert(value);
                break;

            case 3:
                tree.inorder();
                break;

            case 4:
                tree.findSumOfLeaves();
                break;

            case 5:
                tree.findHeight();
                break;

            case 6:
                tree.display();
                break;

            case 0:
                cout << "Выход из программы..." << endl;
                break;

            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }

        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}