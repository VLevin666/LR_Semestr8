#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex myMutex;

int vvod() {
    cout << "Введите число от 0 до 20: ";
    int a;
    cin >> a;
    if ((a > 20) || (a < 0) || (cin.fail())) {
        cout << "Ошибка ввода!" << endl;
        vvod();
    }
    else {
        return a;
    }
}

void res_fact(int start, int stop, unsigned long long& result) {
    int res = 1;
    if (start == 0) {
        start = 1;
    }
    for (int i = start; i < stop; i++) {
        res = res * i;
    }
    lock_guard<mutex> lock(myMutex);
    result = result * res;
}

int main() {
    setlocale(LC_ALL, "RUS");
    cout << "<Вычисление факториала числа>" << endl << endl;
    const int kolvo_potok = thread::hardware_concurrency();
    int n = vvod();
    int step = n / kolvo_potok;
    unsigned long long result = 1;

    if (step < 1) {
        thread one_potok(res_fact, 1, n + 1, ref(result));
        one_potok.join();
    }
    else {
        thread t[20];
        for (int i = 0; i < kolvo_potok; i++) {
            int start = step * i;
            int stop = step * (i + 1);
            if ((i + 1) == kolvo_potok) {
                stop = n + 1;
            }
            t[i] = thread(res_fact, start, stop, ref(result));
        }
        for (int i = 0; i < kolvo_potok; i++) {
            t[i].join();
        }
    }
    cout << n << "! = " << result << endl;
    return 0;
}