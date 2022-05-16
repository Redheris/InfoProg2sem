#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

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
    for (auto i : Gr) {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
    }
    return Gr;
}

int getAdjsNodesNum(vector<vector<int>> Gr, int n) {
    int k = Gr[n].size(); // Длина списка смежности вершины
    for (int i = 0; i < Gr.size(); ++i) {
        for (int j : Gr[i])
            if (j == n) {
                // Если вершины i нет в списке смежных n
                if (find(Gr[n].begin(), Gr[n].end(), i) == Gr[n].end())
                    k++;
                break; // Переход к след. вершине
            }
    }
    return k;
}

// Дан ориентированный граф. Вывести количество вершин, смежных с данной
int main() {
    int N, X;
    vector<vector<int>> Gr;
    cout << "Num of nodes: "; cin >> N;

    Gr = makeAdjList(N);

    cout << "Node X: "; cin >> X;

    cout << "Num of nodes adjacent to X: " << getAdjsNodesNum(Gr, X) << endl;
}