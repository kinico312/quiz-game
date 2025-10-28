#include <iostream>
#include "head.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");


    auto loaded_questions = dictionary();

    if (loaded_questions.empty()) {
        cout << "�� ������� ��������� ������� �� �����!\n";
        return 1;
    }

    cout << "������� ��������� " << loaded_questions.size() << " ��������!\n\n";


    print_questions_matrix();

    cout << "\n";


    char answer = display_question_with_answers();

    if (answer != 'X') {
        cout << "�� �����: " << answer << "\n";
    }

    return 0;
}