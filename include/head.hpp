#pragma once

#include <string>
#include <vector>
#include <map>

struct Question {
    std::string topic;
    int cost;
    std::string text;
    std::vector<std::string> options;
    int correct;
};

extern std::map<std::pair<int, int>, Question> questions_dict;

std::map<std::pair<int, int>, Question> dictionary();
char display_question_with_answers();
void print_questions_matrix();
void game();
// ѕроста€ система трекинга пользовател€ и очков
namespace Tracking {
    struct User {
        std::string name;
        int score;
    };

    // »нициализаци€ текущего пользовател€ (если уже инициализирован Ч перезаписывает)
    void init_default_user(const std::string& name);

    // ƒобавление очков текущему пользователю (без выброса исключений)
    void add_score(int points) noexcept;

    // ѕолучить текущего пользовател€ (создаст дефолтного, если не инициализирован)
    const User& current_user() noexcept;
}
