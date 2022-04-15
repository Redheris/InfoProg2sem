#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

// Структура даты
struct date {
	int day;
	int month;
	int year;
};

// Структура сотрудника
struct employee {
	string surname;
	string post;
	date dateBirth;
	int exp;
	int salary;
};


// Преобразование строки в структуру даты
date makeDate(string& s) {
	date date;
	date.day = atoi(s.substr(0, 2).c_str());
	date.month = atoi(s.substr(3, 2).c_str());
	date.year = atoi(s.substr(6, 4).c_str());

	return date;
}

// Преобразование структуры даты в строку
string dateStr(date& date) {
	return to_string(date.day) + "." + to_string(date.month) + "." + to_string(date.year);
}

// Вывод в файл списка сотрудников
void print(vector<employee> empls, ofstream& out) {
	for(employee empl : empls)
		out << empl.surname + ", " + empl.post + ", " + dateStr(empl.dateBirth) + ", " + to_string(empl.exp) + "," + to_string(empl.salary) << endl;
}

// Преобразование строки в структуру сотрудника
employee emplFromString(string& s) {
	employee empl;
	vector<string> parts;
	int n = 0;
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


// Функция сортировки
void quickSort_bySalary(vector<employee>& staff, int L, int R) {
	// Переменные для границ цикла и значение зарплаты из середины промежутка
	int i = L, j = R, mid = staff[(j + i) / 2].salary;
	
	while (i <= j) {
		// Двигаем левый индекс до элемента не меньшего mid
		while (staff[i].salary < mid)
			i++;
		// Двигаем правый индекс до элемента не больше mid
		while (staff[j].salary > mid)
			j--;
		// Если левый индекс не больше правого
		if (i <= j)
			// поменять местами эелменты и сдвинуть индексы
			swap(staff[i++], staff[j--]);
	}
	// Запуск функции для левой части
	if (i - L > 0)
		quickSort_bySalary(staff, L, j);
	// Запуск функции для правой части
	if (R - j > 0)
		quickSort_bySalary(staff, i, R);
}


int main() {
	setlocale(LC_ALL, "RUS");

	ifstream in("task3_in.txt");
	ofstream out("task3_out.txt");

	// Список сотрудников
	vector<employee> staff;

	// Запись в вектор из файла
	while (in.peek() != EOF) {
		string s;
		getline(in, s);
		staff.push_back(emplFromString(s));
	}
	in.close();

	quickSort_bySalary(staff, 0, staff.size() - 1);

	print(staff, out);
	out.close();

}