#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "head.hpp"
#include "multiple_players.hpp"

using namespace std;

map<pair<int, int>, Question> dictionary()
{
    int row = 0, col = 0;
    const int COLS_PER_ROW = 5;

    ifstream file(filename);
    map<pair<int, int>, Question> local_dict;

    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << "\n";
        return local_dict;
    }

    string line;
    int line_count = 0;
    int loaded_questions = 0;

    while (getline(file, line))
    {
        line_count++;

        if (line.empty()) {
            continue;
        }

        vector<string> cells;
        stringstream s(line);
        string cell;

        while (getline(s, cell, ';')) {
            cell.erase(0, cell.find_first_not_of(" \t"));
            cell.erase(cell.find_last_not_of(" \t") + 1);
            cells.push_back(cell);
        }

        if (cells.size() >= 8) {
            try {
                Question q;
                q.topic = cells[0];
                q.cost = stoi(cells[1]);
                q.text = cells[2];
                q.options = { cells[3], cells[4], cells[5], cells[6] };
                q.flag = true;

                string correct_str = cells[7];
                if (!correct_str.empty() && correct_str.back() == ',') {
                    correct_str.pop_back();
                }

                q.correct = correct_str;

                local_dict[{row, col}] = q;
                loaded_questions++;

                col++;
                if (col >= COLS_PER_ROW) {
                    col = 0;
                    row++;
                }

            }
            catch (const exception& e) {
                cout << "Ошибка в строке " << line_count << ": " << e.what() << "\n";
            }
        }
        else {
            cout << "Ошибка в строке " << line_count << ": только " << cells.size()
                << " колонок, ожидается 8\n";
        }
    }
    file.close();

    cout << "Загружено вопросов: " << loaded_questions << "\n";
    questions_dict = local_dict;
    return local_dict;
}

void print_questions_matrix() {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return;
    }

    map<char, pair<string, vector<string>>> themes;
    string line;
    char currentChar = 'A';
    string currentTheme = "";

    while (getline(file, line)) {
        vector<string> row;
        string cell;
        size_t start = 0;
        size_t end = line.find(';');

        while (end != string::npos) {
            cell = line.substr(start, end - start);
            row.push_back(cell);
            start = end + 1;
            end = line.find(';', start);
        }
        cell = line.substr(start);
        row.push_back(cell);

        if (row.size() >= 3 && !row[0].empty()) {
            if (row[0] != currentTheme) {
                currentTheme = row[0];

                if (currentChar > 'Z') {
                    cout << "Ошибка: слишком много тем! Максимум 26." << endl;
                    break;
                }

                themes[currentChar] = make_pair(currentTheme, vector<string>());
                currentChar++;
            }

            if (!themes.empty()) {
                map<char, pair<string, vector<string>>>::reverse_iterator lastTheme = themes.rbegin();
                themes[lastTheme->first].second.push_back(row[1]);
            }
        }
    }

    file.close();

    cout << "==============================================" << endl;
    cout << "               ТЕМЫ И БАЛЛЫ" << endl;
    cout << "==============================================" << endl;

    int theme_number = 0;
    for (map<char, pair<string, vector<string>>>::iterator it = themes.begin(); it != themes.end(); it++) {
        cout << "[" << theme_number << "] " << it->second.first << " - ";

        for (vector<string>::iterator points_it = it->second.second.begin(); points_it != it->second.second.end(); points_it++) {
            cout << *points_it << " ";
        }
        cout << endl;

        theme_number++;
    }

    cout << "==============================================" << endl;
}

void game()
{
    setlocale(LC_ALL, "RU");

    create_multiple_players_auto();

    for (int i = 0; i < 1; i++) {
        print_questions_matrix();
        cout << "\n";

        int row, col;
        cout << "Введите строку и столбец вопроса (0-4 0-4): ";
        cin >> row >> col;

        if (i > 0 && (i + 1) % 6 == 0) {
            cout << "\n=== АУКЦИОН! ===\n";
            conduct_auction();
            cout << "\nАукцион завершен! Продолжаем игру...\n";
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
            continue;
        }

        if (i > 0 && (i + 1) % 10 == 0) {
            cout << "\n=== КОТ В МЕШКЕ! ===\n";
            transfer_cat_question();
            cout << "\nКот в мешке завершен! Продолжаем игру...\n";
            cout << "Нажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
            continue;
        }

        handleQuestion(row, col);
        setQuestionFlag(row, col, false);
    }

    play_random_round();

    system("cls");
    show_final_results();
}