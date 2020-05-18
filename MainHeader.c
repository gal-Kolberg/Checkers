#include "MainHeader.h"

void AllocationCheck(void *Pointer) { // Function that checks if the allocated pointer was successful
	if (!Pointer) {
		printf("Malloc ERROR");
		exit(MALLOC_ERROR_CODE);
	}
}

void CopyBoard(Board boart, SingleSourceMoveTreeNode* t) { // Function that copy every block in the given board to the board in the given node
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		if (i % 2 == 0) // Skip the irrelevant blocks
			j = 1;
		else
			j = 0;
		for (j = 0; j < BOARD_SIZE; j++)
			t->board[i][j] = boart[i][j];
	}
}