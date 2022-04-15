#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<algorithm>

using namespace std;

// Вывод k эл-тов контейнера с конца
void print(multimap<int, string>& a, int k) {
	int i = 1;
	for (auto it = a.rbegin(); ; it++) {
		cout << it->first << " : " << it->second << endl;
		if (i++ == k)
			return;
	}
}

int main() {
	ifstream in("task2_13-input.txt"); // Чтение

	// Отображение со всеми словами
	map<string, int> words;
	int k;

	cout << "k = "; cin >> k;

	// Запись слов из файла в отображение words
	while (in.peek() != EOF) {
		string c;
		in >> c;
		if (c.find_first_of("0123456789") == string::npos) {
			if (words.find(c) == words.end())
				// Если нет ключа, то добавляем со значением 1
				words.insert(pair<string, int>(c, 1));
			else // Иначе увеличиваем значение на 1
				words.find(c)->second++;
		}
	}
	in.close(); // Закрытие файла

	// Мультиотображение, "отзеркаленное" отображение words для сортировки по значению
	multimap<int, string> max;
	
	// "Отзеркаливание" отображения words в max
	for (auto it = words.begin(); it != words.end(); it++) {
		max.insert(pair<int, string>(it->second, it->first));
	}

	print(max, k);
}