#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

// Структура даты
struct date
{
	int day;
	int month;
	int year;
};

// Структура сотрудника
struct employee
{
	string surname;		// Фамилия
	string post;		// Должность
	date dateBirth;		// Дата рождения
	int exp;			// Стаж
	int salary;			// Зарплата
};

// Узел двусвязного списка
struct node
{
	employee inf;
	node *prev;
	node *next;
};

// Двусвязный список
struct list
{
	node *head = NULL;
	node *tail = NULL;
};


// ==== Функции для списка ====

// Добавление в конец списка
void push(list &empl, employee x) {
	node *r = new node; // Создание нового элемента
	r->inf = x;
	r->next = NULL;
	r->prev = empl.tail;
	if (!empl.head && !empl.tail) // Первый элемент
		empl.head = r;
	else
		empl.tail->next = r;
	empl.tail = r; // Перемещение хвоста на новый элемент
}

// Удаление из списка
void del_node(list &empl, node *x) {
	if (empl.head == empl.tail) {		// Единичный список
		empl.head = empl.tail = NULL;
	}
	else if (empl.head == x) {			// Удаление головы
		empl.head = empl.head->next;
		empl.head->prev = NULL;
	}
	else if (empl.tail == x) {			// Удаление хвоста
		empl.tail = empl.tail->prev;
		empl.tail->next = NULL;
	}
	else {								// Удаление из середины списка
		x->prev->next = x->next;
		x->next->prev = x->prev;
	}

	delete x;
}


// ==== Функции для структуры работника и даты ====

// Преобразование строки в структуру даты
date makeDate(string &s) {
	date date;
	date.day = atoi(s.substr(0, 2).c_str());
	date.month = atoi(s.substr(3, 2).c_str());
	date.year = atoi(s.substr(6, 4).c_str());

	return date;
}

// Преобразование структуры даты в строку
string dateStr(date &date) {
	return to_string(date.day) + "." + to_string(date.month) + "." + to_string(date.year);
}

// Преобразование структуры сотрудника в строку
string employeeStr(employee empl) {
	return empl.surname + ", " + empl.post + ", " + dateStr(empl.dateBirth)
		+ ", " + to_string(empl.exp) + ", " + to_string(empl.salary);
}

// Преобразование строки в структуру сотрудника
employee emplFromString(string &s) {
	employee empl;
	vector<string> parts;	// Разделённая по пробелам строка

	// n - начало слова, i - конец слова
	for (int n = 0, i = s.find(' ', n); i <= string::npos; n = i + 1, i = s.find(' ', n)) {

		if (i == string::npos) { // Последнее слово
			parts.push_back(s.substr(n, s.size() - n));
			break;
		}
		else {
			parts.push_back(s.substr(n, i - n));
		}
	}

	empl.surname = parts[0];
	empl.post = parts[1];
	empl.dateBirth = makeDate(parts[2]);
	empl.exp = atoi(parts[3].c_str());
	empl.salary = atoi(parts[4].c_str());

	return empl;

}


// ==== Функции для хеш-таблицы ====

// Создание хеш-таблицы
void createHashTable(list *&A, int N, int M) {
	fstream in("task9_in.txt");
	for (int i = 0; i < N; ++i) {
		string s;
		getline(in, s);
		employee x = emplFromString(s);
		int k = x.dateBirth.day % M;		// Значение хеш-функции
		push(A[k], x);						// Добавление в хеш-таблицу
	}
	in.close();
}

// Вывод хеш-таблицы
void printHashTable(list *&hashTable, int M) {
	cout << "\nHash table:\n";
	for (int i = 0; i < M; ++i) {		// Проход по строкам таблицы

		for (int j = 0; j < 30; ++j) {	// Визуально выделенный номер строки
			cout << "--";
			if (j == 14) cout << i;
		}
		cout << endl << endl;

		node *r = hashTable[i].head;	// Указатель на голову списка строки
		while (r) {						// Проход по эл-там списка
			cout << "\t" << employeeStr(r->inf) << endl;
			r = r->next;
		}

		cout << endl;
	}
}

// Поиск и удаление элемента в хеш-таблице
void findNDel(list *&hashTable, int M, employee x) {
	int k = x.dateBirth.day % M;	// Значения хеш-функции
	node *r = hashTable[k].head;	// Указатель на голову
	string str = employeeStr(x);	// Преобразование в строку для сравнения
	while (r) {
		if (employeeStr(r->inf) == str)
			return del_node(hashTable[k], r);
		r = r->next;
	}
}

// Открытая хеш-таблица методом делителя по дню рождения
int main() {
	setlocale(LC_ALL, "RUS");
	int N = 20, M, a;

	cout << "a: "; cin >> a;
	M = N / a;
	list *A = new list[M];

	createHashTable(A, N, M);
	printHashTable(A, M);

	string find = "Иванов Менеджер 08.04.1953 18 32088";
	cout << "\nFind:\n" << find << endl;
	findNDel(A, M, emplFromString(find));

	printHashTable(A, M);
}
