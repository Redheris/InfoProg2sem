#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<list>
#include<set>

using namespace std;

template <typename T, typename Iter>
// Вывод на экран всех эл-тов контейнера
// Input: сам контейнер и его итератор begin()
void print(T& a, Iter it) {
	for (; it != a.end(); it++)
		cout << *it << " ";

	cout << endl;
}

int t;
bool larger(int x) {
	return x > t;
}


void task_1(vector<int>& a) {
	cout << "1.\nInitial vector: "; print(a, a.begin());

	// Сохранение 5-го эл-та и значения начального размера вектора
	t = a[5];
	int size = a.size();

	// Сдвиг эл-тов, равных 5-му, в конец вектора
	for (int i = 0; i < count(a.begin(), a.end(), t); ++i) {
		a.push_back(*find(a.begin(), a.end(), t)); // Добавление копии в конец
		a.erase(find(a.begin(), a.end(), t)); // Удаление эл-та
	}

	// Сдвиг эл-тов, больших t, в конец вектора
	for (int i = 0; i < count_if(a.begin(), a.end(), larger); ++i) {
		a.push_back(*find_if(a.begin(), a.end(), larger)); // Добавление копии в конец
		a.erase(find_if(a.begin(), a.end(), larger)); // Удаление эл-та
	}
	
	cout << "Changed vector: "; print(a, a.begin());
}
 
void task_2(list<int>& a) {
	cout << "2.\nInitial list: "; print(a, a.begin());
	
	// Сдвиг первого максимального эл-та в начало
	a.insert(a.begin(), *max_element(a.begin(), a.end()));
	a.erase(max_element(++a.begin(), a.end()));
	
	// Сдвиг остальных эл-тов
	rotate(++a.begin(), --a.end(), a.end());
	/*a.insert(++a.begin(), *--a.end());
	a.erase(--a.end());*/

	cout << "Changed list: "; print(a, a.begin());
}

void task_3(vector<int>& a) {
	cout << "3.\nInitial vector: "; print(a, a.begin());

	// Преобразование в кучу
	make_heap(a.begin(), a.end());

	cout << "Changed vector: "; print(a, a.begin());
}

void task_4(list<int>& a, list<int>& b) {
	cout << "3.\nInitial lists:\n"; print(a, a.begin()); print(b, b.begin());

	cout << "Scalar product: " << inner_product(a.begin(), a.end(), b.begin(), 0);
}

void task_5(char s[]) {
	set<char> a;

	cout << "\n4.\nInitial string: ";
	for (int i = 0; i < 20; ++i) { // Вывод данной строки и запись эл-тов в множество
		cout << s[i] << " ";
		a.insert(s[i]);
	}

	cout << "\nSet: "; print(a, a.begin());
	// Количество различных букв в слове есть размер получившегося множества
	cout << "Num of diff letters: " << a.size() << endl;
}


int main() {
	vector<int> t1 = { 1, 3, 12, 76, 2, 24, 100, 76, 24, 5 };
	task_1(t1);
	
	list<int> t2 = { 1, 3, 12, 76, 2, 24, 100, 76, 24, 5 };
	task_2(t2);

	vector<int> t3 = { 1, 3, 12, 76, 2, 24, 100, 76, 24, 5 };
	task_3(t3);

	list<int> a4 = { 1, 3, 12, 76, 2, 24, 100, 76, 24, 5 };
	list<int> b4 = { 8, 39, 80, 99, 94, 50, 12, 93, 15, 80 };
	task_4(a4, b4);

	char s[20] = "qaebsybzzagstqqxhsx";
	task_5(s);
}