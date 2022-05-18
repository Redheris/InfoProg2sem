#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// Вывод списка смежности
void printAdjList(vector<vector<int>> v) {
    cout << "\nCurrent graph:\n";
    for (int i = 0; i < v.size(); ++i) {    // Проход по вершинам графа
        cout << i << " | ";
        for (int j : v[i])                  // Вывод смежных
            cout << j << " ";
        cout << endl;
    }
}

vector<vector<int>> makeAdjList(int N) {
    vector<vector<int>> Gr; // Список смежности
    Gr.resize(N);           // Выделение памяти
    cout << "Edges in the graph (x y) (0 0 to stop):\n";
    int x = -1, y = -1;
    // Пока пользователь не введёт "0 0"
    while (x != 0 || y != 0) {
        cin >> x >> y;
        // Выход из цикла
        if (x == 0 && y == 0)
            break;
        // Ограничения для входных данных
        if (x > N || y > N || x == y)
            continue;

        Gr[x].push_back(y);
    }
    // Сортировка и удаление дубликатов для каждой строки списка
    for (auto &i : Gr) {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
    }
    return Gr;
}

// Обход в глубину
void depthBypass(vector<vector<int>> &Gr, int *&used, int x) {
    used[x] = 1;    // Помечаем вершину x посещённой
    
    for (int i : Gr[x]) {
        if (used[i] == 0) {
            depthBypass(Gr, used, i);
        }
    }
}

// Дан ориентированный граф. Вывести все вершины, недостижимые из данной
int main() {
    int N, X;
    vector<vector<int>> Gr;
    cout << "Num of nodes: "; cin >> N;
    int *used = new int[N];

    Gr = makeAdjList(N);

    printAdjList(Gr);

    cout << "\nX: "; cin >> X;
    depthBypass(Gr, used, X);

    // Выводим непосещённые вершины
    for (int i = 0; i < N; ++i) {
        if (used[i] != 1)
            cout << i << " ";
    }
}

// Для примера
// 1 6 
// 2 3
// 3 2
// 3 1
// 4 6
// 6 5
// 0 0