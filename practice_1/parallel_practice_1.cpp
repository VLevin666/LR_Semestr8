#include <iostream>
#include "omp.h"

using namespace std;

int hello_world() {
#pragma omp for
	for (int i = 0; i < 4; i++)
		cout << "Привет, мир!" << endl;
	return 0;
};

int kolvo_potokov() {
	int n;
#pragma omp parallel for
	cout << "Введите число потоков: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Поток номер " << i << ". Всего потоков - " << n << endl;
	}
	return 0;
}

int kolvo_potokov_ompget() {
	int n, num_thread;
	cout << "Введите число потоков: ";
	cin >> n;

#pragma omp parallel num_threads(n)
	{
#pragma omp critical
		{
			num_thread = omp_get_thread_num();
			cout << "Поток номер " << num_thread << endl;
		}
	}
	return 0;
}

int main() {
	setlocale(0, "");

	hello_world();
	cout << endl;

	kolvo_potokov();
	cout << endl;

	kolvo_potokov_ompget();
	cout << endl;

	return 0;
}