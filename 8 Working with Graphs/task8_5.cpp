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
    // Массив кратчайших путей для каждой вершины
    vector<int> *path = new vector<int>[Gr.size()];
    queue<int> que;
    used[x] = 1;        // Помечаем вершину x посещённой
    path[x].push_back(x);
    que.push(x);

    while (!que.empty()) {
        int y = que.front();
        que.pop();
        for (int i = 0; i < Gr[y].size(); ++i) {
            if (used[Gr[y][i]] == 0) {
                used[Gr[y][i]] = 1;    // Помечаем вершину x посещённой
                que.push(Gr[y][i]);
                // Добавляем к пути путь до предыдущей точки
                path[Gr[y][i]].insert(path[Gr[y][i]].end(), path[y].begin(), path[y].end());
                // Добавляем саму вершину в путь
                path[Gr[y][i]].push_back(Gr[y][i]);
            }
        }
    }

    // Вывод всех кратчайших путей
    for (int i = 0; i < Gr.size(); ++i) {
        cout << i << " | ";
        for (auto j = path[i].begin(); j != path[i].end(); j++) {
            cout << *j;
            if (j + 1 != path[i].end())
                cout << " -> ";
        }
            cout << endl;
    }
}

// Дан ориентированный граф. Вывести кратчайшие пути от до каждой точки
int main() {
    int N, X;
    vector<vector<int>> Gr;
    vector<int> used;
    cout << "Num of nodes: "; cin >> N;
    used.resize(N);

    Gr = makeAdjList(N);

    printAdjList(Gr);

    cout << "\nShortest paths:\n";
    widthBypass(Gr, used);
}

/* Для примера
0 1
0 4
1 3
1 5
2 1
2 7
3 6
3 2
4 5
6 2
7 2
0 0
*/
