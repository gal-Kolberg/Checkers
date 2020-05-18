#pragma once

#include "MainHeader.h"

void LoadBoard(char *filename, Board board);  // This function store the board from the file to the variable 
void StoreBoard(Board board, char *filename); // This function save the current board in the given file