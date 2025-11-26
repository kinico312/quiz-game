#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include "head.hpp"
#include "multiple_players.hpp"
#include <chrono>
#include <thread>

using namespace std;

void load_random_round_file() {
    cout << "Текущий файл случайного раунда: " << filename << endl;
    cout << "Хотите использовать другой файл? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();

    if (choice == 'y' || choice == 'Y') {
        cout << "Введите путь к файлу для случайного раунда: ";
        getline(cin, filename);
    }

    cout << "Файл для случайного раунда: " << filename << endl;
}

map<pair<int, int>, Question> load_random_questions() {
    map<pair<int, int>, Question> random_questions;

    cout << "Загрузка вопросов для случайного раунда из: " << filename << endl;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл случайного раунда: " << filename << endl;
        cout << "Использую основной файл вопросов.\n";
        return questions_dict;
    }

    string line;
    int row = 0;
    int loaded_count = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> cells;
        string cell;
        size_t start = 0;
        size_t end = line.find(';');

        while (end != string::npos) {
            cell = line.substr(start, end - start);
            cell.erase(0, cell.find_first_not_of(" \t"));
            cell.erase(cell.find_last_not_of(" \t") + 1);
            cells.push_back(cell);
            start = end + 1;
            end = line.find(';', start);
        }
        cell = line.substr(start);
        cell.erase(0, cell.find_first_not_of(" \t"));
        cell.erase(cell.find_last_not_of(" \t") + 1);
        cells.push_back(cell);

        if (cells.size() >= 8) {
            try {
                Question q;
                q.topic = cells[0];
                q.cost = stoi(cells[1]);
                q.text = cells[2];
                q.options = { cells[3], cells[4], cells[5], cells[6] };

                q.correct = cells[7];
                if (!q.correct.empty() && q.correct.back() == ',') {
                    q.correct.pop_back();
                }

                q.flag = true;

                random_questions[{row, 0}] = q;
                row++;
                loaded_count++;
            }
            catch (const exception& e) {
                cout << "Ошибка парсинга строки: " << e.what() << endl;
            }
        }
        else {
            cout << "Пропущена строка с " << cells.size() << " колонками (ожидается 8)" << endl;
        }
    }

    file.close();
    cout << "Загружено " << loaded_count << " вопросов для случайного раунда\n";
    return random_questions;
}

void prepare_random_questions(int count) {
    random_round_questions.clear();

    auto random_questions_dict = load_random_questions();

    if (random_questions_dict.size() < count) {
        cout << "В файле случайного раунда мало вопросов. Использую основные вопросы.\n";
        random_questions_dict = questions_dict;
    }

    vector<Question> all_questions;
    for (const auto& entry : random_questions_dict) {
        all_questions.push_back(entry.second);
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(all_questions.begin(), all_questions.end(), g);

    for (int i = 0; i < count && i < all_questions.size(); i++) {
        random_round_questions.push_back(all_questions[i]);
    }

    cout << "Подготовлено " << random_round_questions.size() << " случайных вопросов\n";
}

void print_random_questions_matrix() {
    cout << "==============================================\n";
    cout << "           СЛУЧАЙНЫЙ РАУНД\n";
    cout << "==============================================\n";
    cout << "Файл: " << filename << "\n";
    cout << "==============================================\n";

    for (int i = 0; i < random_round_questions.size(); i++) {
        const Question& q = random_round_questions[i];
        string status = q.flag ? "[ДОСТУПЕН]" : "[ОТВЕЧЕН]";
        cout << "[" << i + 1 << "] " << q.topic << " - " << q.cost << " очков " << status << "\n";
    }
    cout << "==============================================\n";
}

void handle_random_question(int index) {
    if (index < 0 || index >= random_round_questions.size()) {
        cout << "Неверный номер вопроса!\n";
        return;
    }

    Question& question = random_round_questions[index];

    if (!question.flag) {
        cout << "Этот вопрос уже был отвечен!\n";
        return;
    }

    cout << "\n=== СЛУЧАЙНЫЙ РАУНД ===\n";
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

void play_random_round() {
    is_random_round = true;

    cout << "\n*** НАЧИНАЕТСЯ СЛУЧАЙНЫЙ РАУНД ***\n\n";

    load_random_round_file();
    prepare_random_questions(10);

    int questions_answered = 0;
    while (questions_answered < random_round_questions.size()) {
        system("cls");
        print_random_questions_matrix();
        show_scoreboard();

        int question_num;
        cout << "\nВыберите вопрос (1-" << random_round_questions.size() << ", 0 - выход): ";
        cin >> question_num;

        if (question_num == 0) {
            break;
        }

        if (question_num >= 1 && question_num <= random_round_questions.size()) {
            if (random_round_questions[question_num - 1].flag) {
                handle_random_question(question_num - 1);
                questions_answered++;
            }
            else {
                cout << "Этот вопрос уже отвечен!\n";
            }
        }
        else {
            cout << "Неверный номер вопроса!\n";
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.ignore();
        cin.get();
    }

    is_random_round = false;
    cout << "\n*** СЛУЧАЙНЫЙ РАУНД ЗАВЕРШЕН ***\n\n";
}