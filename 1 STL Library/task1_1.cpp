#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int a, b;

bool incl(int x) {
	return a <= x && x <= b;
}

int main() {
	// ������� �������
	a = 1;
	b = 10;
	// ������ ������������������
	vector<int> a = {11, 3, 20, 4, 3, 5, 65, 15, 20, 100, 240};

	replace_if(a.begin(), a.end(), incl, 0); // ������ �� ���� ���������, �������� � ����������
	cout << accumulate(a.begin(), a.end(), 0) << endl; // ����� ���� ���������
}