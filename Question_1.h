#pragma once

#include "MainHeader.h"

SingleSourceMoveTreeNode* CreateNewSingleMoveNode(Board board, checkersPos *pos, int TotalCapsSoFar); // Function that creates new node for the possible move tree
SingleSourceMoveTreeNode *UpdateNodeToSimpleMove(SingleSourceMoveTreeNode* t, Board board, int branchSelect, char CurrPlayer); // Update the received node to "simple move"
int CheckNextStepForB(Board board, checkersPos *Pos);
int IsInBoardForB(checkersPos *pos, int place);
int CheckNextStepForT(Board board, checkersPos *Pos);
int IsInBoardForT(checkersPos *pos, int place);
int CheckNextStep(Board board, checkersPos *Pos, char CurrPlayer); // Check which step will be the next one
void UpdateNodeAfterCapture(SingleSourceMoveTreeNode *t, Board board, int BranchSelect, char CurrPlayer); // This function update the node after a capture move
SingleSourceMoveTreeNode* FindSingleSourceMoveRec(SingleSourceMoveTreeNode *t, Board board, char CurrPlayer); // Function that create the the tree that represent all the possible move of the current "soldier"
SingleSourceMoveTree* FindSingleSourceMove(SingleSourceMoveTreeNode *t, Board board, checkersPos *src); // This function finds all the possible moves of the current "soldier"