#pragma once

#include <string>
#include <vector>
#include <map>


void create_user(const std::string& name);
void create_multiple_players_auto();


const std::string& get_current_player_name();
int get_current_player_score();
int get_player_score(const std::string& name);
std::vector<std::string> get_all_players();


void add_score_to_current_player(int points);

void switch_to_next_player();
void switch_to_player(const std::string& name);
void div_score_to_current_player(int points);

void show_scoreboard();