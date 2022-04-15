#include<iostream>

using namespace std;

// Структура стека
struct stack {
	string inf; // Значение элемента
	stack* next; // Ссылка на следующий элемент
};

// Добавление в стек
void push(stack*& h, string x) {
	stack* r = new stack; // Создание нового элемента
	r->inf = x;
	r->next = h;
	h = r; // Пермещение головы на новый элемент
}

// Удаление из стека
string pop(stack*& h) {
	string i = h->inf; // Значение элемента
	stack* r = h; // Голова стека
	h = h->next; // Перемещение головы на следующий элемент
	delete r; // Удаление
	return i;
}

// Вывод стека
void print(stack*& h) {
	stack* r = h; // Указатель на голову
	while (r) {
		cout << r->inf << " ";
		r = r->next; // Переход к след. элементу
	}
	cout << endl;
}

// Задание
void task(stack*& h, char ch) {
	stack* r = NULL; // Новый стек
	while (h) {
		// Удаление элемента из исходного стека и сохранение его значения
		string word = pop(h);
		if (word[word.size() - 1] != ch) // Проверка последней буквы
			push(r, word); // Добавление в новый стек
	}
	h = r; // Замена исходного стека новым
}

int main() {
	int n; // Кол-во элементов
	char ch;
	cout << "n: "; cin >> n;
	cout << "char: "; cin >> ch;

	stack* task1 = NULL;

	// Заплонение стека
	for (int i = 0; i < n; ++i) {
		string t;
		cin >> t;
		push(task1, t);
	}
	task(task1, ch);
	print(task1);
	
}