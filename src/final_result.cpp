#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "multiple_players.hpp"

using namespace std;

void show_final_results() {
    vector<string> all_players = get_all_players();

    vector<pair<string, int>> players_scores;
    for (const auto& player : all_players) {
        players_scores.push_back({ player, get_player_score(player) });
    }

    sort(players_scores.begin(), players_scores.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    cout << "\n";
    cout << "==============================================\n";
    cout << "             ФИНАЛЬНЫЕ РЕЗУЛЬТАТЫ\n";
    cout << "==============================================\n";
    cout << "\n";

    int max_score = players_scores[0].second;
    vector<string> winners;

    for (const auto& [player, score] : players_scores) {
        if (score == max_score) {
            winners.push_back(player);
        }
    }

    if (winners.size() == 1) {
        cout << "ПОБЕДИТЕЛЬ: " << winners[0] << "\n";
        cout << "Количество очков: " << max_score << "\n";
    }
    else {
        cout << "ПОБЕДИТЕЛИ (НИЧЬЯ): ";
        for (size_t i = 0; i < winners.size(); i++) {
            cout << winners[i];
            if (i < winners.size() - 1) {
                cout << ", ";
            }
        }
        cout << "\n";
        cout << "Количество очков: " << max_score << "\n";
    }

    cout << "\n";
    cout << "==============================================\n";
    cout << "           ИТОГОВАЯ ТАБЛИЦА\n";
    cout << "==============================================\n";

    cout << left << setw(20) << "Игрок"
        << setw(10) << "Очки"
        << "Место" << "\n";
    cout << "----------------------------------------------\n";

    for (size_t i = 0; i < players_scores.size(); i++) {
        string place;
        if (i == 0) {
            place = "1-е место";
        }
        else if (i == 1) {
            place = "2-е место";
        }
        else if (i == 2) {
            place = "3-е место";
        }
        else {
            place = to_string(i + 1) + "-е место";
        }

        cout << left << setw(20) << players_scores[i].first
            << setw(10) << players_scores[i].second
            << place << "\n";
    }

    cout << "==============================================\n";
    cout << "\nИГРА ЗАВЕРШЕНА! СПАСИБО ЗА ИГРУ!\n";
}