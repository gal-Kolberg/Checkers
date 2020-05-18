#pragma once

#include "MainHeader.h"

void MakeEmptyMultipleMovesList(MultipleSourceMovesList* PlayerMoveList);  // Make the given list an empty one
int IsEmptyMoveList(MultipleSourceMovesList* lst); // Checks if the given list is empty or not
MultipleSourceMovesListCell* CreateNewListMultipleCell(Board board, checkersPos *pos, MultipleSourceMovesListCell* Next); // Create new list cell
void insertCellToMulipleListTail(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* NewCell); // Insert cell to tail of list
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player); // Main function that find all the possible move to current player