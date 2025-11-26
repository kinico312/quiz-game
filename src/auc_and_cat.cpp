#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <vector>
#include "multiple_players.hpp"

using namespace std;

void conduct_auction() {
    vector<string> all_players = get_all_players();
    map<string, int> players;

    for (const auto& name : all_players) {
        players[name] = get_player_score(name);
    }

    int max_bid = -1;
    string winner = "";
    int winning_bid = 0;
    vector<string> passed_players;

    for (auto& player : players) {
        const string& player_name = player.first;
        int player_score = player.second;
        int bid;

        cout << "\n" << player_name << ", у вас " << player_score << " очков\n";
        cout << "Введите вашу ставку (0 - пас): ";
        cin >> bid;

        while (cin.fail() || bid < 0 || bid > player_score) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (bid < 0) {
                cout << "Ставка не может быть отрицательной! Введите снова: ";
            }
            else if (bid > player_score) {
                cout << "У вас недостаточно очков! Максимум: " << player_score << ". Введите снова: ";
            }
            else {
                cout << "Некорректная ставка! Введите число: ";
            }
            cin >> bid;
        }

        if (bid == 0) {
            passed_players.push_back(player_name);
            cout << player_name << " пасует.\n";
        }
        else {
            if (bid > max_bid) {
                max_bid = bid;
                winner = player_name;
                winning_bid = bid;
            }
            cout << player_name << " ставит " << bid << " очков.\n";
        }
    }

    if (max_bid == -1) {
        cout << "Все игроки пасуют! Аукцион не состоялся.\n";
        return;
    }

    switch_to_player(winner);
    div_score_to_current_player(winning_bid);

    cout << "С победителя " << winner << " списано " << winning_bid << " очков.\n";
    cout << "У " << winner << " осталось " << get_player_score(winner) << " очков.\n";
}

void transfer_cat_question() {
    vector<string> all_players = get_all_players();
    string current_player = get_current_player_name();

    cout << "=== КОТ В МЕШКЕ ===\n";
    cout << current_player << ", вам выпал вопрос 'Кот в мешке'!\n";
    cout << "Вы должны передать этот вопрос другому игроку.\n\n";

    vector<string> available_players;
    for (const auto& player : all_players) {
        if (player != current_player) {
            available_players.push_back(player);
        }
    }

    cout << "Доступные игроки для передачи:\n";
    for (int i = 0; i < available_players.size(); i++) {
        cout << i + 1 << ". " << available_players[i] << "\n";
    }

    int choice;
    cout << "\nВыберите игрока для передачи вопроса (1-" << available_players.size() << "): ";
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > available_players.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный выбор! Введите число от 1 до " << available_players.size() << ": ";
        cin >> choice;
    }

    string selected_player = available_players[choice - 1];
    cout << "\n" << current_player << " передает вопрос игроку " << selected_player << "!\n";

    switch_to_player(selected_player);

    cout << "Теперь " << selected_player << " отвечает на вопрос 'Кот в мешке'!\n";
}