#include "play_hex.h"

void play_hex(){
    int size;
    string player_red, player_blue;

    // Select the game size
    cout << "Welcome the game of hax." << endl;
    cout << "Please insert the size of the board. The size should be more than 1." << endl;
    cin >> size;

    //  Select the players!
    // Create the viable options for player.
    vector<string> options; 
    options.push_back("RealHuman");
    options.push_back("StupidAI");

    // Intro Players
    cout << "Please select the players to be one of: ";
    for(auto player = options.begin(); player != options.end(); ++player) cout << *player << ", ";
    cout << endl;

    // Select Player Blue
    cout << "Your Selection for player Blue:" << endl;
    cin >> player_blue;

    // !!! Error check whether the input is correct.

    // Select Player Red
    cout << "Your Selection for player Red:" << endl;
    cin >> player_blue;

    // !!! Error check whether the input is correct!

    // Create the game
    Hex h(size, player_red, player_blue);

    // Run the game
    while(!h.game_over()){
        h.player_red_turn();

        h.print();

        h.player_blue_turn();

        h.print();

        // ... to do ...
        // to break the infinit loop at the moment:
        break;
    }
    if (h.player_blue_won()){
        cout << "Player Blue Won!" << endl;
    } else {
        if(h.player_red_won()){
            cout << "Player Red Won!" << endl;
        } else {
            cout << "This can't be! At least one player needs to have won!" << endl;
        }
    }
}