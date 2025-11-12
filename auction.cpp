#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <vector>
#include "multiple_players.hpp"

void conduct_auction() {
    std::vector<std::string> all_players = get_all_players();
    std::map<std::string, int> players;

    for (const auto& name : all_players) {
        players[name] = get_player_score(name);
    }

    int max_bid = -1;
    std::string winner = "";
    int winning_bid = 0;
    std::vector<std::string> passed_players;

    for (auto& player : players) {
        const std::string& player_name = player.first;
        int player_score = player.second;
        int bid;

        std::cout << "\n" << player_name << ", у вас " << player_score << " очков\n";
        std::cout << "Введите вашу ставку: ";
        std::cin >> bid;

        while (std::cin.fail() || bid < 0 || bid > player_score) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (bid < 0) {
                std::cout << "Ставка не может быть отрицательной! Введите снова: ";
            }
            else if (bid > player_score) {
                std::cout << "У вас недостаточно очков! Максимум: " << player_score << ". Введите снова: ";
            }
            else {
                std::cout << "Некорректная ставка! Введите число: ";
            }
            std::cin >> bid;
        }

        if (bid == 0) {
            passed_players.push_back(player_name);
            std::cout << player_name << " пасует.\n";
        }
        else {
            if (bid > max_bid) {
                max_bid = bid;
                winner = player_name;
                winning_bid = bid;
            }
            std::cout << player_name << " ставит " << bid << " очков.\n";
        }
    }

    if (max_bid == -1) {
        std::cout << "Все игроки пасуют! Аукцион не состоялся.\n";
        return;
    }

    switch_to_player(winner);
    div_score_to_current_player(winning_bid);

    std::cout << "С победителя " << winner << " списано " << winning_bid << " очков.\n";
    std::cout << "У " << winner << " осталось " << get_player_score(winner) << " очков.\n";
}


void transfer_cat_question() {
    std::vector<std::string> all_players = get_all_players();
    std::string current_player = get_current_player_name();

    std::cout << "=== КОТ В МЕШКЕ ===\n";
    std::cout << current_player << ", вам выпал вопрос 'Кот в мешке'!\n";
    std::cout << "Вы должны передать этот вопрос другому игроку.\n\n";

    std::vector<std::string> available_players;
    for (const auto& player : all_players) {
        if (player != current_player) {
            available_players.push_back(player);
        }
    }

    std::cout << "Доступные игроки для передачи:\n";
    for (int i = 0; i < available_players.size(); i++) {
        std::cout << i + 1 << ". " << available_players[i] << "\n";
    }

    int choice;
    std::cout << "\nВыберите игрока для передачи вопроса (1-" << available_players.size() << "): ";
    std::cin >> choice;

    while (std::cin.fail() || choice < 1 || choice > available_players.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный выбор! Введите число от 1 до " << available_players.size() << ": ";
        std::cin >> choice;
    }

    std::string selected_player = available_players[choice - 1];
    std::cout << "\n" << current_player << " передает вопрос игроку " << selected_player << "!\n";

    switch_to_player(selected_player);

    std::cout << "Теперь " << selected_player << " отвечает на вопрос 'Кот в мешке'!\n";
}




