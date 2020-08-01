//
// Created by kryst on 2020-05-18.
//

#ifndef STATKI_HEADER_H
#define STATKI_HEADER_H

#include "grid.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <regex>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::pair;
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
using std::string;

extern vector<pair<byte, byte>> vec;

//controller
void add_ships_to_grid_manually(grid *layout);
void add_ships_to_grid_automatically(grid *layout);
void ask_about_coordinates(int a);
bool opponent_shot(bool** ship_layout, bool game_layout[][10]);
bool my_shot(grid* opponent_grid, bool game_layout[][10]);
bool was_game_done(bool** ship_layout, bool game_layout[][10]);
void reload_vector();
void save(int my_score, int opponent_score, string path);
void load(int& my_score, int& opponent_score, string path);
void create_strategy(pair<byte, byte> target_point);

//viewer
void print_my_grid(bool** ship_layout, byte size, bool game_layout[][10]);
void print_my_grid(bool** ship_layout, byte size);
void print_opponent_grid(bool** ship_layout, byte size, bool game_layout[][10]);

#endif //STATKI_HEADER_H
