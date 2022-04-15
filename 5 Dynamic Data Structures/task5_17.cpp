#include<iostream>
#include<vector>

using namespace std;

// Структура очереди
struct queue {
	string inf; // Значения элемента
	queue* next; // Ссылка на следующий элемент
};

// Запись в очередь
void push(queue*& h, queue*& t, string x) {
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
string pop(queue*& h, queue*& t) {
	queue* r = h; // Ссылка на голову
	string i = h->inf; // Значение элемента
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
void task(queue*& h, queue*& t) {
	queue* rh = NULL, * rt = NULL; // Голова и хвост новой очереди
	vector<string> words; // Вектор для слов
	while (h) {
		// Удаление элемента из исходной очереди и сохранение его значения
		string s = pop(h, t);

		// Если слово не встречалось ранее
		if (find(words.begin(), words.end(), s) == words.end()) {
			push(rh, rt, s); // Добавление в новую очередь
			words.push_back(s); // Добавление в вектор длля првоерки
		}
	}
	// Замена исходной очереди на новую
	h = rh;
	t = rt;
}

int main() {
	int n;
	queue* head = NULL, * tail = NULL;

	cout << "n: "; cin >> n;

	// Заполнение очереди
	for (int i = 0; i < n; ++i) {
		string t;
		cin >> t;
		push(head, tail, t);
	}

	task(head, tail);
	print(head, tail);
}