#pragma once

#include "MainHeader.h"

void Turn(Board board, Player player);
void PrintMove(SingleSourceMoveList* BestMove, Board board);
void FindBestMove(MultipleSourceMovesList* List, Board board, Player player); 
void UpdateBoardAfterCaptureTurn(SingleSourceMoveList* BestMove, Board board, Player player);
void UpdateBoardAfterSimpleTurn(SingleSourceMoveList* BestMove, Board board, Player player);
void UpdateBoardAfterCaptureToLeft(checkersPos* CurrPos, Board board, int FlipSign);
void UpdateBoardAfterCaptureToRight(checkersPos* CurrPos, Board board, int FlipSign);
void FreeList(MultipleSourceMovesList* List);