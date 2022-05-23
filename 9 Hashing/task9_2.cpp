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
void createHashTable(employee *&hashTable, int N, int M) {
    fstream in("task9_in.txt");

    for (int y = 0; y < N; ++y) {
        string s;
        getline(in, s);
        employee empl = emplFromString(s);
        // Вспомогательная хеш-функция
        int k = (int)(M * (empl.exp * 0.618034 - (int)(empl.exp * 0.618034)));
        int j = 0;
        for (int i = 0; i < M; ++i) {
            // Основная хеш-функция
            int p = (k + j + 2 * j * j) % M;
            // Проверка наличия эл-та по значению стажу
            if (hashTable[p].exp == -1) {
                hashTable[p] = empl;
                break;
            }
            else
                j++;
        }
    }
    in.close();
}

// Вывод хеш-таблицы
void printHashTable(employee *&hashTable, int M) {
    cout << "\nHash table:\n";
    for (int i = 0; i < M; ++i) {		// Проход по строкам таблицы
        cout << i << " | ";
        if (hashTable[i].exp == -1)
            cout << "NULL\n";
        else
            cout << employeeStr(hashTable[i]) << endl;
    }
}

employee &find(employee *&hashTable, int M, employee empl) {
    // Дополнительная хеш-функция
    int k = (int)(M * (empl.exp * 0.618034 - (int)(empl.exp * 0.618034)));
    int j = 0;
    for (int i = 0; i < M; ++i) {
        // Основная хеш-функция
        int p = (k + j + 2 * j * j) % M;
        if (employeeStr(hashTable[p]) == employeeStr(empl)) {
            cout << "Index: " << p << endl;
            return hashTable[p];
        }
        else
            j++;
    }
}


// Закрытое хеширование.
// Основная хеш-функция — квадратичное хеширование,
// вспомогательная — метод умножения по стажу
int main() {
    setlocale(LC_ALL, "RUS");
    int N = 20, M = 32;
    employee *hashTable = new employee[M];
    // Заполнение эл-тов ключевым значением стажа
    for (int i = 0; i < M; ++i)
        hashTable[i].exp = -1;

    createHashTable(hashTable, N, M);
    printHashTable(hashTable, M);

    string tofind = "Иванов Менеджер 08.04.1953 18 32088";
    cout << "\nFind:\n" << tofind << endl;
    
    employee &found = find(hashTable, M, emplFromString(tofind));

    // Просто пример, что находится не просто индекс в списке
    cout << endl << employeeStr(hashTable[7]) << endl;
    found.salary = 130;
    cout << employeeStr(hashTable[7]) << endl;

}