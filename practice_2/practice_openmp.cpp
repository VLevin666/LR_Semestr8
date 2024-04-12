#include <iostream>
#include "omp.h"
#include <thread>
#include <vector>
#include <chrono>
#include <ctime> 
using namespace std;

void sum_array() {
	int size_array;
	cout << "Введите размер массива: ";
	cin >> size_array;
	int* mas = new int[size_array];
	double summa = 0;
	cout << "Случайный массив: ";

	for (int i = 0; i < size_array; i++) {
		srand(time(NULL));
		mas[i] = rand()%100;
		cout << mas[i];
		if (i + 1 != size_array) {
			cout << ", ";
		}
	}
	cout << endl;

#pragma omp parallel num_threads(3) reduction(+:summa)
#pragma omp parallel for
	for (int i = 0; i < size_array; i++) {
		summa += mas[i];
	}
	cout << "Сумма элементов массива = " << summa << endl;
	return;

	}

	void zamena_elem_array(int* array, int left, int seredina, int right) {
		int* temp = new int[right + 1];
		int left_part = left;
		int right_part = seredina + 1;
		int k = 0;

		while (left_part <= seredina && right_part <= right) {
			if (array[left_part] <= array[right_part])
				temp[k++] = array[left_part++];
			else
				temp[k++] = array[right_part++];
		}
		while (left_part <= seredina)
			temp[k++] = array[left_part++];
		while (right_part <= right)
			temp[k++] = array[right_part++];
		k--;
		while (k >= 0) {
			array[k + left] = temp[k];
			k--;
		}
	}

	void sort_array_no_parallel(int* array, int left, int right) {
		int seredina;
		if (left < right) {
			seredina = (left + right) / 2;
			sort_array_no_parallel(array, left, seredina);
			sort_array_no_parallel(array, seredina + 1, right);
			zamena_elem_array(array, left, seredina, right);
		}
	}

	void sort_array_parallel(int* mas, int left, int right) {
		if (left < right) {
			int seredina = left + (right - left) / 2;
#pragma omp parallel sections
		{
#pragma omp section
			sort_array_parallel(mas, left, seredina);
#pragma omp section
			sort_array_parallel(mas, seredina + 1, right);
		}
			zamena_elem_array(mas, left, seredina, right);
		}
	}

	void sort_array() {
		const int size_array = 100;
		int array1[size_array];
		int array2[size_array];
		long long int sum = 0;
		for (int i = 0; i < size_array; ++i) {
			array1[i] = rand() % 100;
			array2[i] = array1[i];
		}


		chrono::high_resolution_clock::time_point start_prog = chrono::high_resolution_clock::now();
		sort_array_no_parallel(array1, 0, size_array - 1);
		chrono::high_resolution_clock::time_point end_prog = chrono::high_resolution_clock::now();
		chrono::nanoseconds time_prog = chrono::duration_cast<chrono::nanoseconds>(end_prog - start_prog);

		cout << "Отсортированный массив (без ||): ";
		for (int i = 0; i < size_array; i++) {
			cout << array1[i] << " ";
		}
		cout << endl;
		cout << "Время работы (без ||): " << endl;
		cout << time_prog.count() << endl;


		chrono::high_resolution_clock::time_point start_prog2 = chrono::high_resolution_clock::now();
		sort_array_parallel(array2, 0, size_array - 1);
		chrono::high_resolution_clock::time_point end_prog2 = chrono::high_resolution_clock::now();
		chrono::nanoseconds time_prog2 = chrono::duration_cast<chrono::nanoseconds>(end_prog2 - start_prog2);

		cout << "Отсортированный массив (c ||): ";
		for (int i = 0; i < size_array; i++) {
			cout << array2[i] << " ";
		}
		cout << endl;
		cout << "Время работы (с ||): ";
		cout << time_prog2.count() << endl;

		cout << endl << "Выигрыш по времени = " << time_prog.count() - time_prog2.count() << endl;
	}

	int main() {
		setlocale(0, "");
		cout << "1.Сумма массива:" << endl;
		sum_array();
		cout << endl << endl;

		cout << "2.Сортировка массива:" << endl;
		sort_array();
	}