#include <iostream>
#include "head.hpp"
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <cctype>

using namespace std;

char display_question_with_answers()
{
    int i, j;
    cout << "Выберите номер темы : ";
    cin >> i; i -= 1;
    cout << "Выберите номер вопроса : ";
    cin >> j; j -= 1;
   
    auto key = make_pair(i, j);
    auto it = questions_dict.find(key);
    if (it == questions_dict.end())
    {
        cout << "вопрос под номерами " << i << "; " << j << " не найден\n";
        return 'X';
    }
    const Question& q = it->second;

    const int WIDTH = 70;
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << "| Тема: " << left << setw(WIDTH - 29) << q.topic << left << setw(22) << "Стоимость:" + (to_string(q.cost) + " баллов ") << "| \n";
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << left << setw((WIDTH / 2) - (q.text.length()) / 2) << "| " << left << setw((WIDTH / 2) + (q.text.length()) / 2 + 1) << q.text << "|\n";
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << "| A) " << left << setw(WIDTH - 4) << q.options[0] << "|\n| B) " << left << setw(WIDTH - 4) << q.options[1];
    cout << "|\n| C) " << left << setw(WIDTH - 4) << q.options[2] << "|\n| D) " << left << setw(WIDTH - 4) << q.options[3] << "|\n";
    cout << "+" << string(WIDTH, '-') << "+\n";

    cout << "Ваш ответ: ";
    char answer;
    cin >> answer;
    answer = toupper(static_cast<unsigned char>(answer));

    if (answer != 'A' && answer != 'B' && answer != 'C' && answer != 'D')
    {
        cout << "Некорректный формат ответа, введите A, B, C или D\n";
        return display_question_with_answers();
    }

    int answerIndex = -1;
    switch (answer) {
    case 'A': answerIndex = 0; break;
    case 'B': answerIndex = 1; break;
    case 'C': answerIndex = 2; break;
    case 'D': answerIndex = 3; break;
    default: break;
    }

    bool isCorrect = (answerIndex == q.correct);
    if (isCorrect) {
        cout << "Верно! +" << q.cost << " очков\n";
        // Обновляем очки пользователя, но не даём ошибкам рушить основной поток
        try {
            Tracking::add_score(q.cost);
        }
        catch (...) {
            // Игнорируем — по требованию отказоустойчивости
        }
    }
    else {
        cout << "Неверно. Правильный ответ: "
            << static_cast<char>('A' + q.correct) << " ("
            << q.options[q.correct] << ")\n";
    }

    // Показать текущие очки (мягко, без падений)
    try {
        const auto& user = Tracking::current_user();
        cout << "Очки игрока '" << user.name << "': " << user.score << "\n";
    }
    catch (...) {
        // Не критично, продолжаем
    }

    return answer;
}