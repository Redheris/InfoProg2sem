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

/*
3 5 1 2 4 6

3 5 1 2 4 6
  . .
3 1 5 2 4 6
      . .
3 1 5 2 4 6
. .
1 3 5 2 4 6
    . .
1 3 2 5 4 6
        . .
1 3 2 5 4 6
  . .
1 2 3 5 4 6
      . .
1 2 3 4 5 6
*/
// 12. Сортировка чет-нечет
void sort_even_odd(vector<int>& vec) {
	int N = vec.size();
	for (int i = 0; i < N - 1; ++i) {
		// Если индекс элемента чётный
		if (i % 2 == 0) {
			for (int j = 2; j < N; j += 2)
				if (vec[j - 1] > vec[j])
					swap(vec[j - 1], vec[j]);
		}
		// Если индекс элемента нечётный
		else {
			for (int j = 1; j < N; j += 2)
				if (vec[j - 1] > vec[j])
					swap(vec[j - 1], vec[j]);
		}
	}
}

// Сортировка диагоналей
void sort_diagonals(int(&arr)[7][7]) {
	int N = 7;
	// Цикл для каждой диагонали (2 за цикл)
	for (int k = 0; k < N - 1; ++k) {

		// Диагонали под главной

		vector<int> diag; // Рассматриваемая диагональ

		// Запись диагонали в вектор
		for (int i = 0; i < N; ++i) {
			if (k + i < N)
				diag.push_back(arr[i][k + i]);
		}

		// Вызов сортировки
		sort_even_odd(diag);
		int L = 0;

		// Запись в диагональ исходного массива
		// остортированного вектора
		for (int i = 0; i < N - k; ++i) {
			if (k - i < N) {
				arr[i][k + i] = diag.at(L++);
			}
		}

		// Диагонали над главной
		diag.clear();

		// Запись диагонали в вектор
		for (int j = 0; j < N; ++j) {
			if (k + j < N)
				diag.push_back(arr[k + j][j]);
		}


		// Вызов сортировки
		sort_even_odd(diag);

		L = 0;
		// Запись в диагональ исходного массива
		// остортированного вектора
		for (int j = 0; j < N; ++j) {
			if (k + j < N)
				arr[k + j][j] = diag[L++];
		}
		diag.clear();
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
	cout << "Номер задания:\n 1 - Подсчётом\n 2 - Гномья\n 3 - Чет-нечет" << endl;
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
		sort_diagonals(arr);
		break;
	}

	print(arr);

	in.close();
	out.close();
}