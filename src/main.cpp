#include <iostream>
#include "head.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    auto loaded_questions = dictionary();

    if (loaded_questions.empty()) {
        cout << "пустой!\n";
        return 1;
    }

    cout << "загружено " << loaded_questions.size() << " вопросов!\n\n";

    game();

    return 0;
}