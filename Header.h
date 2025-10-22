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

std::map<std::pair<int, int>, Question> dictionary();

char display_question_with_answers(
    const std::map<std::pair<int, int>, Question>& questions_dict,
    int i,
    int j
);


