#include<iostream>
#include<list>
#include<algorithm>

using namespace std;

int X;

bool kratnX(int x) { // Проверка на кратность X
	return x % X == 0 && x % 2 == 0;
}

void print(list<int>& a) { // Вывод на экран всех эл-тов списка
	for (list<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << " ";
	cout << endl;
}

int main() {
	setlocale(LC_ALL, "RUS");

	//Данные числа и последовательности
	X = 4;
	int N = 1111;
	list<int> a, b;
	// Заполнение последовательностей
	for (int i = 0; i < 20; ++i) {
		a.push_back(rand() % 14);
		b.push_back(rand() % 14);
	}

	cout << "Дано: " << endl; print(a); print(b);

	// Проход по всем эл-там первого списка, кратных X
	for (list<int>::iterator it = find_if(a.begin(), a.end(), kratnX); it != a.end(); it = find_if(it, a.end(), kratnX)) {
		a.insert(++it, N); // Добавление N после эл-та
	}
	// Удаление всех максимальных эл-тов
	b.remove(*max_element(b.begin(), b.end()));

	cout << "\n1: " << endl; print(a); print(b);

	a.sort(); b.sort();
	cout << "\n2. Sort: " << endl; print(a); print(b);

	a.unique(); b.unique();
	cout << "\n3. Unique: " << endl; print(a); print(b);

	a.merge(b); // Объединение последовательностей в a и сортировкв
	cout << "\n4. Новая отсортированная посл-ть: " << endl; print(a);

}