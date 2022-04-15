#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

// Двузначное ли
bool is2digit(int x) {
	return x >= 10 && x < 100;
}
// Трёхзначное ли
bool is3digit(int x) {
	return x >= 100 && x < 1000;
}

// Добавление в мн-во цифр числа
void splitNum(set<int>& a, int x) {
	if (is2digit(x)) {
		a.insert(x % 10);
		a.insert(x / 10);
	}
	else {
		a.insert(x % 10);
		a.insert(x % 100 / 10);
		a.insert(x / 100);
	}
}


int main() {
	setlocale(LC_ALL, "RUS");
	// Мн-ва для цифр 2-х и 3-хзначных чисел
	set<int> a,b;

	int n;
	cout << "Длина посл-ти: "; cin >> n;
	cout << "Эл-ты посл-ти:" << endl;

	// Запись в мн-ва
	for (int i = 0; i < n; ++i) {
		int c;
		cin >> c;
		if (is2digit(c)) // Цифр 2-хзначных в a
			splitNum(a, c);
		else if (is3digit(c)) // Цифр 3-хзначных в b
			splitNum(b, c);
	}

	// Вывод цифр, встречающихся и в 2-х, и в 3-хзначных числах
	for (set<int>::iterator it = a.begin(); it != a.end(); it++) {
		if (b.find(*it) != b.end())
			cout << *it << " ";
	}
}