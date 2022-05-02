#include<iostream>

using namespace std;

struct tree {
	int inf;
	tree* right;
	tree* left;
	tree* parent;
};

tree* node(int x) {
	tree* n = new tree;
	n->inf = x;
	n->left = n->right = NULL;
	n->parent = NULL;
	return n;
}

void insert(tree*& tr, int x) {
	tree* n = node(x);
	if (!tr)
		tr = n;
	else {
		tree* y = tr;
		while (y) {
			if (n->inf > y->inf)
				if (y->right)
					y = y->right;
				else {
					n->parent = y;
					y->right = n;
					break;
				}
			else if (n->inf < y->inf)
				if (y->left)
					y = y->left;
				else {
					n->parent = y;
					y->left = n;
					break;
				}
		}
	}
}

void print(tree* tr) {
	if (tr) {
		print(tr->left);
		cout << tr->inf << " ";
		print(tr->right);
	}
}

void task(tree* tr, tree* X) {
	tree* y = tr;
	int n = 0;
	while (y != X) {
		cout << y->inf << " -> ";
		if (X->inf > y->inf)
			y = y->right;
		else
			y = y->left;
	}
	cout << y->inf << endl;
}

tree* find(tree* tr, int x) {
	if (!tr || x == tr->inf)
		return tr;
	if (x < tr->inf)
		return find(tr->left, x);
	else
		return find(tr->right, x);
}

tree* Min(tree* tr) {
	if (!tr->left)
		return tr;
	else
		return Min(tr->left);
}

tree* Max(tree* tr) {
	if (!tr->right)
		return tr;
	else
		return Max(tr->right);
}

int main() {
	int n, X;
	tree* tr = NULL;
	cout << "n: ";  cin >> n;
	cout << "X: "; cin >> X;

	for (int i = 0; i < n; ++i) {
		int t;
		cin >> t;
		insert(tr, t);
	}
	print(tr);
	cout << endl;
	task(tr, find(tr, X));
}