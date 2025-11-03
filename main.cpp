#include <iostream>
#include "head.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");

    auto loaded_questions = dictionary();

    if (loaded_questions.empty()) {
        cout << "Не удалось загрузить вопросы из файла!\n";
        return 1;
    }

    cout << "Успешно загружено " << loaded_questions.size() << " вопросов!\n\n";


    print_questions_matrix();

    cout << "\n";


    char answer = display_question_with_answers();

    if (answer != 'X') {
        cout << "Вы ввели: " << answer << "\n";
    }

    return 0;
}