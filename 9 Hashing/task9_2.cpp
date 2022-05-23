#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

// ��������� ����
struct date
{
    int day;
    int month;
    int year;
};

// ��������� ����������
struct employee
{
    string surname;		// �������
    string post;		// ���������
    date dateBirth;		// ���� ��������
    int exp;			// ����
    int salary;			// ��������
};


// ==== ������� ��� ��������� ��������� � ���� ====

// �������������� ������ � ��������� ����
date makeDate(string &s) {
    date date;
    date.day = atoi(s.substr(0, 2).c_str());
    date.month = atoi(s.substr(3, 2).c_str());
    date.year = atoi(s.substr(6, 4).c_str());

    return date;
}

// �������������� ��������� ���� � ������
string dateStr(date &date) {
    return to_string(date.day) + "." + to_string(date.month) + "." + to_string(date.year);
}

// �������������� ��������� ���������� � ������
string employeeStr(employee empl) {
    return empl.surname + ", " + empl.post + ", " + dateStr(empl.dateBirth)
        + ", " + to_string(empl.exp) + ", " + to_string(empl.salary);
}

// �������������� ������ � ��������� ����������
employee emplFromString(string &s) {
    employee empl;
    vector<string> parts;	// ���������� �� �������� ������

    // n - ������ �����, i - ����� �����
    for (int n = 0, i = s.find(' ', n); i <= string::npos; n = i + 1, i = s.find(' ', n)) {

        if (i == string::npos) { // ��������� �����
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


// ==== ������� ��� ���-������� ====

// �������� ���-�������
void createHashTable(employee *&hashTable, int N, int M) {
    fstream in("task9_in.txt");

    for (int y = 0; y < N; ++y) {
        string s;
        getline(in, s);
        employee empl = emplFromString(s);
        // ��������������� ���-�������
        int k = (int)(M * (empl.exp * 0.618034 - (int)(empl.exp * 0.618034)));
        int j = 0;
        for (int i = 0; i < M; ++i) {
            // �������� ���-�������
            int p = (k + j + 2 * j * j) % M;
            // �������� ������� ��-�� �� �������� �����
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

// ����� ���-�������
void printHashTable(employee *&hashTable, int M) {
    cout << "\nHash table:\n";
    for (int i = 0; i < M; ++i) {		// ������ �� ������� �������
        cout << i << " | ";
        if (hashTable[i].exp == -1)
            cout << "NULL\n";
        else
            cout << employeeStr(hashTable[i]) << endl;
    }
}

employee &find(employee *&hashTable, int M, employee empl) {
    // �������������� ���-�������
    int k = (int)(M * (empl.exp * 0.618034 - (int)(empl.exp * 0.618034)));
    int j = 0;
    for (int i = 0; i < M; ++i) {
        // �������� ���-�������
        int p = (k + j + 2 * j * j) % M;
        if (employeeStr(hashTable[p]) == employeeStr(empl)) {
            cout << "Index: " << p << endl;
            return hashTable[p];
        }
        else
            j++;
    }
}


// �������� �����������.
// �������� ���-������� � ������������ �����������,
// ��������������� � ����� ��������� �� �����
int main() {
    setlocale(LC_ALL, "RUS");
    int N = 20, M = 32;
    employee *hashTable = new employee[M];
    // ���������� ��-��� �������� ��������� �����
    for (int i = 0; i < M; ++i)
        hashTable[i].exp = -1;

    createHashTable(hashTable, N, M);
    printHashTable(hashTable, M);

    string tofind = "������ �������� 08.04.1953 18 32088";
    cout << "\nFind:\n" << tofind << endl;
    
    employee &found = find(hashTable, M, emplFromString(tofind));

    // ������ ������, ��� ��������� �� ������ ������ � ������
    cout << endl << employeeStr(hashTable[7]) << endl;
    found.salary = 130;
    cout << employeeStr(hashTable[7]) << endl;

}