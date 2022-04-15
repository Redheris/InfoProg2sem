#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

bool odd(int x) {
	return x % 2 == 0;
}

void print(list<int>& a) { // ����� �� ����� ���� ��������� ������
	for (list<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << " ";
	cout << endl;
}

int main() {
	// ������ �����
	int x = 1111;
	// ������ ������������������
	list<int> a = {1, 54, 12, 13, 0, 0, 12, 54, 50, 6, 7, 19, 54, 54, 19, 1};

	cout << "Container: ";  print(a);
	int max = *max_element(a.begin(), a.end());

	a.remove(max); // �������� ������������ ��-���
	cout << "1. Delete Max(" << max << "): ";  print(a);

	// ������ �� ������ ��������� ������������������
	for (list<int>::iterator it = find_if(a.begin(), a.end(), odd); it != a.end(); it = find_if(it, a.end(), odd)) { 
		a.insert(++it, x); // ���������� X ����� ��-��
	}
	cout << "2. New elems: ";  print(a);

	a.sort();
	cout << "3. Sort: "; print(a);

	a.erase(unique(a.begin(), a.end()), a.end()); // �������� ����������
	cout << "4. Unique: "; print(a);
}