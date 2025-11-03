#include <iostream>
#include "head.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");


    // Инициализируем пользователя по умолчанию
    Tracking::init_default_user("Player1");

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
        cout << "Вы ответили: " << answer << "\n";
    }

    return 0;
}