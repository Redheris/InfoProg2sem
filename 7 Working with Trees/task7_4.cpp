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
int task(tree *tr, int &num) {
	if (tr) {
		task(tr->left, num);		// Рекурсия для левого поддерева
		if (!tr->left && tr->right)
			num++;
		task(tr->right, num);		// Рекурсия для правого поддерева
	}
	else
		return num;
}

int main() {
	int n, num = 0;						// Кол-во элементов
	tree *tr = NULL;					// Создание дерева
	cout << "n: ";  cin >> n;

	for (int i = 0; i < n; ++i) {		// Заполнение дерева
		int t;
		cin >> t;
		insert(tr, t);
	}
	inorder(tr);						// Вывод дерева
	cout << endl << task(tr, num) << endl;
}