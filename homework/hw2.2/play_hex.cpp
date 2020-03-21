#include "play_hex.h"

void play_hex(){
    int size;
    int player_red, player_blue;

    // Select the game size
    /*cout << "Welcome the game of hax." << endl;
    cout << "Please insert the size of the board. The size should be more than 1." << endl;
    cin >> size;*/
    size = 4;

    // Intro Players
    // This is stupid. The codes are defined in the PLAYER enum and could change...
    /*cout << "Please select the players to be one of: 0: RealHuman, 1: StupidAI" << endl;
    // Select Player Blue
    cout << "Your Selection for player Blue:" << endl;
    cin >> player_blue;

    // Select Player Red
    cout << "Your Selection for player Red:" << endl;
    cin >> player_red;*/

    player_red = 1;
    player_blue = 1; 

    // !!! Error check whether the input is correct!

    // Create the game
    Hex h(size, static_cast<Player>(player_red), static_cast<Player>(player_blue));

    cout << "Player blue playes 'X', player red playes 'O'." << endl;

    // Run the game
    while(!(h.red_won() || h.blue_won())){
        // The players make their move
        h.player_red_turn();
        h.player_blue_turn();

        // Show the board to the user
        h.print();
    }
    
    // Check who won the game
    if (h.blue_won()){
        cout << "Player Blue Won!" << endl;
        h.print();
    } else {
        if(h.red_won()){
            cout << "Player Red Won!" << endl;
            h.print();
        } else {
            cout << "This can't be! At least one player needs to have won!" << endl;
        }
    }
}