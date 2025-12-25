#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m; 
    cout << "Введите размеры поля (строки столбцы): ";
    cin >> n >> m;
    
    
    vector<vector<int>> right_time(n, vector<int>(m));
    cout << "Введите время движения вправо для каждой клетки:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> right_time[i][j];
        }
    }
    
    
    vector<vector<int>> up_time(n, vector<int>(m));
    cout << "Введите время движения вверх для каждой клетки:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> up_time[i][j];
        }
    }
    
    
    
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    
    dp[0][0] = 0;
    
    
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][0] + up_time[i-1][0];
    }
    
    
    for (int j = 1; j < m; j++) {
        dp[0][j] = dp[0][j-1] + right_time[0][j-1];
    }
    
    
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            
            int from_bottom = dp[i-1][j] + up_time[i-1][j];
            
            int from_left = dp[i][j-1] + right_time[i][j-1];
            
            dp[i][j] = min(from_bottom, from_left);
        }
    }
    
    
    cout << "\nТаблица минимальных времён:\n";
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            cout << dp[i][j] << "\t";
        }
        cout << "\n";
    }
    
    cout << "\nМинимальное время: " << dp[n-1][m-1] << "\n";
    
    
    cout << "\n=== ОЦЕНКА ПЕРЕБОРОВ ===\n";
    
    
    int dp_operations = n * m;
    cout << "Переборов при ДП: " << dp_operations << "\n";
    
    
    long long brute_force_paths = 1;
    int total_steps = n + m - 2;
    int up_steps = n - 1;
    
    
    for (int i = 0; i < up_steps; i++) {
        brute_force_paths *= (total_steps - i);
        brute_force_paths /= (i + 1);
    }
    
    cout << "Переборов при грубой силе: " << brute_force_paths << "\n";
    cout << "Выигрыш: в " << (double)brute_force_paths / dp_operations << " раз\n";
    
    return 0;
}