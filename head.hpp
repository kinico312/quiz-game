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

// Простая система трекинга пользователя и очков
namespace Tracking {
    struct User {
        std::string name;
        int score;
    };

    // Инициализация текущего пользователя (если уже инициализирован — перезаписывает)
    void init_default_user(const std::string& name);

    // Добавление очков текущему пользователю (без выброса исключений)
    void add_score(int points) noexcept;

    // Получить текущего пользователя (создаст дефолтного, если не инициализирован)
    const User& current_user() noexcept;
}