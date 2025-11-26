#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include "multiple_players.hpp"

using namespace std;

namespace {
    vector<string> players;
    map<string, int> scores;
    int current_player_index = 0;
}

void create_user(const std::string& name) {
    players.push_back(name);
    scores[name] = 0;
}

void create_multiple_players_auto() {
    players = { "Игрок_1", "Игрок_2", "Игрок_3" };
    scores.clear();
    for (const auto& player : players) {
        scores[player] = 0;
    }
    current_player_index = 0;
}

const std::string& get_current_player_name() {
    return players[current_player_index];
}

int get_current_player_score() {
    return scores[players[current_player_index]];
}

int get_player_score(const std::string& name) {
    return scores[name];
}

std::vector<std::string> get_all_players() {
    return players;
}

void add_score_to_current_player(int points) {
    scores[players[current_player_index]] += points;
}

void switch_to_next_player() {
    current_player_index = (current_player_index + 1) % players.size();
}

void switch_to_player(const std::string& name) {
    auto it = find(players.begin(), players.end(), name);
    if (it != players.end()) {
        current_player_index = distance(players.begin(), it);
    }
}

void div_score_to_current_player(int points) {
    scores[players[current_player_index]] -= points;
    if (scores[players[current_player_index]] < 0) {
        scores[players[current_player_index]] = 0;
    }
}

void show_scoreboard() {
    cout << "==============================================\n";
    cout << "            ТАБЛИЦА РЕЗУЛЬТАТОВ\n";
    cout << "==============================================\n";

    vector<pair<string, int>> sorted_players;
    for (const auto& player : players) {
        sorted_players.push_back({ player, scores[player] });
    }

    sort(sorted_players.begin(), sorted_players.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

    cout << left << setw(20) << "Игрок" << setw(10) << "Очки" << "\n";
    cout << "----------------------------------------------\n";

    for (const auto& [name, score] : sorted_players) {
        string current_indicator = (name == get_current_player_name()) ? " ← текущий" : "";
        cout << left << setw(20) << name << setw(10) << score << current_indicator << "\n";
    }

    cout << "==============================================\n";
}