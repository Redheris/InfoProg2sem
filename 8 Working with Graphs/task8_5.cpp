#include<iostream>
#include<vector>
#include<queue>
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
void widthBypass(vector<vector<int>> &Gr, vector<int> &used, int x = 0) {
    vector<int> path;
    queue<int> que;
    used[x] = 1;        // Помечаем вершину x посещённой
    path.push_back(x);
    que.push(x);

    while (!que.empty()) {
        int y = que.front();
        que.pop();
        for (int i = 0; i < Gr[y].size(); ++i) {
            if (used[Gr[y][i]] == 0) {
                used[Gr[y][i]] = 1;    // Помечаем вершину x посещённой
                path.push_back(Gr[y][i]);
                que.push(Gr[y][i]);
            }
        }
    }

    for (int i : path)
        if (Gr[i].size() == Gr.size() - 1)
            cout << i << " ";
    cout << endl;
}

// Дан ориентированный граф. Вывести все истоки графа
int main() {
    int N, X;
    vector<vector<int>> Gr;
    vector<int> used;
    cout << "Num of nodes: "; cin >> N;
    used.resize(N);

    Gr = makeAdjList(N);

    printAdjList(Gr);

    cout << "\nOrigins:\n";
    widthBypass(Gr, used);
}

// Для примера
// 0 1
// 0 2
// 0 3
// 2 1
// 2 3
// 1 2
// 1 0
// 3 0
// 3 2
// 3 1