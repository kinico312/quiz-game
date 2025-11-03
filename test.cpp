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
    cout << "Введите номер строки и столбца вопроса: ";
    cin >> i >> j;

    auto key = make_pair(i, j);
    auto it = questions_dict.find(key);
    if (it == questions_dict.end())
    {
        cout << "Вопрос с координатами " << i << "; " << j << " не найден\n";
        return 'X';
    }
    const Question& q = it->second;

    const int WIDTH = 40;
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << "| Тема: " << left << setw(33) << q.topic << "|\n";
    cout << "| Стоимость: " << left << setw(28) << (to_string(q.cost) + " очков") << "|\n";
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << "| " << left << setw(39) << q.text << "|\n";
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << "| A) " << left << setw(15) << q.options[0] << " B) " << left << setw(17) << q.options[1] << "|\n";
    cout << "| C) " << left << setw(15) << q.options[2] << " D) " << left << setw(17) << q.options[3] << "|\n";
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
        } catch (...) {
            // Игнорируем — по требованию отказоустойчивости
        }
    } else {
        cout << "Неверно. Правильный ответ: "
             << static_cast<char>('A' + q.correct) << " ("
             << q.options[q.correct] << ")\n";
    }

    // Показать текущие очки (мягко, без падений)
    try {
        const auto& user = Tracking::current_user();
        cout << "Очки игрока '" << user.name << "': " << user.score << "\n";
    } catch (...) {
        // Не критично, продолжаем
    }

    return answer;
}