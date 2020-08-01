//
// Created by kryst on 2020-05-18.
//
#include "header.h"

void print_my_grid(bool** ship_layout, byte size){

    cout << "Pole Gry: Twoje. " << endl;

    for(int i = -1; i < size; i++){
        for(int j = -1; j < size; j++){
            if((i < 0 || j < 0) && i != -1) printf("%3d", i + 1);
            else if((i < 0 || j < 0) && i == -1) {
                if(j == -1) cout << "   ";
                else printf("%3d", j + 1);
            }
            else {
                if(!ship_layout[i][j]) printf("%3s", ".") ;
                else printf("%3s", "#");
            }
        }
        cout << endl;
    }

}

void print_my_grid(bool** ship_layout, byte size, bool game_layout[][10]){

    cout << "Pole Gry: Twoje. " << endl;

    for(int i = -1; i < size; i++){
        for(int j = -1; j < size; j++){
            if((i < 0 || j < 0) && i != -1) printf("%3d", i + 1);
            else if((i < 0 || j < 0) && i == -1) {
                if(j == -1) cout << "   ";
                else printf("%3d", j + 1);
            }
            else {
                if(ship_layout[i][j] == 0 && game_layout[i][j] == 1) printf("%3s", "*") ;
                else if(ship_layout[i][j] && game_layout[i][j]) printf("%3s", "!") ;
                else if(ship_layout[i][j] == 1 && game_layout[i][j] == 0) printf("%3s", "#");
                else printf("%3s", ".");
            }
        }
        cout << endl;
    }

}

void print_opponent_grid(bool** ship_layout, byte size, bool game_layout[][10]){

    cout << "Pole Gry: Przeciwnika. " << endl;

    for(int i = -1; i < size; i++){
        for(int j = -1; j < size; j++){
            if((i < 0 || j < 0) && i != -1) printf("%3d", i + 1);
            else if((i < 0 || j < 0) && i == -1) {
                if(j == -1) cout << "   ";
                else printf("%3d", j + 1);
            }
            else {
                if(ship_layout[i][j] == 0 && game_layout[i][j] == 1) printf("%3s", "*");
                else if(ship_layout[i][j] && game_layout[i][j]) printf("%3s", "!");
                else printf("%3s", ".");
            }
        }
        cout << endl;
    }

}