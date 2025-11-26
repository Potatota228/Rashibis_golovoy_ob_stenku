#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

// Структура для хранения ребра графа
struct Edge {
    int from;    // откуда
    int to;      // куда
    int weight;  // вес ребра
};

// Класс для работы с графом
class Graph {
private:
    int vertices;           // количество вершин
    vector<Edge> edges;     // список всех рёбер
    
public:
    // Конструктор
    Graph(int v) {
        vertices = v;
    }
    
    // Добавление ребра в граф
    void addEdge(int from, int to, int weight) {
        Edge e;
        e.from = from;
        e.to = to;
        e.weight = weight;
        edges.push_back(e);
    }
    
    // Алгоритм Беллмана-Форда
    void bellmanFord(int start) {
        // Массив расстояний от начальной вершины
        vector<int> distance(vertices + 1, INT_MAX);
        // Массив для хранения предыдущих вершин (для восстановления пути)
        vector<int> parent(vertices + 1, -1);
        
        // Расстояние до стартовой вершины = 0
        distance[start] = 0;
        
        cout << "\n=== Алгоритм Беллмана-Форда ===" << endl;
        cout << "Начальная вершина: " << start << "\n" << endl;
        
        // Релаксация рёбер (V-1) раз
        for (int i = 1; i < vertices; i++) {
            bool updated = false;
            
            for (const Edge& e : edges) {
                // Если есть путь к вершине from и можно улучшить путь к to
                if (distance[e.from] != INT_MAX && 
                    distance[e.from] + e.weight < distance[e.to]) {
                    distance[e.to] = distance[e.from] + e.weight;
                    parent[e.to] = e.from;
                    updated = true;
                }
            }
            
            if (!updated) {
                cout << "Алгоритм завершился на итерации " << i << endl;
                break;
            }
        }
        
        // Проверка на отрицательные циклы
        bool hasNegativeCycle = false;
        for (const Edge& e : edges) {
            if (distance[e.from] != INT_MAX && 
                distance[e.from] + e.weight < distance[e.to]) {
                hasNegativeCycle = true;
                break;
            }
        }
        
        if (hasNegativeCycle) {
            cout << "\nВНИМАНИЕ: Обнаружен отрицательный цикл!" << endl;
            return;
        }
        
        // Вывод результатов
        printResults(start, distance, parent);
    }
    
    // Вывод результатов
    void printResults(int start, vector<int>& distance, vector<int>& parent) {
        cout << "\n--- Результаты ---\n" << endl;
        cout << "Вершина" << "          " << "Расстояние" << "      " << "Путь" << endl;
        cout << string(45, '-') << endl;
        
        for (int i = 1; i <= vertices; i++) {
            cout << setw(7) << i;
            if (distance[i] == INT_MAX) {
                cout << setw(18) << " ∞" << setw(20) << "            Нет пути" << endl;
            } else {
                cout << setw(16) << distance[i] << setw(10);
                printPath(i, parent);
                cout << endl;
            }
        }
    }
    
    // Рекурсивный вывод пути
    void printPath(int vertex, vector<int>& parent) {
        if (parent[vertex] == -1) {
            cout << vertex;
            return;
        }
        printPath(parent[vertex], parent);
        cout << " → " << vertex;
    }
    
    // Вывод структуры графа
    void printGraph() {
        cout << "\n=== Структура графа ===" << endl;
        cout << "Рёбра графа:" << endl;
        for (const Edge& e : edges) {
            cout << e.from << " → " << e.to << " : " << e.weight << endl;
        }
    }
};

// Функция для ввода графа с клавиатуры
void inputGraph(Graph& g) {
    int numEdges;
    cout << "Введите количество рёбер: ";
    cin >> numEdges;
    
    cout << "\nВведите рёбра в формате: вершина_откуда вершина_куда вес" << endl;
    
    for (int i = 0; i < numEdges; i++) {
        int from, to, weight;
        cout << "Ребро " << (i + 1) << ": ";
        cin >> from >> to >> weight;
        g.addEdge(from, to, weight);
    }
}

// Функция для загрузки тестового графа
void loadTestGraph(Graph& g) {
    cout << "Тестовый граф" << endl;
    
    g.addEdge(1, 2, 23);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 3, 25);
    g.addEdge(3, 4, 18);
    g.addEdge(4, 6, 20);
    g.addEdge(6, 7, 24);
    g.addEdge(7, 8, 16);
    g.addEdge(8, 2, 35);
    g.addEdge(2, 5, 22);
    g.addEdge(5, 7, 14);
    g.addEdge(5, 6, 23);
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "Алгоритм Беллмана-Форда" << endl;
    cout << "Поиск кратчайших путей в графе" << endl;
    
    int numVertices = 8; // Максимальная вершина в графе
    Graph graph(numVertices);
    
    int choice;
    cout << "\nВыберите способ ввода графа:" << endl;
    cout << "1 - Использовать тестовый граф из задания" << endl;
    cout << "2 - Ввести граф вручную" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    
    if (choice == 1) {
        loadTestGraph(graph);
    } else {
        inputGraph(graph);
    }
    
    graph.printGraph();
    
    int startVertex;
    cout << "\nВведите вершину для поиска путей: ";
    cin >> startVertex;
    
    graph.bellmanFord(startVertex);
    
    cout << "\n\nПрограмма завершена." << endl;
    
    return 0;
}