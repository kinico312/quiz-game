#include <iostream>
#include <vector>
#include <string>
#include "head.hpp"
#include "multiple_players.hpp"
#include <chrono>
#include <thread>

using namespace std;

void setQuestionFlag(int row, int col, bool new_flag) {
    auto it = questions_dict.find({ row, col });
    if (it != questions_dict.end()) {
        it->second.flag = new_flag;
    }
}

void handleQuestion(int row, int col) {
    auto it = questions_dict.find({ row, col });
    if (it == questions_dict.end()) {
        cout << "Вопрос не найден!\n";
        return;
    }

    Question& question = it->second;

    if (!question.flag) {
        cout << "Этот вопрос уже был отвечен!\n";
        return;
    }

    cout << "\n=== ВОПРОС ===\n";
    cout << "Тема: " << question.topic << "\n";
    cout << "Стоимость: " << question.cost << " очков\n";
    cout << "Вопрос: " << question.text << "\n\n";

    char option_char = 'A';
    for (const auto& option : question.options) {
        cout << option_char << ") " << option << "\n";
        option_char++;
    }

    char user_answer;
    cout << "\nВаш ответ (A/B/C/D): ";
    cin >> user_answer;
    user_answer = toupper(user_answer);

    char correct_char = 'A';
    bool found = false;
    for (int i = 0; i < question.options.size(); i++) {
        string option_clean = question.options[i];
        string correct_clean = question.correct;

        option_clean.erase(0, option_clean.find_first_not_of(" \t"));
        option_clean.erase(option_clean.find_last_not_of(" \t") + 1);
        correct_clean.erase(0, correct_clean.find_first_not_of(" \t"));
        correct_clean.erase(correct_clean.find_last_not_of(" \t") + 1);

        if (option_clean == correct_clean) {
            correct_char = 'A' + i;
            found = true;
            break;
        }
    }

    if (!found && !question.correct.empty()) {
        char correct_letter = toupper(question.correct[0]);
        if (correct_letter >= 'A' && correct_letter <= 'D') {
            correct_char = correct_letter;
            found = true;
        }
    }

    if (user_answer == correct_char && found) {
        cout << "Правильно! +" << question.cost << " очков\n";
        add_score_to_current_player(question.cost);
    }
    else {
        cout << "Неправильно! Правильный ответ: " << correct_char << "\n";
        cout << "-" << question.cost << " очков\n";
        div_score_to_current_player(question.cost);
    }

    question.flag = false;
    switch_to_next_player();

    
    cout << "\nОчистка через 3 секунды...";
    this_thread::sleep_for(chrono::seconds(3));
    system("cls");
}
std::pair<char, bool> display_question_with_answers(int row, int col) {
    return { 'A', true };
}

bool check_answer(char user_answer, int row, int col) {
    return true;
}