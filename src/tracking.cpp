#include "head.hpp"
#include <mutex>
#include <vector>
#include <iostream>
#include <algorithm>

namespace {
    std::map<std::string, int> g_players; // список игроков с именем и очками
    std::string g_current_player = ""; // имя активного игрока
    std::vector<std::string> g_player_order; // порядок игроков
    size_t g_current_player_index = 0; // индекс текущего игрока в порядке
    std::mutex g_mutex;
}

// Создание пользователя без автоматического переключения
void create_user(const std::string& name)
{
    std::lock_guard<std::mutex> lock(g_mutex);
    g_players[name] = 0;
    g_player_order.push_back(name);

    // Если это первый игрок - делаем его текущим
    if (g_current_player.empty()) {
        g_current_player = name;
        g_current_player_index = 0;
    }
}

// Получить имя текущего игрока
const std::string& get_current_player_name() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_current_player;
}

// Получить очки текущего игрока
int get_current_player_score() {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_current_player.empty()) {
        return 0;
    }
    auto it = g_players.find(g_current_player);
    return (it != g_players.end()) ? it->second : 0;
}

// Добавить очки текущему игроку
void add_score_to_current_player(int points) {
    if (points <= 0) return;
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_current_player.empty()) {
        g_players[g_current_player] += points;
    }
}
void div_score_to_current_player(int points) {
    if (points <= 0) return;
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_current_player.empty()) {
        g_players[g_current_player] -= points;
    }
}

// Получить список всех игроков
std::vector<std::string> get_all_players() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_player_order;
}

// Переключиться на следующего игрока
void switch_to_next_player() {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_player_order.size() > 1) {
        g_current_player_index = (g_current_player_index + 1) % g_player_order.size();
        g_current_player = g_player_order[g_current_player_index];
    }
}

// Переключиться на конкретного игрока
void switch_to_player(const std::string& name) {
    std::lock_guard<std::mutex> lock(g_mutex);
    auto it = std::find(g_player_order.begin(), g_player_order.end(), name);
    if (it != g_player_order.end()) {
        g_current_player_index = std::distance(g_player_order.begin(), it);
        g_current_player = name;
    }
}

// Получить очки конкретного игрока
int get_player_score(const std::string& name) {
    std::lock_guard<std::mutex> lock(g_mutex);
    auto it = g_players.find(name);
    return (it != g_players.end()) ? it->second : 0;
}

void create_multiple_players_auto() {
    int num_players;

    std::cout << "Введите количество игроков: ";
    std::cin >> num_players;
    std::cin.ignore();

    for (int i = 0; i < num_players; i++) {
        std::string player_name = "Игрок_" + std::to_string(i + 1);
        create_user(player_name);
        std::cout << "Создан: " << player_name << "\n";
    }
}