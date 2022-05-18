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
        Gr[y].push_back(x);
    }
    // Сортировка и удаление дубликатов для каждой строки списка
    for (auto &i : Gr) {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
    }
    return Gr;
}

void addEdge(vector<vector<int>> &Gr, int A, int B) {
    // Если они не являются уже смежные
    if (find(Gr[A].begin(), Gr[A].end(), B) == Gr[A].end()) {
        Gr[A].push_back(B);                 // Добавление в смежные вершины
        sort(Gr[A].begin(), Gr[A].end());   // Сортировка вершин в строке

        Gr[B].push_back(A);
        sort(Gr[B].begin(), Gr[B].end());
    }
}

// Дан неориентированный граф. Вставить в граф ребро, соединяющее вершины A и B
int main() {
    int N, A, B;
    vector<vector<int>> Gr;
    cout << "Num of nodes: "; cin >> N;

    Gr = makeAdjList(N);

    printAdjList(Gr);

    cout << "\nA, B:\n"; cin >> A >> B;
    addEdge(Gr, A, B);

    printAdjList(Gr);
}
