#pragma once

#include <string>
#include <vector>
#include <map>

struct Question {
    std::string topic;
    int cost;
    std::string text;
    std::vector<std::string> options;
    std::string correct; 
    bool flag;
};

extern std::map<std::pair<int, int>, Question> questions_dict;
void setQuestionFlag(int row, int col, bool new_flag);
std::map<std::pair<int, int>, Question> dictionary();
void print_questions_matrix();
void game();
void handleQuestion(int row, int col);
void create_user(const std::string& name);

std::pair<char, bool> display_question_with_answers(int row, int col);

bool check_answer(char user_answer, int row, int col);
void transfer_cat_question();
void conduct_auction(std::map<std::string, int>& players, std::string& winner, int& winning_bid);
void conduct_auction();