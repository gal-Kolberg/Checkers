#pragma once

#include "MainHeader.h"

void PrintBoard(Board board);
int IsWin(Board board, Player *player); // Find if a player has won in the last move
void SwitchPlayer(char* CurrPLayer); // Switch players
void PlayGame(Board board, Player starting_player);