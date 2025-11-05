/*
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <cctype>

using namespace std;

struct Question {
    string topic;
    int cost;
    string text;
    vector<string> options; //состоять будет из A, B, C, D
    char correct;
};

map<pair<int, int>, Question> questions_dict;

char display_question_with_answers(map<pair<int, int>, Question>& questions_dict)
{
    int i, j;
    cout << "Введите сторку и столбец вашего вопроса: ";
    cin >> i >> j;

    auto key = make_pair(i, j); //создает пару из двух целых чисел i и j
    auto it = questions_dict.find(key); //ищем элемент в map по ключу key и возвращаем итератор(указатель на элемент)
    if (it == questions_dict.end())
    {
        cout << "Вопрос с координатами " << i << j << " не найден\n";
        return 'X';
    }
    const Question& q = it->second; //получаем ссылку на найденный вопрос 

    const int WIDTH = 40;
    cout << "+" << string(WIDTH, '-') << "+\n";
    cout << "| Тема: " << left << setw(33) << q.topic << "|\n";
    cout << "| Стоимость: " << left << setw(28) << (to_string(q.cost) + " баллов") << "|\n";
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
        cout << "Некорректный ввод ответа, введите A, B, C или D\n";
        return display_question_with_answers(questions_dict);
    }
    return answer;
}
*/