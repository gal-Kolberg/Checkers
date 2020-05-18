#include "Question_4.h"
#include "Question_3.h"
#include "Question_2.h"
#include "Question_1.h"

void UpdateBoardAfterCaptureToLeft(checkersPos* CurrPos, Board board, int FlipSign) {
	board[(CurrPos->row - '0') + FlipSign][(CurrPos->col - '0') + 1] = ' ';
}

void UpdateBoardAfterCaptureToRight(checkersPos* CurrPos, Board board, int FlipSign) { 
	board[(CurrPos->row - '0') + FlipSign][(CurrPos->col - '0') - 1] = ' ';
}

void UpdateBoardAfterCaptureTurn(SingleSourceMoveList* BestMove, Board board, Player player) {
	int i, FlipSign = 1;
	checkersPos* PrevPos = BestMove->head->position; // Save the previous position of the "soldier"
	SingleSourceMovesListCell* temp = BestMove->head; // Save the current position of the "soldier"
	board[BestMove->head->position->row - '0'][BestMove->head->position->col - '0'] = ' '; // Update the starting position of the turn
	if (player == 'T') // If the current player is 'T'
		FlipSign *= -1; // Update variable for continue updating board
	for (i = 0; i <= BestMove->tail->captures; i++)
	{ // Runs untill the end of the turn
		if (temp->position->col < PrevPos->col) // If the next move is capture to the left
			UpdateBoardAfterCaptureToLeft(temp->position, board,FlipSign);
		else if (temp->position->col > PrevPos->col) // If the next move is capture to the right
			UpdateBoardAfterCaptureToRight(temp->position, board,FlipSign);
		PrevPos = temp->position; // // Promote the previous position of the "soldier"
		temp = temp->next; // Promote the current position of the "soldier"
	}
	board[BestMove->tail->position->row - '0'][BestMove->tail->position->col - '0'] = player; // Update the finishing position of the turn
}

void UpdateBoardAfterSimpleTurn(SingleSourceMoveList* BestMove, Board board, Player player) {
	board[BestMove->head->position->row - '0'][BestMove->head->position->col - '0'] = ' '; // Put in the stating possition ' ' 
	board[BestMove->tail->position->row - '0'][BestMove->tail->position->col - '0'] = player; // Put in the last possition 'B'/'T'
}

void PrintMove(SingleSourceMoveList* BestMove, Board board) { // Print the given move according to the given rules
	int i = 0;
	unsigned short captures = BestMove->tail->captures;
	char *CurrMove = (char*)malloc((sizeof(char) * captures * 4) + 7); // Allocate memory for size of the move  
	AllocationCheck(CurrMove); // Check the allocation
	SingleSourceMovesListCell* temp = BestMove->head;
	CurrMove[i++] = temp->position->row - '0' + 'A'; // Insert the start position 
	CurrMove[i++] = temp->position->col + 1; // See above
	temp = temp->next; // Promote the "index"
	while (temp != NULL) { // Runs untill the end of the move
		CurrMove[i++] = '-'; // After each move, insert the arrow
		CurrMove[i++] = '>';
		CurrMove[i++] = temp->position->row + -'0' + 'A'; // Than insert the next position 
		CurrMove[i++] = temp->position->col + 1; // See above
		temp = temp->next; // Promote the "index"
	}
	CurrMove[i] = '\0';
	if (board[BestMove->tail->position->row - '0'][BestMove->tail->position->col - '0'] == 'T') // Check which is the current player 
		printf("player TOP_DOWN's turn\n");
	else
		printf("player BOTTOM_UP's turn\n");
	printf("%s\n", CurrMove); // Print the turn
	free(CurrMove); // Free move
}

void FindBestMove(MultipleSourceMovesList* List, Board board, Player player) {
	if (List->head == NULL) {
		printf("Player %c dosen't have any more pieces.\n", player);
		return;
	}
	MultipleSourceMovesListCell* temp = List->head; // Variable that help me run on the list
	SingleSourceMoveList* BestMove = temp->single_source_moves_list; // Variable for the best move possible
	unsigned short MaxCapture = 0;
	while (temp != NULL) { // Runs untill the end of the moves list
		if (temp->single_source_moves_list->tail->captures > 0) // If the current move is capture move
			if (temp->single_source_moves_list->tail->captures > MaxCapture) { // If the current move is "better" than all moves that came before
				MaxCapture = temp->single_source_moves_list->tail->captures; // Update the variable
				BestMove = temp->single_source_moves_list; // Save the best move
			}
		temp = temp->next; // Promote the "index"
	}
	if (MaxCapture > 0 || BestMove->tail->captures > 0) // If there was a capturing move
		UpdateBoardAfterCaptureTurn(BestMove, board, player); // Update the board after the turn
	else { // No capture move available, do the first simple move 
		temp = List->head;
		while (temp != NULL && BestMove->head->next == NULL) { // Find the first simple move
			BestMove = temp->single_source_moves_list; // Update the current move to be the best one
			temp = temp->next; // Promote the "index"
		}
		if(BestMove->head->next != NULL)
			UpdateBoardAfterSimpleTurn(BestMove, board, player); // Update simple move
		else {
			board[0][0] = 'X'; // Marking that there is no more moves
			printf("No more moves left for %c.\n", player);
			return;
		}
	}
	PrintMove(BestMove, board); // Print the best move according to the given rules
}

void FreeList(MultipleSourceMovesList* List) { // Free function
	MultipleSourceMovesListCell *curr1 = List->head;
	MultipleSourceMovesListCell *next1;
	SingleSourceMovesListCell *curr2; 
	SingleSourceMovesListCell *next2;
	if (curr1 == NULL) // Check if the list of all possible moves is empty
		return;
	while (curr1 != NULL) { // Free the list of all possible moves
		next1 = curr1->next; // Promote the next variable
		curr2 = curr1->single_source_moves_list->head;
		while (curr2 != NULL) { // Free the list of the best move of any given possible move
			next2 = curr2->next; // Promote the next variable
			free(curr2->position); // Free pos
			free(curr2); // Free node
			curr2 = next2; // Promote the "index"
		}
		free(curr1); // Free node
		curr1 = next1; // Promote the "index"
	}
}

void Turn(Board board, Player player) {
	MultipleSourceMovesList *List = FindAllPossiblePlayerMoves(board, player); // Using the last question to find all of the possible moves
	FindBestMove(List, board, player); // Between those moves, find the best one
	FreeList(List); // Free Lists after the turn has been made
}