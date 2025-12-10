#include <iostream>
#include "head.hpp"

using namespace std;
string filename;
map<pair<int, int>, Question> questions_dict;
vector<Question> random_round_questions;
bool is_random_round = false;

int main()
{
    setlocale(LC_ALL, "RU");

    cout << "Введите ссылку на основной файл: ";
    getline(cin, filename);

    auto loaded_questions = dictionary();
    if (loaded_questions.empty()) {
        cout << "Не удалось загрузить вопросы!\n";
        return 1;
    }

    cout << "Загружено " << loaded_questions.size() << " вопросов!\n\n";
    game();

    return 0;
}