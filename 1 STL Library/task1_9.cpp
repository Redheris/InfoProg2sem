#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

bool odd(int x) {
	return x % 2 == 0;
}

void print(list<int>& a) { // Вывод на экран всех элементов списка
	for (list<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << " ";
	cout << endl;
}

int main() {
	// Данное число
	int x = 1111;
	// Данная последовательность
	list<int> a = {1, 54, 12, 13, 0, 0, 12, 54, 50, 6, 7, 19, 54, 54, 19, 1};

	cout << "Container: ";  print(a);
	int max = *max_element(a.begin(), a.end());

	a.remove(max); // Удаление максимлаьных эл-тов
	cout << "1. Delete Max(" << max << "): ";  print(a);

	// Проход по чётным элементам последовательности
	for (list<int>::iterator it = find_if(a.begin(), a.end(), odd); it != a.end(); it = find_if(it, a.end(), odd)) { 
		a.insert(++it, x); // Добавление X после эл-та
	}
	cout << "2. New elems: ";  print(a);

	a.sort();
	cout << "3. Sort: "; print(a);

	a.erase(unique(a.begin(), a.end()), a.end()); // Удаление дубликатов
	cout << "4. Unique: "; print(a);
}