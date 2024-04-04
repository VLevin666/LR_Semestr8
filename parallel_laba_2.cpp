#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>
#include <chrono>
using namespace std;

mutex myMutex;

void write_to_file(int n) {
    unique_lock<mutex> lock(myMutex);
    fstream file_text("Res.txt", ios::app);
    cout << "Поток " << n + 1 << " стартовал" << endl;
    file_text << "Поток " << n + 1 << " стартовал" << endl;
    chrono::milliseconds timespan(2000);
    this_thread::sleep_for(timespan);
    cout << "Поток " << n + 1 << " заврешен" << endl;
    file_text << "Поток " << n + 1 << " заврешен" << endl;
    file_text.close();
    lock.unlock();
}


int main() {
    setlocale(LC_ALL, "RUS");
    cout << "<Спасение файла>" << endl << endl;
    const int kolvo_potok = thread::hardware_concurrency();

    fstream file_text;
    file_text.open("Res.txt", fstream::out | fstream::trunc);
    file_text.close();

    thread t[20];
    for (int i = 0; i < kolvo_potok; i++) {
        t[i] = thread(write_to_file, i);
    }

    for (int i = 0; i < kolvo_potok; i++) {
        t[i].join();
    }

    return 0;
}
