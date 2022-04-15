#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

ifstream in("task4-in.txt");
ofstream out("task4-out.txt");

int max_arr(int arr[7]) {
	int max = -1;
	for (int i = 0; i < 7; ++i) {
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

void print(int(&arr)[7][7]) {
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			out << arr[i][j] << " ";
		}
		out << endl;
	}
}


// 2. Сортировка строк по возрастанию подсчётом
void sort_counting(int(&arr)[7][7]) {
	// Для каждой строки
	for (int i = 0; i < 7; ++i) {
		int N = 7, k = max_arr(arr[i]) + 1;

		// Создание и заполение нулями доп. массива
		int* B = new int[k];
		for (int j = 0; j < k; ++j)
			B[j] = 0;

		// Запись в доп. массив кол-ва каждого встречающегося числа
		// соответственно с индексом
		for (int j = 0; j < N; ++j)
			B[arr[i][j]]++;

		int ind = 0;
		// Перезапись (сортировка) строки
		for (int num = 0; num < k; ++num) { // Каждое число в промежутке

			// Запись в строку B[num] числа num
			while (B[num] > 0) {
				arr[i][ind++] = num;
				B[num]--;
			}
		}
	}
}

/*
3 5 1 2 4 6
  + -
3 1 5 2 4 6
  - 
1 3 5 2 4 6
> + + -
...
1 2 3 5 4 6
  + + + -
1 2 3 4 5 6
      + + +
*/
// 10. Гномья сортировка
void gnome_sort(int(&arr)[7][7]) {
	// Для каждой строки
	for (int i = 1; i < 7; i += 2) {
		int N = 7, j = 1;

		while (j < N) { // Пока j не дойдёт до конца
			if (j == 0)
				j++;
			if (arr[i][j - 1] >= arr[i][j])
				j++;
			else {
				swap(arr[i][j - 1], arr[i][j]);
				j--;
			}
		}
	}
}


int main() {
	setlocale(LC_ALL, "RUS");

	int arr[7][7];

	cout << "Входной массив:" << endl;
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			in >> arr[i][j];
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Номер задания:\n 1 - Подсчётом\n 2 - Гномья\n 3 - " << endl;
	int flag;
	cin >> flag;
	switch (flag) {
	case 1:
		sort_counting(arr);
		break;
	case 2:
		gnome_sort(arr);
		break;
	case 3:
		
		break;
	}

	print(arr);

	in.close();
	out.close();
}