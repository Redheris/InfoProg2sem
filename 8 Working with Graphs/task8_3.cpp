#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

// Вывод списка смежности
void printAdjList(vector<vector<int>> v) {
    cout << "\nCurrent graph:\n";
    for (int i = 0; i < v.size(); ++i) {
        cout << i << " | ";
        for (int j : v[i])
            cout << j << " ";
        cout << endl;
    }
}

vector<vector<int>> makeAdjList(int N) {
    vector<vector<int>> Gr;     // Список смежности
    Gr.resize(N);               // Выделение памяти
    cout << "Edges in the graph (x y):\n";
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

void outDegrees(vector<vector<int>> &Gr) {
    cout << endl;
    for (int i = 0; i < Gr.size(); ++i)
        // Возврващаем длину i-ой строки списка смежности
        cout << i << " | " << Gr[i].size() << endl;;
}

// Дан ориентированный граф. Вывести количество вершин, смежных с данной
int main() {
    int N;
    vector<vector<int>> Gr;
    cout << "Num of nodes: "; cin >> N;

    Gr = makeAdjList(N);

    printAdjList(Gr);

    outDegrees(Gr);
}
