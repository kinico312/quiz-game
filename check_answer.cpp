#include "head.hpp"
#include <iostream>
#include <cctype>

extern std::map<std::pair<int, int>, Question> questions_dict;
using namespace std;

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