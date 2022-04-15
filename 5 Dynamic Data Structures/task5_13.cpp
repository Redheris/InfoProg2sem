#include<iostream>

using namespace std;

// Структура очереди
struct queue {
	int inf; // Значения элемента
	queue* next; // Ссылка на следующий элемент
};

// Запись в очередь
void push(queue*& h, queue*& t, int x) {
	queue* r = new queue; // Создание нового элемента
	r->inf = x;
	r->next = NULL;
	if (!h && !t) // Если очередь пустая
		h = t = r;
	else {
		t->next = r; // Добавление в хвост ссылки на новый элемент
		t = r; // Перемещение хвоста на новый элемент
	}
}

// Удаление из очереди
int pop(queue*& h, queue*& t) {
	queue* r = h; // Ссылка на голову
	int i = h->inf; // Значение элемента
	h = h->next; // Перемещение головы
	if (!h) // Очередь опустела
		t = NULL;
	delete r; // Удаление
	return i;
}

// Вывод очереди
void print(queue*& h, queue*& t) {
	queue* rh = h; // Указатель на голову
	while (rh) {
		cout << rh->inf << " ";
		rh = rh->next; // Переход к след. элементу
	}
	cout << endl;
}

// Задание
void task(queue*& h, queue*& t, int X, int elem) {
	queue* rh = NULL, *rt = NULL; // Голова и хвост новой очереди
	while (h) {
		// Удаление элемента из исходной очереди и сохранение его значения
		int i = pop(h, t);
		push(rh, rt, i); // Добавление элемента в новую очередь
		if (i % X == 0) // Проверка кратности
			push(rh, rt, elem); // Добавление нового элемента
	}
	// Замена исходной очереди на новую
	h = rh;
	t = rt;
}


int main() {
	int n, X, elem;

	cout << "n, X, new: "; cin >> n >> X >> elem;

	queue* head = NULL, * tail = NULL;

	// Заполнение очереди
	for (int i = 0; i < n; ++i) {
		int t;
		cin >> t;
		push(head, tail, t);;
	}

	task(head, tail, X, elem);
	print(head, tail);
	
}