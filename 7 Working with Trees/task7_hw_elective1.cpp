#include <iostream>
#include <string>

using namespace std;

// Структура дерева
struct tree
{
    char inf;        // Значение элемента
    tree *right;    // Правый ребёнок
    tree *left;     // Левый ребёнок
    tree *parent;
};

// Создание узла
tree *node(int x) {
    tree *n = new tree;         // Новое дерево
    n->inf = x;                 // Значение
    n->left = n->right = NULL;  // Дети
    n->parent = NULL;
    return n;
}

// Создние дерева
tree *create(string str) {
    tree *tr = NULL;

    for (unsigned int i = 0; i < str.length(); ++i) {
        tree *n = node(str[i]);
        if (str[i] == '-' || str[i] == '+') {
            tr->parent = n;
            n->left = tr;
            tr = n;
        }
        else if (str[i] == '/' || str[i] == '*') {
            if (isdigit(tr->inf)) {
                tr->parent = n;
                n->left = tr;
                tr = n;
            }
            else {
                n->parent = tr;
                n->left = tr->right;
                tr->right->parent = n;
                tr->right = n;
            }
        }
        else {
            if (!tr)
                tr = n;
            else {
                if (!tr->right) {
                    n->parent = tr;
                    n->left = tr->right;
                    tr->right = n;
                }
                else {
                    tree *x = tr->right;
                    while (x->right) x = x->right;
                    n->parent = x->parent;
                    x->right = n;
                }
            }
        }
    }
    return tr;
}

void preorder(tree *tr) {   // Прямой обход
    if (tr) {
        cout << tr->inf;
        preorder(tr->left);
        preorder(tr->right);
    }
}

void postorder(tree *tr) {  //Обратный обход
    if (tr) {
        postorder(tr->left);
        postorder(tr->right);
        cout << tr->inf;
    }
}

int main() {
    tree *tr = NULL;
    string s;

    cin >> s;

    tr = create(s);

    cout << "\nPrefix:\n";
    preorder(tr);

    cout << "\nPostfix:\n";
    postorder(tr);

}