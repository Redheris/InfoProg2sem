#include<iostream>

using namespace std;

// Структура дерева
struct tree
{
	int inf;		// Значение
	tree *right;	// Правый ребёнок
	tree *left;		// Левый ребёнок
	tree *parent;	// Родитель
};

// Создание узла
tree *node(int x) {
	tree *n = new tree;			// Новое дерево
	n->inf = x;					// Значение
	n->left = n->right = NULL;	// Дети
	n->parent = NULL;			// Родитель
	return n;
}

// Добавление нового элемента в дерево
void insert(tree *&tr, int x) {
	tree *n = node(x);					// Новый элемент
	if (!tr)							// Дерево пустое
		tr = n;
	else {
		tree *y = tr;					// Указатель на корень
		while (y) {
			if (n->inf < y->inf)		// Новый элемент меньше корня
				if (y->left)			// Есть левый ребёнок
					y = y->left;		// Переходим на него
				else {
					n->parent = y;		// Новый элемент - левый ребёнок корня
					y->left = n;
					break;
				}
			else						// Новый элемент не меньше корня
				if (y->right)			// Есть правый ребёнок
					y = y->right;		// Переходим на него
				else {
					n->parent = y;		// Новый элемент - правый ребёнок корня
					y->right = n;
					break;
				}

		}
	}
}

// Вывод симметричным обходом
void inorder(tree *tr) {
	if (tr) {
		inorder(tr->left);		// Рекурсия для левого поддерева
		cout << tr->inf << " ";	// Вывод корня
		inorder(tr->right);		// Рекурсия для правого поддерева
	}
}

// Задание
void task(tree *tr, tree *X) {
	tree *y = tr;					// Указатель на корень
	int n = 0;
	while (y != X) {
		cout << y->inf << " -> ";	// Вывод шага пути
		if (X->inf < y->inf)		// X меньше корня - идём влево
			y = y->left;
		else
			y = y->right;
	}
	cout << y->inf << endl;			// Элемент X, конец пути
}

// Поиск элемента по значению
tree *find(tree *tr, int x) {
	if (!tr || x == tr->inf)
		return tr;
	if (x < tr->inf)				// X меньше корня - идём влево
		return find(tr->left, x);
	else
		return find(tr->right, x);
}

int main() {
	int n, X;						// Кол-во элементов и находимый элемент
	tree *tr = NULL;				// Создание дерева
	cout << "n: ";  cin >> n;
	cout << "X: "; cin >> X;

	for (int i = 0; i < n; ++i) {
		int t;
		cin >> t;
		insert(tr, t);
	}
	inorder(tr);
	cout << endl;
	task(tr, find(tr, X));
}