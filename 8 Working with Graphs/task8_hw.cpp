#include<iostream>
#include<vector>
#include<stack>
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
        Gr[y].push_back(x);
    }
    // Сортировка и удаление дубликатов для каждой строки списка
    for (auto &i : Gr) {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
    }
    return Gr;
}

// Проверка существования ребра
bool edge(vector<int> &Gr, int x) {
    for (int i : Gr)
        if (i == x) {
            return true;
        }
    return false;
}

// Удаление ребра в неориентированном графе
void edgeDel(vector<vector<int>> &Gr, int x, int y) {
    Gr[x].erase(find(Gr[x].begin(), Gr[x].end(), y));
    Gr[y].erase(find(Gr[y].begin(), Gr[y].end(), x));
}

// Добавление ребра в неориентированном графе
void edgeAdd(vector<vector<int>> &Gr, int x, int y) {
    Gr[x].push_back(y);
    Gr[y].push_back(x);

    sort(Gr[x].begin(), Gr[x].end());
    sort(Gr[y].begin(), Gr[y].end());

    Gr[x].erase(unique(Gr[x].begin(), Gr[x].end()), Gr[x].end());
    Gr[y].erase(unique(Gr[y].begin(), Gr[y].end()), Gr[y].end());
}

bool edgesExist(vector<vector<int>> &Gr) {
    for (auto i : Gr)
        if (i.size() > 0)
            return true;
    return false;
}


void EulersCycle(vector<vector<int>> D, vector<int> &c) {
    stack<int> path;
    bool cycleExist = true;

    // Степени вершин и результирующий вектор
    vector<int> degree(D.size(), 0);

    for (int i = 0; i < D.size(); ++i)
        for (int j : D[i]) {
            degree[i]++;
        }

    int v1 = 0, v2 = -1;

    for (int i = 0; i < D.size(); ++i)
        if (degree[i] % 2 == 1) {
            if (v1 == 0)
                v1 = i;
            else if (v2 == -1)
                v2 = i;
            else {
                cout << "Euler's path doesn't exist\n";
                return;
            }
            cycleExist = false;
        }


    if (v2 != -1) {
        edgeAdd(D, v1, v2);
        degree[v1]++;
        degree[v2]++;
    }

    path.push(v1);
    while (!path.empty()) {
        int y = path.top();
        if (degree[y] != 0) {
            path.push(D[y][0]);

            degree[y]--;
            degree[D[y][0]]--;
            edgeDel(D, y, D[y][0]);
        }
        else {
            c.push_back(y);
            path.pop();
        }
    }

    if (v2 != -1) {
        for (int i = 1; i <= c.size(); ++i) {
            if (c[i - 1] == v1 && c[i] == v2 ||
                c[i - 1] == v2 && c[i] == v1) {

                vector<int> temp;

                for (auto it = c.begin() + i; it != c.end(); it++)
                    temp.push_back(*it);
                for (auto it = c.begin() + 1; it != c.begin() + i; it++)
                    temp.push_back(*it);


                c = temp;
            }
        }
    }

    if (cycleExist && edgesExist(D))
        cycleExist = false;

    if (!cycleExist)
        cout << "Euler's cycle doesn't exist\n";
    else
        cout << "Euler's cycle exist\n";
}

void topologSort(vector<vector<int>> &Gr, vector<bool> &used, vector<int> &order, int x) {
    used[x] = 1;
    for (int i : Gr[x])
        if (!used[i])
            topologSort(Gr, used, order, i);
    order.push_back(x);
}

// Дан ориентированный граф. Вывести кратчайшие пути до каждой точки
int main() {
    int N, X;
    vector<vector<int>> Gr;
    vector<int> path, order;
    
    cout << "Num of nodes: "; cin >> N;

    vector<bool> used(N, 0);

    Gr = makeAdjList(N);

    printAdjList(Gr);

    
    cout << "\nEuler's path:\n";
    EulersCycle(Gr, path);

    for (auto it = path.begin(); it != path.end(); it++) {
        cout << *it;
        if (it + 1 != path.end())
            cout << " -> ";
    }

    
    cout << "\nTopological sort:\n";
    topologSort(Gr, used, order, 0);
    
    for (auto it = order.rbegin(); it != order.rend(); it++) {
        cout << *it;
        if (it + 1 != order.rend())
            cout << " -> ";
    }

}
