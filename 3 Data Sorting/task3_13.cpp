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
	for (employee empl : empls)
		out << empl.surname + ", " + empl.post + ", " + dateStr(empl.dateBirth) + ", " + to_string(empl.exp) + ", " + to_string(empl.salary) << endl;
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


// Функция для сортировки перемешиванием
void coctailSort(vector<employee>& staff) {
	int begin = -1, end = staff.size() - 1;
	// Возможны ли обмены
	bool flag = true;

	while (flag) {
		flag = false;
		begin++;
		for (int j = begin; j < end; ++j) {
			// Проверка на несортированные по году-месяцу-дню элементы
			if (staff[j].dateBirth.year > staff[j + 1].dateBirth.year || // По году
				(staff[j].dateBirth.year == staff[j + 1].dateBirth.year && staff[j].dateBirth.month > staff[j + 1].dateBirth.month) || // По месяцу
				(staff[j].dateBirth.year == staff[j + 1].dateBirth.year && staff[j].dateBirth.month == staff[j + 1].dateBirth.month && staff[j].dateBirth.day > staff[j + 1].dateBirth.day)) { // По дню

				swap(staff[j], staff[j + 1]);
				flag = true;
			}
		}

		if (!flag)
			return;

		flag = false;
		end--;

		for (int j = end; j >= begin; --j) {
			// Проверка на несортированные по году-месяцу-дню элементы
			if (staff[j].dateBirth.year > staff[j + 1].dateBirth.year || // По году
				(staff[j].dateBirth.year == staff[j + 1].dateBirth.year && staff[j].dateBirth.month > staff[j + 1].dateBirth.month) || // По месяцу
				(staff[j].dateBirth.year == staff[j + 1].dateBirth.year && staff[j].dateBirth.month == staff[j + 1].dateBirth.month && staff[j].dateBirth.day > staff[j + 1].dateBirth.day)) { // По дню

				swap(staff[j], staff[j + 1]);
				flag = true;
			}
		}
	}
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

	// Вызов сортировки
	coctailSort(staff);

	print(staff, out);
	out.close();
}