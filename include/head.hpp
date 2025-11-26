#pragma once
#include <string>
#include <vector>
#include <map>
#include <random>

struct Question {
    std::string topic;
    int cost;
    std::string text;
    std::vector<std::string> options;
    std::string correct;
    bool flag;
};

extern std::string filename;
extern std::map<std::pair<int, int>, Question> questions_dict;
extern std::vector<Question> random_round_questions;
extern bool is_random_round;

void setQuestionFlag(int row, int col, bool new_flag);
std::map<std::pair<int, int>, Question> dictionary();
void print_questions_matrix();
void game();
void handleQuestion(int row, int col);
void create_user(const std::string& name);
std::pair<char, bool> display_question_with_answers(int row, int col);
bool check_answer(char user_answer, int row, int col);
void transfer_cat_question();
void conduct_auction();

// Функции случайного раунда
void play_random_round();
void load_random_round_file();
std::map<std::pair<int, int>, Question> load_random_questions();
void prepare_random_questions(int count = 10);
void print_random_questions_matrix();
void handle_random_question(int index);

// Финальные результаты
void show_final_results();