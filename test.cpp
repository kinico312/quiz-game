#include <iostream>
#include "head.hpp"
#include <iomanip>
#include <cctype>

using namespace std;

extern map<pair<int, int>, Question> questions_dict;

pair<char, bool> display_question_with_answers(int row, int col)
{
    auto it = questions_dict.find({ row, col });
    if (it == questions_dict.end())
    {
        cout << "Вопрос с координатами  " << row << "; " << col << " не найден\n";
        return { 'X', false };
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
        return { answer, false };
    }

    return { answer, true };
}


bool check_answer(char user_answer, int row, int col)
{
    auto it = questions_dict.find({ row, col });
    if (it == questions_dict.end())
    {
        return false;
    }

    const Question& q = it->second;
    int answer_index = -1;
    switch (user_answer) {
    case 'A': answer_index = 0; break;
    case 'B': answer_index = 1; break;
    case 'C': answer_index = 2; break;
    case 'D': answer_index = 3; break;
    default: return false;
    }

    bool correct = (answer_index == q.correct);
    if (correct)
    {
        add_score_to_current_player(q.cost);
        cout << "Верный ответ! +" << q.cost << " очков\n";
    }
    else
    {
        char correct_char = 'A' + q.correct;
        cout << "Неправильный ответ";
    }
    cout << "Игрок '" << get_current_player_name() << "' — очки: " << get_current_player_score() << endl;
    return correct;
}

   