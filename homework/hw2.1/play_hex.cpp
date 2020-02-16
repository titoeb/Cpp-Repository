#include "play_hex.h"

void play_hex(){
    int size;
    int player_red, player_blue;

    // Select the game size
    cout << "Welcome the game of hax." << endl;
    cout << "Please insert the size of the board. The size should be more than 1." << endl;
    cin >> size;

    // Intro Players
    cout << "Please select the players to be one of: 0: RealHuman, 1: StupidAI" << endl;
    // Select Player Blue
    cout << "Your Selection for player Blue:" << endl;
    cin >> player_blue;

    // Select Player Red
    cout << "Your Selection for player Red:" << endl;
    cin >> player_red;

    // !!! Error check whether the input is correct!

    // Create the game
    Hex h(size, player_red, player_blue);

    cout << "Player blue playes 'X', player red playes 'O'." << endl;

    // Run the game
    while(!h.game_over()){
        h.player_red_turn();

        h.print();

        h.player_blue_turn();

        h.print();
    }
    if (h.player_blue_won()){
        cout << "Player Blue Won!" << endl;
        h.print();
    } else {
        if(h.player_red_won()){
            cout << "Player Red Won!" << endl;
            h.print();
        } else {
            cout << "This can't be! At least one player needs to have won!" << endl;
        }
    }
}