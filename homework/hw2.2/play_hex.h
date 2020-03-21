#ifndef PLAY_HEX_H
#define PLAY_HEX_H

#include<iostream>
#include<string>
#include<vector>

#include "hex.h"

using namespace std;

// Function interacting with the user and steering the game.
void play_hex();

// Just for fun: let the two monte carlo bots compete
// You have to call the function in main.
void bot_play();

#endif