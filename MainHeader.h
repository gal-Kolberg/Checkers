#pragma once

#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR_CODE -1
#define BOARD_SIZE 8
#define LEFT 0
#define RIGHT 1
#define BOTH 2
#define NO_POSSIBLE_MOVE -1

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;

typedef struct  _checkersPos {
	char row;
	char col;
}checkersPos;

typedef struct  _SingleSourceMoveTreeNode {
	Board board;
	checkersPos *Pos;
	unsigned short total_capture_so_far;
	struct _SingleSourceMoveTreeNode *next_move[2];
}SingleSourceMoveTreeNode;

typedef struct _SingleSourceMoveTree {
	SingleSourceMoveTreeNode *source;
}SingleSourceMoveTree;

typedef struct _SingleSourceMovesListCell {
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMoveList {
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;
}SingleSourceMoveList;

typedef struct _multipleSourceMovesListCell {
	SingleSourceMoveList *single_source_moves_list;
	struct _multipleSourceMovesListCell *next;
}MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList {
	MultipleSourceMovesListCell *head;
	MultipleSourceMovesListCell *tail;
}MultipleSourceMovesList;

void AllocationCheck(void *Pointer);  // Function that checks if the allocated pointer was successful
void CopyBoard(Board board, SingleSourceMoveTreeNode* t);  // Function that copy every block in the given board to the board in the given node