#include <iostream>

using namespace std;

// Структура дерева
struct tree
{
    int inf;        // Значение элемента
    tree *right;    // Правый ребёнок
    tree *left;     // Левый ребёнок
};

// Создание узла
tree *node(int x) {
    tree *n = new tree;         // Новое дерево
    n->inf = x;                 // Значение
    n->left = n->right = NULL;  // Дети
    return n;                   // Родитель
}

// Создать дерево
void create(tree *&tr, int n) {
    int x;

    if (n > 0) {
        cin >> x;               // Значение элемента
        tr = node(x);           // Создание элемента
        int nl = n / 2;         // Кол-во эл-тов в левой ветке
        int nr = n - nl - 1;    // Кол-во эл-тов в правой ветке
        create(tr->left, nl);   // Вызов функции для левого ребёнка
        create(tr->right, nr);  // Вызов функции для правого ребёнка
    }
}

// Прямой обход
void preorder(tree *tr) {
    if (tr) {
        cout << tr->inf << " "; // Вывод значение
        preorder(tr->left);     // Рекурсия для левого ребёнка
        preorder(tr->right);    // Рекурсия для правого ребёнка
    }
}

// Высота левой ветки
int lefth(tree *tr) {
    int k = 0;

    while (tr) {
        k++;
        tr = tr->left;  // Переход на левого ребёнка
    }
    return k - 1;
}

// Высота правой ветки
int righth(tree *tr) {
    int k = 0;

    while (tr) {
        k++;
        tr = tr->right; // Переход на правого ребёнка
    }
    return k - 1;
}

// Вывод листьев
void leafs(tree *tr) {
    if (!tr->left && !tr->right)
        cout << tr->inf << ' ';
    else {
        if (tr->left)
            leafs(tr->left);
        if (tr->right)
            leafs(tr->right);
    }
}

int main() {
    tree *tr = NULL;        // Создание дерева
    int n;
    cout << "n: "; cin >> n;

    create(tr, n);

    cout << "Current tree:\n";
    preorder(tr);

    cout << "Leafs:\n";
    leafs(tr);
}