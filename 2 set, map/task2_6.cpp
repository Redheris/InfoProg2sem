#include<iostream>
#include<string>
#include<set>
#include<algorithm>


using namespace std;

// ��-�� ��� ���� �����������������, �������. � ��������. �����������
set<string> narrative, exclam, question;


// ����� ���� ��-��� ���������
void print(set<string>& a) {
	for (auto it = a.begin(); it != a.end(); it++) {
		cout << *it << ", ";
	}
	cout << endl;
}

// �������� ������� ����� � �����. ��� ����. �����-��
bool notInclude(string s) {
	return exclam.find(s) != exclam.end() || question.find(s) != question.end();
}

// ������� ������ � ������ �������
string stringToLower(string s) {
	for (char &c : s) {
		c = tolower(c);
	}
	return s;
}

// ���������� ����������� �� ����� �� ����������� � ���������� �� � ��-��
void addSplit(string s, char del, set<string>& res) {
	// ������ ������� �����
	int n = s.find_first_not_of(' ');

	while (s.find(del, n) != string::npos) {
		// ����� �����������
		string temp = s.substr(n, s.find(del, n) - n);

		// ���������� � ��-�� ��������� ����
		if (temp.length() > 0)
			res.insert(temp);

		// ������ ������ ���������� �����
		n = s.find(del, n + 1) + 1;
	}
}


int main() {
	setlocale(LC_ALL, "RUS");

	// ������ �����
	string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor? Incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris! Nisi ut aliquip ex ea commodo consequat? Duis aute irure dolor in reprehenderit in voluptate? Velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

	// �������� �� ������ ������ ����������
	for (char c : ",:;-")
		while (text.find(c) != string::npos)
			text.erase(text.find(c), 1);

	cout << "����������������� �����������:" << endl;

	
	while (text.find_first_of(".?!") != string::npos) {
		// ��������� ������ �����������
		int i = text.find_first_of("?!.");

		// ����������� ������
		string temp = stringToLower(text.substr(0, i));
		
		// ������������� ���� �� ��-���
		if (text[i] == '.') {
			cout << text.substr(0, i + 1) << endl;
			addSplit(temp, ' ', narrative);
		}
		else if(text[i] == '!')
			addSplit(temp, ' ', exclam);
		else
			addSplit(temp, ' ', question);

		text.erase(0, i + 1); // �������� ����������� �� ������
	}
	
	// �������� �� ��-�� ���� �������. ����������� ����, ������������� � �����. � ����. ������������
	for (set<string>::iterator it = find_if(narrative.begin(), narrative.end(), notInclude); it != narrative.end(); it = find_if(it, narrative.end(), notInclude)) {
		narrative.erase(it++);
	}
	
	cout << "\n(" << narrative.size() << ") �����, ������������� ������ � �������. ������������:" << endl;
	print(narrative);
}