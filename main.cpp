#include "header.h"

#define endl_x2 endl << endl

int opponent_score = 0;
int my_score = 0;

int main() {

    int continue_or_not = 0;

    do{
        bool end_flag = false;
        int decision;
        grid *my_grid = new grid();
        grid *oppenent_grid = new grid();

        reload_vector();
        //test
        pair<byte, byte> a(10, 10);
        create_strategy(a);

        const int size = 10;
        bool opponent_game_layout[size][size];
        bool my_game_layout[size][size];
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                opponent_game_layout[i][j] = false;
                my_game_layout[i][j] = false;
            }
        }

        add_ships_to_grid_automatically(oppenent_grid);

        cout << "Moj wyniki: " << my_score << endl;
        cout << "Wynik przeciwnika: " << opponent_score << endl << endl;

        do{
            cout << "W jaki sposob chesz rozmiescic statki?" << endl;
            cout << "[1] Manualny." << endl;
            cout << "[2] Automatyczny." << endl;
            cout << "--------------------------------------" << endl;
            cout << "[3] Wyjscie." << endl;
            cout << "[4] Zapisz." << endl;
            cout << "[5] Wczytaj." << endl;

            cin >> decision;

            switch (decision){
                case 1:
                    add_ships_to_grid_manually(my_grid);
                    break;
                case 2:
                    add_ships_to_grid_automatically(my_grid);
                    break;
                case 3:
                    exit(1);
                case 4:
                    //Przykladowa sciezka do pliku
                    save(my_score, opponent_score, R"(D:\Programowanie\C++\ProjektC++\Statki\save.txt)");
                    break;
                case 5:
                    //Przykladowa sciezka do pliku
                    load(my_score, opponent_score, R"(D:\Programowanie\C++\ProjektC++\Statki\save.txt)");
                    break;
                default:
                    cout << "Brak takiej opcji." << endl;
                    break;
            }
        }while(!(decision == 1 || decision == 2));

        do{
            print_my_grid(my_grid->get_ship_layout(), grid::size, my_game_layout);
            cout << endl_x2;
            print_opponent_grid(oppenent_grid->get_ship_layout(), grid::size, opponent_game_layout);
            cout << endl_x2;

            while(my_shot(oppenent_grid, opponent_game_layout));
            while(opponent_shot(my_grid->get_ship_layout(), my_game_layout));

            if(was_game_done(my_grid->get_ship_layout(), my_game_layout)){
                cout << "Przeciwnik wygral runde." << endl;
                opponent_score++;
                end_flag = true;

                delete my_grid;
                delete oppenent_grid;
            }
            else if(was_game_done(oppenent_grid->get_ship_layout(), opponent_game_layout)){
                cout << "Wygrales." << endl;
                my_score++;
                end_flag = true;

                delete my_grid;
                delete oppenent_grid;
            }
        }while(!end_flag);

        cout << "Czy chcesz kontynuowac gre?" << endl;
        cout << "[1] Tak." << endl;
        cout << "[2] Nie." << endl;

        cin >> continue_or_not;

    }while(continue_or_not == 1);

    return 0;
}