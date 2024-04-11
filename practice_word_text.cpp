#include <iostream>
#include <omp.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main() {
    setlocale(0, "");

    ifstream text_hobbit("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы Кузин/practice_word_text/practice_word_text/Хоббит.txt");
    if (!text_hobbit.is_open()) {
        cout << "Ошибка! Не удалось открыть файл!" << endl;
        return -1;
    }

    string stroka;
    vector<string> text_in_prog;
    while (getline(text_hobbit, stroka)) {
        if (stroka != "") {
            text_in_prog.push_back(stroka);
        }
    }
    text_hobbit.close();  

    map<string, int> kolvo_word;
    map<string, int>::iterator it;
    vector<string> all_words;

#pragma omp parallel for 
    for (int i = 0; i < text_in_prog.size(); i++) {
        stringstream poisk_word{ text_in_prog[i] };
        string word;

        while (poisk_word >> word) {
            it = kolvo_word.find(word);
            if (it == kolvo_word.end()) {
#pragma omp critical
                kolvo_word[word] = 1;
                all_words.push_back(word);
            }
            else {
#pragma omp critical
                kolvo_word[word]++;
            }
        }
    }


    int max_kolvo_word1 = 1;
    int max_kolvo_word2 = 1;
    int max_kolvo_word3 = 1;
    int max_kolvo_word4 = 1;
    int max_kolvo_word5 = 1;
    string top_word1, top_word2, top_word3, top_word4, top_word5;

    for (int i = 0; i < all_words.size(); i++) {
        if (kolvo_word[all_words[i]] > max_kolvo_word1) {
            max_kolvo_word1 = kolvo_word[all_words[i]];
            top_word1 = all_words[i];
        }
        else {
            if (kolvo_word[all_words[i]] > max_kolvo_word2) {
                max_kolvo_word2 = kolvo_word[all_words[i]];
                top_word2 = all_words[i];
            }
            else {
                if (kolvo_word[all_words[i]] > max_kolvo_word3) {
                    max_kolvo_word3 = kolvo_word[all_words[i]];
                    top_word3 = all_words[i];
                }
                else {
                    if (kolvo_word[all_words[i]] > max_kolvo_word4) {
                        max_kolvo_word4 = kolvo_word[all_words[i]];
                        top_word4 = all_words[i];
                    }
                    else {
                        if (kolvo_word[all_words[i]] > max_kolvo_word5) {
                            max_kolvo_word5 = kolvo_word[all_words[i]];
                            top_word5 = all_words[i];
                        }
                    }
                }
            }
        }
    }

    cout << "Представляем Вашему вниманию топ-5 слов в выбранном файле:" << endl;
    cout << "1 место: в тексте - " << max_kolvo_word1 << " \"" << top_word1 << "\"" << endl;
    cout << "2 место: в тексте - " << max_kolvo_word2 << " \"" << top_word2 << "\"" << endl;
    cout << "3 место: в тексте - " << max_kolvo_word3 << " \"" << top_word3 << "\"" << endl;
    cout << "4 место: в тексте - " << max_kolvo_word4 << " \"" << top_word4 << "\"" << endl;
    cout << "5 место: в тексте - " << max_kolvo_word5 << " \"" << top_word5 << "\"" << endl;

    return 0;
}

