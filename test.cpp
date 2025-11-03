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
    cin >> j;
    j -= 1;

    auto key = make_pair(i, j);
    auto it = questions_dict.find(key);
    if (it == questions_dict.end())
    {
        cout << "вопрос под номерами " << i << "; " << j << " не существует\n";
        return 'X';
    }
    const Question& q = it->second;

    const int WIDTH = 70;
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << "| Темавфввцфв: " << left << setw(WIDTH-29) << q.topic << left << setw(22)<< "Стоимость:"+(to_string(q.cost) + " баллов ") << "| \n";
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << left << setw((WIDTH/2)-(q.text.length())/2) <<"| " << left << setw((WIDTH / 2) + (q.text.length()) / 2+1) << q.text << "|\n";
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << "| A) " << left << setw(WIDTH-4) << q.options[0] << "|\n| B) " << left << setw(WIDTH-4) << q.options[1] ;
    cout << "|\n| C) " << left << setw(WIDTH -4) << q.options[2] << "|\n| D) " << left << setw(WIDTH-4) << q.options[3]<<"|\n";
    cout << "+" << string(WIDTH, '-') << "+\n";

    cout << "Ваш ответ: ";
    char answer;
    cin >> answer;
    answer = toupper(static_cast<unsigned char>(answer));

    if (answer != 'A' && answer != 'B' && answer != 'C' && answer != 'D')
    {
        cout << "Неверный ввод, введите один из символов: A, B, C или D\n";
        return display_question_with_answers();
    }
    return answer;
}