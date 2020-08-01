//
// Created by kryst on 2020-05-18.
//

#include "header.h"

vector<pair<byte, byte>> vec;
vector<pair<byte,byte>> future_moves;

void reload_vector(){

    while(!vec.empty()){
        vec.erase(vec.begin());
    }

    for(int i = 0; i < grid::size; i++){
        for(int j = 0 ; j < grid::size; j++){

            pair<byte, byte> temp;
            temp.first = i;
            temp.second = j;

            vec.push_back(temp);
        }
    }

}

void ask_about_coordinates(int a){
    switch(a){
        case 1:
            cout << "Podaj wspolrzedna [x]" << endl;
            break;
        case 2:
            cout << "Podaj wspolrzedna [y]" << endl;
            break;
        case 3:
            cout << "Dodac statek pionowo czy poziomo? [1] -pionowo, [2] -poziomo." << endl;
            break;
        case 4:
            cout << "Polecenie niemozliwe do zrealizowania. Prosze powtorzyc akcje." << endl;
    }

}


void add_ships_to_grid_manually(grid *layout){
    int amount_of_patrol_boats, amount_of_destroyers, amount_of_battleships, amount_of_carriers;
    grid::set_amount(amount_of_patrol_boats, amount_of_destroyers, amount_of_battleships, amount_of_carriers);

    int x, y, v;
    int choice;
    bool actionFlag;
    vertical_or_horizontal vh;

    do{
        actionFlag = false;

        print_my_grid(layout->get_ship_layout(), grid::size);

        cout << "[1] Dodaj patrol boat. ( Pozostalo [" << amount_of_patrol_boats << "] )" << endl;
        cout << "[2] Dodaj destroyer. ( Pozostalo [" << amount_of_destroyers << "] )" << endl;
        cout << "[3] Dodaj battleship. ( Pozostalo [" << amount_of_battleships << "] )" << endl;
        cout << "[4] Dodaj carrier. ( Pozostalo [" << amount_of_carriers << "] )" << endl;

        cin >> choice;

        ask_about_coordinates(1);
        cin >> x;
        ask_about_coordinates(2);
        cin >> y;
        if(choice != 1) {
            ask_about_coordinates(3);
            cin >> v;
            vh = v == 1? vertical : horizontal;
        }

        switch(choice){
            case 1:
                actionFlag = layout -> add_patrol_boat(x, y);
                if(actionFlag) amount_of_patrol_boats--;
                else ask_about_coordinates(4);
                break;
            case 2:
                actionFlag = layout -> add_destroyer(x, y, vh);
                if(actionFlag) amount_of_destroyers--;
                else ask_about_coordinates(4);
                break;
            case 3:
                actionFlag = layout -> add_battleship(x, y, vh);
                if(actionFlag) amount_of_battleships--;
                else ask_about_coordinates(4);
                break;
            case 4:
                actionFlag = layout -> add_carrier(x, y, vh);
                if(actionFlag) amount_of_carriers--;
                else ask_about_coordinates(4);
                break;
            default:
                ask_about_coordinates(4);
                break;
        }

    }while(amount_of_battleships || amount_of_carriers || amount_of_destroyers || amount_of_patrol_boats);
}
void add_ships_to_grid_automatically(grid *layout){
    int amount_of_patrol_boats, amount_of_destroyers, amount_of_battleships, amount_of_carriers;
    grid::set_amount(amount_of_patrol_boats, amount_of_destroyers, amount_of_battleships, amount_of_carriers);

    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(1.0, 10.99999);

    do{
        bool is_finished = layout -> add_patrol_boat(dist(mt), dist(mt));
        if(is_finished) amount_of_patrol_boats--;
    }while(amount_of_patrol_boats);

    do{
        vertical_or_horizontal v = dist(mt) > 5 ? vertical : horizontal;
        bool is_finished = layout -> add_destroyer(dist(mt), dist(mt), v);
        if(is_finished) amount_of_destroyers--;
    }while(amount_of_destroyers);

    do{
        vertical_or_horizontal v = dist(mt) > 5  ? vertical : horizontal;
        bool is_finished = layout -> add_battleship(dist(mt), dist(mt), v);
        if(is_finished) amount_of_battleships--;
    }while(amount_of_battleships);

    do{
        vertical_or_horizontal v = dist(mt) > 5  ? vertical : horizontal;
        bool is_finished = layout -> add_carrier(dist(mt), dist(mt), v);
        if(is_finished) amount_of_carriers--;
    }while(amount_of_carriers);
}

bool opponent_shot(bool** ship_layout, bool game_layout[][10]){
    random_device rd;
    mt19937 mt(rd());

    //random shooting
    if(future_moves.empty()){
        double range_up_to = vec.size() - 0.00001;
        uniform_real_distribution<double> dist(0, range_up_to);

        int rand_index = dist(mt);
        pair<byte, byte> temp = vec.at(rand_index);
        vec.erase(vec.begin() + rand_index);

        game_layout[temp.first][temp.second] = true;

        if(ship_layout[temp.first][temp.second]){
            create_strategy(temp);
            return true;
        }
        return false;
    }

    //strategy shooting
    else{
        double range_up_to = future_moves.size() - 0.00001;
        uniform_real_distribution<double> dist(0, range_up_to);

        int rand_index = dist(mt);
        pair<byte, byte> temp = future_moves.at(rand_index);
        future_moves.erase(future_moves.begin() + rand_index);

        game_layout[temp.first][temp.second] = true;

        return ship_layout[temp.first][temp.second];

    }


}

