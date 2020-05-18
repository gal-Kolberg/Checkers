#include "Question_3.h"
#include "Question_2.h"
#include "Question_1.h"

void MakeEmptyMultipleMovesList(MultipleSourceMovesList* PlayerMoveList) { // Make the given list an empty one
	PlayerMoveList->head = PlayerMoveList->tail = NULL;
}

int IsEmptyMoveList(MultipleSourceMovesList* lst) { // Checks if the given list is empty or not
	return lst->head == NULL;
}

MultipleSourceMovesListCell* CreateNewListMultipleCell(Board board, checkersPos *pos, MultipleSourceMovesListCell* Next) { // Create new list cell
	SingleSourceMoveTreeNode *t;
	MultipleSourceMovesListCell* NewCell = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell)); // Allocate new node
	AllocationCheck(NewCell); // Checks the allocation
	NewCell->single_source_moves_list = (SingleSourceMoveList*)malloc(sizeof(SingleSourceMoveList)); // Allocate the best course of moves list
	AllocationCheck(NewCell->single_source_moves_list); // Checks the allocation
	MakeEmptyList(NewCell->single_source_moves_list); // Empty the list
	t = CreateNewSingleMoveNode(board, pos, -1); // Create the source of the tree that represent all of the possible moves
	NewCell->single_source_moves_list = FindSingleSourceOptimalMoveS(FindSingleSourceMove(t, board, pos)); // Build the best list using the function from question one and two
	NewCell->next = Next; // Make the node points to the next node
	return NewCell;
}

void insertCellToMulipleListTail(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* NewCell) { // Insert cell to tail of list
	if (IsEmptyMoveList(lst)) { // Checks if the list is empty
		lst->head = lst->tail = NewCell; // Make head and tail point to the same cell
	}
	else { // If the list is not empty
		lst->tail->next = NewCell; // Make the last cell Point to the new cell
		lst->tail = NewCell; // Make the last cell the tail of the list
	}
}

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) { // Main function that find all the possible move to current player
	int i, j;
	checkersPos CurrPos;
	MultipleSourceMovesList *list = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList)); // Create new multiple list
	AllocationCheck(list); // Check the allocation
	MakeEmptyMultipleMovesList(list); // Make the new multiple list empty
	for (i = 0; i < BOARD_SIZE; i++) { // Runs on every block in the board
		if (i % 2 == 0) // Skip the irrelevant blocks
			j = 1;
		else
			j = 0;
		for (; j < BOARD_SIZE; j += 2)
			if (board[i][j] == player) { // If the current block is relevant
				CurrPos.row = (char)i + '0'; // Update the current position variable
				CurrPos.col = (char)j + '0';
				insertCellToMulipleListTail(list, CreateNewListMultipleCell(board, &CurrPos, NULL)); // Make new multiple cell in the list
			}
	}
	return list; // Return updated list
}