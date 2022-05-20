#include<iostream>
#include<vector>
#include<queue>
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

    bool flag = false;
    cout << "Oriented graph? (1/0) "; cin >> flag;

    cout << "Edges in the graph (x y) (0 0 to stop):\n";
    int x = -1, y = -1;
    // Пока пользователь не введёт "0 0"
    while (cin >> x >> y) {
        // Выход из цикла
        if (x == 0 && y == 0)
            break;
        // Ограничения для входных данных
        if (x > N || y > N || x == y)
            continue;

        Gr[x].push_back(y);
        if (!flag)
            Gr[y].push_back(x);
    }
    // Сортировка и удаление дубликатов для каждой строки списка
    for (auto &i : Gr) {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
    }
    return Gr;
}

// Обход в глубину
void widthBypass(vector<vector<int>> &Gr, int x = 0) {
    vector<int> path;
    vector<bool> used(Gr.size());
    queue<int> que;
    
    used[x] = 1;        // Помечаем вершину x посещённой
    path.push_back(x);
    que.push(x);

    while (!que.empty()) {
        int y = que.front();
        que.pop();
        for (int i = 0; i < Gr[y].size(); ++i) {
            if (!used[Gr[y][i]]) {
                used[Gr[y][i]] = true;    // Помечаем вершину x посещённой
                path.push_back(Gr[y][i]);
                que.push(Gr[y][i]);
            }
        }
    }

    for (int i : path)
        cout << i << " ";

    cout << endl;
}

// Нерекурсивный обход в глубину
void depthBypass(vector<vector<int>> &Gr, int x = 0) {
    vector<bool> used(Gr.size());
    stack<int> stack;
    stack.push(x);

    while (!stack.empty()) {
        int y = stack.top();
        stack.pop();
        
        if (used[y])
            continue;
        used[y] = true;
        
        cout << y << " ";

        // Проход с конца списка смежности для вершины
        for (auto it = Gr[y].rbegin(); it != Gr[y].rend(); it++) {
            int u = *it;
            // Запись в стек непосещённых вершин
            if (!used[u])
                stack.push(u);
        }

    }

    cout << endl;
}

int main() {
    int N;
    vector<vector<int>> Gr;
    cout << "Num of nodes: "; cin >> N;


    Gr = makeAdjList(N);

    printAdjList(Gr);

    cout << "\nWidth bypass:\n";
    widthBypass(Gr);

    cout << "\nDepth bypass:\n";
    depthBypass(Gr);
}