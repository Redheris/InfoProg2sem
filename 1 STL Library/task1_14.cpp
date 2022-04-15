#include<iostream>
#include<list>
#include<algorithm>

using namespace std;

int X;

bool kratnX(int x) { // �������� �� ��������� X
	return x % X == 0 && x % 2 == 0;
}

void print(list<int>& a) { // ����� �� ����� ���� ��-��� ������
	for (list<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << " ";
	cout << endl;
}

int main() {
	setlocale(LC_ALL, "RUS");

	//������ ����� � ������������������
	X = 4;
	int N = 1111;
	list<int> a, b;
	// ���������� �������������������
	for (int i = 0; i < 20; ++i) {
		a.push_back(rand() % 14);
		b.push_back(rand() % 14);
	}

	cout << "����: " << endl; print(a); print(b);

	// ������ �� ���� ��-��� ������� ������, ������� X
	for (list<int>::iterator it = find_if(a.begin(), a.end(), kratnX); it != a.end(); it = find_if(it, a.end(), kratnX)) {
		a.insert(++it, N); // ���������� N ����� ��-��
	}
	// �������� ���� ������������ ��-���
	b.remove(*max_element(b.begin(), b.end()));

	cout << "\n1: " << endl; print(a); print(b);

	a.sort(); b.sort();
	cout << "\n2. Sort: " << endl; print(a); print(b);

	a.unique(); b.unique();
	cout << "\n3. Unique: " << endl; print(a); print(b);

	a.merge(b); // ����������� ������������������� � a � ����������
	cout << "\n4. ����� ��������������� ����-��: " << endl; print(a);

}