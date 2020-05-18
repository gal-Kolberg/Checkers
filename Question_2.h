#pragma once

#include "MainHeader.h"

void MakeEmptyList(SingleSourceMoveList* LongestPathList); // Make the given list an empty one
int IsEmpty(SingleSourceMoveList* lst); // Checks if the given list is empty or not
void insertNodeToHead(SingleSourceMoveList* lst, SingleSourceMovesListCell* NewCell); // Insert node to head of list
void insertDataToHeadList(SingleSourceMoveList* lst, unsigned short *captures, checkersPos *pos); // Function that insert a new node to the head of the list
void FindSingleSourceOptimalMovesRec(SingleSourceMoveTreeNode* t, SingleSourceMoveList* lst, unsigned short* MaxMoves); // Main recursion function
unsigned short FindThelongestpath(SingleSourceMoveTreeNode *t); // Recursion function calculate the longest capture path
void OnlySimpleMove(SingleSourceMoveTreeNode* t, SingleSourceMoveList* lst, int KindOfMove); // Update the list with simple move node
void ImpossibleMove(SingleSourceMoveTreeNode* t, SingleSourceMoveList* lst); // Making a list with only one node, the current position
SingleSourceMoveList* FindSingleSourceOptimalMoveS(SingleSourceMoveTree *moves_tree); // Main function to find the most optimal move
SingleSourceMovesListCell* CreateNewListNode(unsigned short Captures, checkersPos *pos, SingleSourceMovesListCell* Next); // Create new list node
void FreeMoveTree(SingleSourceMoveTree *moves_tree); // Calling the rec free function
void FreeMoveTreeRec(SingleSourceMoveTreeNode *node); // Freeing the Tree recursivle

