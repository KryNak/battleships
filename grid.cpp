//
// Created by kryst on 2020-05-16.
//

#include "grid.h"

byte amount_of_patrol_boat = 4;
byte amount_of_destroyers = 3;
byte amount_of_battleships = 2;
byte amount_of_carriers = 1;

grid::grid() {
    for(int i = 1; i <= 10; i++){
        ship_codes_list.push_back(i);
    }

    ship_layout = new bool*[10];
    detailed_ship_layout = new int*[10];

    for(int i = 0; i < size; i++){
        ship_layout[i] = new bool[10];
        detailed_ship_layout[i] = new int[10];
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){

            ship_layout[i][j] = false;
            detailed_ship_layout[i][j] = 0;

        }
    }
}

grid::~grid() {

    for(int i = 0; i < size; i++){
        delete [] ship_layout[i];
        delete [] detailed_ship_layout[i];
    }
    delete [] ship_layout;
    delete [] detailed_ship_layout;

}

bool** grid::get_ship_layout() {

    return ship_layout;

}

bool grid::add_patrol_boat(byte x, byte y){

    if(amount_of_patrol_boat <= 0) return false;
    if(!check_ship_layout(x, y, patrol_boat, horizontal))
        return false;
    if(!set_ship_layout(x, y, patrol_boat, horizontal))
        return false;

    --amount_of_patrol_boat;
    return true;
}
bool grid::add_destroyer(byte x, byte y, vertical_or_horizontal v){

    if(amount_of_destroyers <= 0) return false;
    if(!check_ship_layout(x, y, destroyer, v))
        return false;
    if(!set_ship_layout(x, y, destroyer, v))
        return false;

    --amount_of_destroyers;
    return true;
};
bool grid::add_battleship(byte x, byte y, vertical_or_horizontal v){

    if(amount_of_battleships <= 0) return false;
    if(!check_ship_layout(x, y, battleship, v))
        return false;
    if(!set_ship_layout(x, y, battleship, v))
        return false;

    --amount_of_battleships;
    return true;
};
bool grid::add_carrier(byte x, byte y, vertical_or_horizontal v){

    if(amount_of_carriers <= 0) return false;
    if(!check_ship_layout(x, y, carrier, v))
        return false;
    if(!set_ship_layout(x, y, carrier, v))
        return false;

    --amount_of_carriers;
    return true;
}

void grid::set_amount(int &patrol_boats, int &destroyers, int &battleships, int &carriers){
    patrol_boats = 4;
    destroyers = 3;
    battleships = 2;
    carriers = 1;
}

bool grid::set_ship_layout(byte x, byte y, class_of_ship type, vertical_or_horizontal v) {

    if(x - 1 > size || y - 1 > size || x - 1 < 0 || y - 1 < 0) return false;
    if(!check_ship_layout(x, y, type, v)) return false;

    if(v == vertical){
        if(y - 1 + type > size) return false;

        for(int i = y - 1; i < y - 1 + type; i++){
            for(int j = x - 1; j <= x - 1; j++){
                ship_layout[i][j] = true;
                detailed_ship_layout[i][j] = ship_code;
            }
        }


    } else if(v == horizontal){
        if(x - 1 + type > size) return false;

        for(int i = y - 1; i <= y - 1; i++){
            for(int j = x - 1; j < x - 1 + type; j++){
                ship_layout[i][j] = true;
                detailed_ship_layout[i][j] = ship_code;
            }
        }

    }

    ship_code++;
    return true;

}

bool grid::check_ship_layout(byte x, byte y, class_of_ship type, vertical_or_horizontal v){

    if(v == vertical){

        for(int i = y - 2; i < y + type; i++){
            for(int j = x - 2; j <= x; j++){
                if(i < 0 || i >= size || j < 0 || j >= size) continue;
                if(ship_layout[i][j]) return false;
            }
        }


    } else{

        for(int i = y - 2; i <= y; i++){
            for(int j = x - 2; j < x + type; j++){
                if(i < 0 || i >= size || j < 0 || j >= size) continue;
                if(ship_layout[i][j]) return false;
            }
        }

    }
    return true;
}

bool grid::is_sunk(){
    vector<int> temp;
    bool exit_flag;

    for(int k = 0; k < ship_codes_list.size(); k++){
        exit_flag = false;

        for(int i = 0; i < size && !exit_flag; i++){
            for(int j = 0; j < size && !exit_flag; j++){
                if(detailed_ship_layout[i][j] == ship_codes_list.at(k)){
                    temp.push_back(ship_codes_list.at(k));
                    exit_flag = true;
                }

            }
        }

    }

    for(int i = 0; i < ship_codes_list.size(); i++){

        if(!contain(temp, ship_codes_list.at(i))){
            ship_codes_list.erase(ship_codes_list.begin() + i);
            return true;
        }

    }

    return false;
}

bool grid::contain(vector<int> temp, int element){
    bool does_contain = false;

    for(int i = 0; i < temp.size(); i++){
        if(temp.at(i) == element) does_contain = true;
    }

    return does_contain;
}

void grid::reset_xy_position(int y, int x){
    
    detailed_ship_layout[y][x] = 0;
    
}

vector<int> grid::get_ship_codes_list(){

    return ship_codes_list;

}