#include "head.hpp"
#include <mutex>

namespace {
    std::map<std::string, int> g_players; //список игроков с именем и очками
    std::string g_current_player = ""; //имя активного игрока
    std::mutex g_mutex;
}

void create_user(const std::string& name)
{
    std::lock_guard<std::mutex> lock(g_mutex);
    g_players[name] = 0;
    g_current_player = name; //делаем активным
}

const std::string& get_current_player_name() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_current_player;
}

int get_current_player_score()
{
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_current_player.empty())
    {
        return 0;
    }
    auto it = g_players.find(g_current_player);
    return (it != g_players.end()) ? it->second : 0;
}

void add_score_to_current_player(int points)
{
    if (points <= 0) return;
    std::lock_guard<std::mutex> lock(g_mutex);
    if (!g_current_player.empty())
    {
        g_players[g_current_player] += points;
    }
}