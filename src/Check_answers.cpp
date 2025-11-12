#include "head.hpp"
#include <iostream>
#include <cctype>
#include "multiple_players.hpp"

extern std::map<std::pair<int, int>, Question> questions_dict;
using namespace std;

bool check_answer(char user_answer, int row, int col)
{
    auto it = questions_dict.find({ row, col });
    if (it == questions_dict.end())
    {
        cout << "Такого вопроса нет!\n";
        return false;
    }

    const Question& q = it->second;

    // Приводим ответ пользователя к верхнему регистру
    char user_upper = toupper(user_answer);

    // Проверяем валидность ввода
    if (user_upper != 'A' && user_upper != 'B' && user_upper != 'C' && user_upper != 'D') {
        cout << "Введите A, B, C или D.\n";
        return false;
    }

    // Сравниваем ответ пользователя с правильным ответом
    bool correct = (user_upper == q.correct[0]); // Берем первый символ строки

    // Получаем имя текущего игрока ДО изменения очков
    string current_player = get_current_player_name();
    int old_score = get_current_player_score();

    if (correct)
    {
        add_score_to_current_player(q.cost);
        int new_score = get_current_player_score();
        cout << "✅ Вы получили +" << q.cost << " очков\n";
        cout << current_player << " Было очков: " << old_score << " Стало " << new_score << endl;
    }
    else
    {
        cout << "❌ Ответ неверный. Правильный ответ: " << q.correct << endl;
        cout << "Игрок '" << current_player << "' — имеет очков: " << old_score << endl;
    }

    return correct;
}