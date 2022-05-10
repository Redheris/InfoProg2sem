#include <iostream>
#include <queue>

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

// Сумма узлав на k-ом уровне
// curk - данный уровень, s - сумма узлов
void nodes_sum(tree *tr, int &k, int curk, int &s) {
   if (curk == k)
       s += tr->inf;
   else if (curk < k) {
       if (tr->left)
           nodes_sum(tr->left, k, curk + 1, s);
       if (tr->right)
           nodes_sum(tr->right, k, curk + 1, s);
   }
}

int main() {
   tree* tr = NULL;
   int n, k, s = 0;
   cout << "n: "; cin >> n;     // Кол-во элементов
   cout << "k: "; cin >> k;     // Уровень k

   create(tr, n);

   cout << "Current tree:\n";
   preorder(tr);

   nodes_sum(tr, k, 0, s);

   cout << "Sum of nodes at level k: " << s << endl;
}