bool my_shot(grid* opponent_grid, bool game_layout[][10]){
    bool endFlag = false;
    int x, y;

    if(opponent_grid->get_ship_codes_list().empty())
        return false;

    cout << "Podaj wspolrzedne strzalu: " << endl;

    while(!endFlag){
        ask_about_coordinates(1);
        cin >> x;
        ask_about_coordinates(2);
        cin >> y;

        bool valid_x = x <= 10 && x >= 1;
        bool valid_y = y <= 10 && y >= 1;
        if(valid_x && valid_y) {

            if(game_layout[y - 1][x - 1]){
                cout << "Juz tu strzelales. Powtorz strzal." << endl;
                return true;
            }

            game_layout[y - 1][x - 1] = true;

            if(opponent_grid->get_ship_layout()[y - 1][x - 1]){

                opponent_grid->reset_xy_position(y - 1, x - 1);

                if(opponent_grid->is_sunk()){
                    cout << endl;
                    print_opponent_grid(opponent_grid->get_ship_layout(), grid::size, game_layout);
                    cout << endl;
                    cout << "Trafiony, zatopiony! Powtorz strzal." << endl;
                }else{
                    cout << endl;
                    print_opponent_grid(opponent_grid->get_ship_layout(), grid::size, game_layout);
                    cout << endl;
                    cout << "Trafiles! Powtorz strzal." << endl;
                }

                return true;
            } else {
                cout << "Nie trafiles." << endl;
                endFlag = true;
            }

        }
        else cout << "Zle wspolrzedne. Powtorz podanie koorydnatow." << endl;
    }

    return false;
}

bool was_game_done(bool** ship_layout, bool game_layout[][10]){
    
    int ship_score = 0, ship_and_game_score = 0;
    
    for(int i = 0; i < grid::size; i++){
        for(int j = 0; j < grid::size; j++){
            
            if(ship_layout[i][j]){
                ship_score++;
            }

            if(ship_layout[i][j] && game_layout[i][j]){
                ship_and_game_score++;
            }
            
        }
    }

    return ship_score == ship_and_game_score;
}

void save(int my_score, int opponent_score, string path){

    std::fstream saver(path);
    saver << "Moj wyniki: " << my_score << endl;
    saver << "Wynik przeciwnika: " << opponent_score << endl;
    saver.close();

}
void load(int& my_score, int& opponent_score, string path){

    std::fstream loader;

    loader.open(path);
    string linia;
    int scoreTab[2];

    int counter = 0;
    do
    {
        getline(loader, linia);
        cout << linia << endl;

        std::regex pattern( "[0-9]+" );
        std::smatch match;
        if( regex_search( linia, match, pattern ) ){
            scoreTab[counter++] = std::stoi(match[0]);
        }
    }
    while(linia != "");

    loader.close();

    my_score = scoreTab[0];
    opponent_score = scoreTab[1];
}

void create_strategy(pair<byte,byte> target_point){

    //left
    for(int i = 1; i <= 3 && target_point.second - i >= 0; i++){
        pair<byte, byte> temp(target_point.first, target_point.second - i);
        vector<pair<byte, byte>>::iterator iterator = find(vec.begin(), vec.end(), temp);
        if( iterator != vec.end()){
            vec.erase(vec.begin() + std::distance(vec.begin(), iterator));
            future_moves.push_back(temp);
        }
    }

    //right
    for(int i = 1; i <= 3 && target_point.second + i < 10; i++){
        pair<byte, byte> temp(target_point.first, target_point.second + i);
        vector<pair<byte, byte>>::iterator iterator = find(vec.begin(), vec.end(), temp);
        if( iterator != vec.end()){
            vec.erase(vec.begin() + std::distance(vec.begin(), iterator));
            future_moves.push_back(temp);
        }
    }

    //down
    for(int i = 1; i <= 3 && target_point.first + i < 10; i++){
        pair<byte, byte> temp(target_point.first + i, target_point.second);
        vector<pair<byte, byte>>::iterator iterator = find(vec.begin(), vec.end(), temp);
        if( iterator != vec.end()){
            vec.erase(vec.begin() + std::distance(vec.begin(), iterator));
            future_moves.push_back(temp);
        }
    }

    //up
    for(int i = 1; i <= 3 && target_point.second - i >= 0; i++){
        pair<byte, byte> temp(target_point.first - i, target_point.second);
        vector<pair<byte, byte>>::iterator iterator = find(vec.begin(), vec.end(), temp);
        if( iterator != vec.end()){
            vec.erase(vec.begin() + std::distance(vec.begin(), iterator));
            future_moves.push_back(temp);
        }
    }
}