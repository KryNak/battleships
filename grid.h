//
// Created by kryst on 2020-05-16.
//

#ifndef STATKI_GRID_H
#define STATKI_GRID_H

#include <cstddef>
#include <iostream>
#include <vector>

using std::vector;
typedef unsigned short int byte;
enum vertical_or_horizontal{vertical, horizontal};
enum class_of_ship{patrol_boat = 1,  destroyer, battleship, carrier};

class grid {
public:
    const static size_t size = 10;

    grid();
    ~grid();

    bool** get_ship_layout();
    vector<int> get_ship_codes_list();
    void reset_xy_position(int x, int y);

    bool add_patrol_boat(byte x, byte y);
    bool add_destroyer(byte x, byte y, vertical_or_horizontal v);
    bool add_battleship(byte x, byte y, vertical_or_horizontal v);
    bool add_carrier(byte x, byte y, vertical_or_horizontal v);

    bool is_sunk();

    static void set_amount(int &patrol_boats, int &destroyers, int &battleships, int &carriers);
private:
    bool check_ship_layout(byte x, byte y, class_of_ship type, vertical_or_horizontal v);
    bool set_ship_layout(byte x, byte y, class_of_ship type, vertical_or_horizontal v);
    bool contain(vector<int> temp, int element);

    int ship_code = 1;
    vector<int> ship_codes_list;

    byte amount_of_patrol_boat;
    byte amount_of_destroyers;
    byte amount_of_battleships;
    byte amount_of_carriers;

    bool** ship_layout;
    int** detailed_ship_layout;
};


#endif //STATKI_GRID_H
