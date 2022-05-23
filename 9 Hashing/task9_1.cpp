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

// ���� ����������� ������
struct node
{
	employee inf;
	node *prev;
	node *next;
};

// ���������� ������
struct list
{
	node *head = NULL;
	node *tail = NULL;
};


// ==== ������� ��� ������ ====

// ���������� � ����� ������
void push(list &empl, employee x) {
	node *r = new node; // �������� ������ ��������
	r->inf = x;
	r->next = NULL;
	r->prev = empl.tail;
	if (!empl.head && !empl.tail) // ������ �������
		empl.head = r;
	else
		empl.tail->next = r;
	empl.tail = r; // ����������� ������ �� ����� �������
}

// �������� �� ������
void del_node(list &empl, node *x) {
	if (empl.head == empl.tail) {		// ��������� ������
		empl.head = empl.tail = NULL;
	}
	else if (empl.head == x) {			// �������� ������
		empl.head = empl.head->next;
		empl.head->prev = NULL;
	}
	else if (empl.tail == x) {			// �������� ������
		empl.tail = empl.tail->prev;
		empl.tail->next = NULL;
	}
	else {								// �������� �� �������� ������
		x->prev->next = x->next;
		x->next->prev = x->prev;
	}

	delete x;
}


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
void createHashTable(list *&A, int N, int M) {
	fstream in("task9_in.txt");
	for (int i = 0; i < N; ++i) {
		string s;
		getline(in, s);
		employee x = emplFromString(s);
		int k = x.dateBirth.day % M;		// �������� ���-�������
		push(A[k], x);						// ���������� � ���-�������
	}
	in.close();
}

// ����� ���-�������
void printHashTable(list *&hashTable, int M) {
	cout << "\nHash table:\n";
	for (int i = 0; i < M; ++i) {		// ������ �� ������� �������

		for (int j = 0; j < 30; ++j) {	// ��������� ���������� ����� ������
			cout << "--";
			if (j == 14) cout << i;
		}
		cout << endl << endl;

		node *r = hashTable[i].head;	// ��������� �� ������ ������ ������
		while (r) {						// ������ �� ��-��� ������
			cout << "\t" << employeeStr(r->inf) << endl;
			r = r->next;
		}

		cout << endl;
	}
}

// ����� � �������� �������� � ���-�������
void findNDel(list *&hashTable, int M, employee x) {
	int k = x.dateBirth.day % M;	// �������� ���-�������
	node *r = hashTable[k].head;	// ��������� �� ������
	string str = employeeStr(x);	// �������������� � ������ ��� ���������
	while (r) {
		if (employeeStr(r->inf) == str)
			return del_node(hashTable[k], r);
		r = r->next;
	}
}

// �������� ���-������� ������� �������� �� ��� ��������
int main() {
	setlocale(LC_ALL, "RUS");
	int N = 20, M, a;

	cout << "a: "; cin >> a;
	M = N / a;
	list *A = new list[M];

	createHashTable(A, N, M);
	printHashTable(A, M);

	string find = "������ �������� 08.04.1953 18 32088";
	cout << "\nFind:\n" << find << endl;
	findNDel(A, M, emplFromString(find));

	printHashTable(A, M);
}
