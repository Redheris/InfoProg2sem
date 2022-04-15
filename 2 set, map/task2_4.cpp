#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

// ���������� ��
bool is2digit(int x) {
	return x >= 10 && x < 100;
}
// ���������� ��
bool is3digit(int x) {
	return x >= 100 && x < 1000;
}

// ���������� � ��-�� ���� �����
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
	// ��-�� ��� ���� 2-� � 3-�������� �����
	set<int> a,b;

	int n;
	cout << "����� ����-��: "; cin >> n;
	cout << "��-�� ����-��:" << endl;

	// ������ � ��-��
	for (int i = 0; i < n; ++i) {
		int c;
		cin >> c;
		if (is2digit(c)) // ���� 2-�������� � a
			splitNum(a, c);
		else if (is3digit(c)) // ���� 3-�������� � b
			splitNum(b, c);
	}

	// ����� ����, ������������� � � 2-�, � � 3-�������� ������
	for (set<int>::iterator it = a.begin(); it != a.end(); it++) {
		if (b.find(*it) != b.end())
			cout << *it << " ";
	}
}