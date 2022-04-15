#include<iostream>

using namespace std;

// Структура стека
struct stack {
	int inf; // Значение элемента
	stack* next; // Ссылка на следующий элемент
};

// Добавление в стек
void push(stack*& h, int x) {
	stack* r = new stack; // Создание нового элемента
	r->inf = x;
	r->next = h;
	h = r; // Пермещение головы на новый элемент
}

// Удаление из стека
int pop(stack*& h) {
	int i = h->inf; // Значение элемента
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
void task(stack*& h, int min, int elem) {
	stack* r = NULL; // Новый стек
	while (h) {
		// Удаление элемента из исходного стека и сохранение его значения
		int i = pop(h);
		// Добавление в новый стек
		push(r, i);
		if (i == min) // Если минимальный, 
			push(r, elem);
	}
	h = r;
}

int main() {
	// Кол-во элементов, миним. эл-т, новый элемент
	int n, min = 99999, elem;
	cout << "n: "; cin >> n;
	cout << "new: "; cin >> elem;
	stack* task2 = NULL;

	// Заполнение стека
	for (int i = 0; i < n; ++i) {
		int t;
		cin >> t;

		if (t < min)
			min = t;

		push(task2, t);
	}

	task(task2, min, elem);
	print(task2);

}