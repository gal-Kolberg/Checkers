#include "Question_1.h"

SingleSourceMoveTreeNode* CreateNewSingleMoveNode(Board board, checkersPos *pos, int TotalCapsSoFar) { // Function that creates new node for the possible move tree
	SingleSourceMoveTreeNode *t = (SingleSourceMoveTreeNode*)malloc(sizeof(SingleSourceMoveTreeNode)); // Allocate the new node
	AllocationCheck(t); // Checks the allocation
	t->Pos = (checkersPos*)malloc(sizeof(checkersPos)); // Allocate the position field int the new node
	AllocationCheck(t->Pos); // Checks the allocation
	CopyBoard(board, t); // Copy board from previous node
	t->total_capture_so_far = TotalCapsSoFar + 1; // Add one to total capture so far field
	t->Pos->col = pos->col; // Copy position of column to new position 
	t->Pos->row = pos->row; // Copy position of row to new position 
	t->next_move[LEFT] = NULL; // Make the left next moves null
	t->next_move[RIGHT] = NULL; // Make the right next moves null
	return t;
}

SingleSourceMoveTreeNode *UpdateNodeToSimpleMove(SingleSourceMoveTreeNode* t, Board board, int branchSelect, char CurrPlayer) { // Update the received node to "simple move"
	char RowPos = t->Pos->row - '0';
	char ColPos = t->Pos->col - '0';
	int FlipSign = -1; // This variable help with updating according to which player it is now
	if (board[RowPos][ColPos] == 'T') // If the current player is 'T' 
		FlipSign *= -1; // Make FlipSign one, If it is not keep it minus one
	t->next_move[branchSelect]->board[RowPos][ColPos] = ' '; // Make the current position of the player empty, only command that is common to every possibly move
	if (branchSelect == LEFT) { // If the player chose to move to the left
		t->next_move[branchSelect]->Pos->row = t->Pos->row + FlipSign; // Update the next move position row 
		t->next_move[branchSelect]->Pos->col = t->Pos->col - 1; // Update the next move position column
		if (CurrPlayer == 'T') // If the current player is 'T'
			t->next_move[branchSelect]->board[RowPos+ FlipSign][ColPos - 1] = 'T'; // Update in the board the player to new positoin after simple move to the left
		else
			t->next_move[branchSelect]->board[RowPos + FlipSign][ColPos - 1] = 'B'; // Update in the board the player to new positoin after simple move to the left
		t->next_move[branchSelect]->total_capture_so_far = 0; // Setting the capture move so far to zero - it is a simple move not capture
		t->next_move[RIGHT] = NULL; // The user chose to move to the left, no possible move to the right
	} // The line that changes the new row location is the same in both of these options but different in the last one, so we couldn't merge those lines
	else if (branchSelect == RIGHT) { // If the player chose to move to the left
		t->next_move[branchSelect]->Pos->col = t->Pos->col + 1; // Update the next move position column
		t->next_move[branchSelect]->Pos->row = t->Pos->row + FlipSign; // Update the next move position row
		if (CurrPlayer == 'T') // If the current player is 'T'
			t->next_move[branchSelect]->board[RowPos + FlipSign][ColPos + 1] = 'T'; // Update in the board the player to new positoin after simple move to the right
		else
			t->next_move[branchSelect]->board[(RowPos)+ FlipSign][ColPos - 1] = 'B'; // Update in the board the player to new positoin after simple move to the left
		t->next_move[branchSelect]->total_capture_so_far = 0; // Setting the capture move so far to zero - it is a simple move not capture
		t->next_move[LEFT] = NULL; // The user chose to move to the right, no possible move to the left
	}
	else { // Else it is a possible move to the left AND to the right
		t->next_move[LEFT]->board[RowPos][ColPos] = ' '; // Update the new position in the left sub tree
		t->next_move[LEFT]->total_capture_so_far = 0; // Setting the capture move so far to zero - it is a simple move not capture
		t->next_move[RIGHT]->board[RowPos][ColPos] = ' '; // Update the new position in the rigth sub tree
		t->next_move[RIGHT]->total_capture_so_far = 0; // Setting the capture move so far to zero - it is a simple move not capture
		if (CurrPlayer == 'T') { // If the current player is 'T'
			t->next_move[LEFT]->board[RowPos + FlipSign][ColPos - 1] = 'T'; // Update the new position of the player in the left sub tree
			t->next_move[RIGHT]->board[RowPos + FlipSign ][ColPos + 1 ] = 'T'; // Update the new position of the player in the right sub tree
		}
		else {
			t->next_move[LEFT]->board[RowPos + FlipSign][ColPos - 1] = 'B'; // Update the new position of the player in the left sub tree
			t->next_move[RIGHT]->board[RowPos + FlipSign][ColPos + 1] = 'B'; // Update the new position of the player in the right sub tree
		}
		t->next_move[RIGHT]->Pos->col = t->Pos->col + 1; // Update the next move position column in right sub tree
		t->next_move[RIGHT]->Pos->row = t->Pos->row + FlipSign; // Update the next move position row in right sub tree
		t->next_move[LEFT]->Pos->row = t->Pos->row + FlipSign; // Update the next move position row in right sub tree
		t->next_move[LEFT]->Pos->col = t->Pos->col - 1; // Update the next move position column in left sub tree
	}
	return t;
}

int IsInBoardForT(checkersPos *pos,int place) {
	if (pos->col - '0' + place >= 0 && pos->col - '0' + place < BOARD_SIZE && pos->row - '0' + 1 >= 0 && pos->row - '0' + 1 < BOARD_SIZE)
		return 1;
	else 
		return 0;
}

int CheckNextStepForT(Board board, checkersPos *Pos) {
	time_t t;
	srand((unsigned)time(&t));
	char RowPos = Pos->row - '0';
	char ColPos = Pos->col - '0';
	int res = NO_POSSIBLE_MOVE;
	if (IsInBoardForT(Pos,1) && board[RowPos + 1][ColPos + 1] == ' ') // If possible right simple move
		res = RIGHT;
	if (IsInBoardForT(Pos,-1) && board[RowPos + 1][ColPos - 1] == ' ') { // If possible left simple move
		res = LEFT;
		if (IsInBoardForT(Pos,1) && board[RowPos + 1][ColPos + 1] == ' ') // If possible simple move left AND right
			res = rand() % 2; // Do random choose
	}
	if (board[RowPos + 1][ColPos - 1] == 'B') // If there is an opponent to the left
		if (ColPos - 2 >= 0 && RowPos + 2 < BOARD_SIZE && board[RowPos + 2][ColPos - 2] == ' ') // And if the capture to the left is "legal"
			res = 4; // four is equal to capture move to the left
	if (board[RowPos + 1][ColPos + 1] == 'B') // If there is an opponent to the right
		if (ColPos + 2 < BOARD_SIZE && (RowPos + 2 < BOARD_SIZE) && board[RowPos + 2][ColPos + 2] == ' ') { // And if the capture to the right is "legal"	
			res = 5; // five is equal to capture move to the right
			if (board[RowPos + 1][ColPos - 1] == 'B') // Same check for capture to the left
				if (ColPos - 2 >= 0 && RowPos + 2 < BOARD_SIZE && board[RowPos + 2][ColPos - 2] == ' ') // Check first for memory leak
					res = 6; // Six is equal to capture move to the left and to the right
		}
	return res; // If the function got here, after the "loop of fire", so there is no possible move
}

int IsInBoardForB(checkersPos *pos, int place) {
	if (pos->col - '0' + place >= 0 && pos->col - '0' + place < BOARD_SIZE && pos->row - '0' - 1 >= 0 && pos->row - '0' - 1 < BOARD_SIZE)
		return 1;
	else
		return 0;
}

int CheckNextStepForB(Board board, checkersPos *Pos) {
	time_t t;
	srand((unsigned)time(&t));
	char RowPos = Pos->row - '0';
	char ColPos = Pos->col - '0';
	int res = NO_POSSIBLE_MOVE;
	if (IsInBoardForB(Pos,1) && board[RowPos - 1][ColPos + 1] == ' ') // If possible right simple move
		res = RIGHT;
	if (IsInBoardForB(Pos,-1) && board[RowPos - 1][ColPos - 1] == ' ') { // If possible left simple move
		res = LEFT;
		if (IsInBoardForB(Pos,1) && board[RowPos - 1][ColPos + 1] == ' ')
			res = rand() % 2; // Do random choose
	}
	if (board[RowPos - 1][ColPos - 1] == 'T') // If there is an opponent to the left
		if (ColPos - 2 >= 0 && 0 <= RowPos - 2 && board[RowPos - 2][ColPos - 2] == ' ') // And if the capture to the left is "legal"
			res = 4; // four is equal to capture move to the left
	if (board[RowPos - 1][ColPos + 1] == 'T') // If there is an opponent to the right
		if ((0 <= RowPos - 2 && ColPos + 2 < BOARD_SIZE) && board[RowPos - 2][ColPos + 2] == ' ') { // And if the capture to the right is "legal"	
			res = 5; // five is equal to capture move to the right
			if (board[RowPos - 1][ColPos - 1] == 'T') // Same check for capture to the left
				if (ColPos - 2 >= 0 && 0 <= RowPos - 2 && board[RowPos - 2][ColPos - 2] == ' ')// check fisst for mem leak
					res = 6; // six is equal to capture move to the left and to the right
		}
	return res; // If the function got here, after the "loop of fire", so there is no possible move
}

int CheckNextStep(Board board, checkersPos *Pos, char CurrPlayer) { // This function checks what is the next possible move there is a priority to capturing move
	if (CurrPlayer == 'T') // If the current player is 'T'
		return CheckNextStepForT(board, Pos);
	return CheckNextStepForB(board, Pos);
}

void UpdateNodeAfterCapture(SingleSourceMoveTreeNode *t, Board board, int BranchSelect, char CurrPlayer) { // This function update the node after a capture move
	char RowPos = t->Pos->row - '0';
	char ColPos = t->Pos->col - '0';
	int FlipSign = -1; // This variable help with updating according to which player it is now
	if (CurrPlayer == 'T') // If the current player is 'T' 
		FlipSign *= -1; // Make FlipSign one, If it is not keep it minus one
	if (BranchSelect == LEFT) { // If the capture is to the left
		if (CurrPlayer == 'T') // If the current player is 'T'
			t->board[RowPos + (2 * FlipSign)][ColPos - 2] = 'T'; // Update the player new positon in the board after capture
		else
			t->board[RowPos + (2 * FlipSign)][ColPos - 2] = 'B'; // Update the player new positon in the board after capture
		t->board[t->Pos->row][t->Pos->col] = ' '; // Update  old location in the board to empty
		t->board[RowPos + FlipSign][ColPos - 1] = ' '; // Update the captured piece in the board to empty
		t->Pos->col = t->Pos->col - 2; // Update the player position column in the node
		t->Pos->row = t->Pos->row + (2 * FlipSign); // Update the player position row in the node
	}
	if (BranchSelect == RIGHT) { // If capture is to the right
		if (CurrPlayer == 'T') // If the current player is 'T'
			t->board[RowPos + (2 * FlipSign)][ColPos + 2] = 'T'; // Update the player new positon in the board after capture
		else
			t->board[RowPos + (2 * FlipSign)][ColPos + 2] = 'B'; // Update the player new positon in the board after capture
		t->board[RowPos][ColPos] = ' '; // Update  old location in the board to empty
		t->board[RowPos + FlipSign][ColPos + 1] = ' '; // Update the captured piece in the board to empty
		t->Pos->col = (t->Pos->col + 2); // Update the player position column in the node
		t->Pos->row = t->Pos->row + (2 * FlipSign); // Update the player position row in the node
	}
}

SingleSourceMoveTreeNode* FindSingleSourceMoveRec(SingleSourceMoveTreeNode *t, Board board, char CurrPlayer) { // Function that create the the tree that represent all the possible move of the current "soldier"
	int NextMove = CheckNextStep(board, t->Pos, CurrPlayer); // Check what kind of move is the next one, priority to capturing move
	if (NextMove == LEFT && t->total_capture_so_far == 0) // If the next move is a simple move(to left) and there was not any capures before
	{
		t->next_move[LEFT] = CreateNewSingleMoveNode(board, t->Pos, -1); // Create new node in the left sub tree
		return t = UpdateNodeToSimpleMove(t, board, LEFT, CurrPlayer); // Return the updatated move after the simple move to the left
	}
	if (NextMove == RIGHT && t->total_capture_so_far == 0) // Ifthe next move is simple move(to right) and there was not any capures before
	{
		t->next_move[RIGHT] = CreateNewSingleMoveNode(board, t->Pos, -1); // Create new node in the right sub tree
		return t = UpdateNodeToSimpleMove(t, board, RIGHT, CurrPlayer); // Return the updatated move after the simple move to the right
	}
	if (NextMove == BOTH && t->total_capture_so_far == 0) // If the next move is simple move(to right && right) and there was not any capures before
	{
		t->next_move[LEFT] = CreateNewSingleMoveNode(board, t->Pos, -1); // Create new node in the left sub tree
		t->next_move[RIGHT] = CreateNewSingleMoveNode(board, t->Pos, -1); // Create new node in the right sub tree
		return t = UpdateNodeToSimpleMove(t, board, BOTH, CurrPlayer); // Return the updatated move after the simple move of both moves
	}
	if (NextMove == 4) { // if the next move is capturing move to the left
		t->next_move[LEFT] = CreateNewSingleMoveNode(board, t->Pos, t->total_capture_so_far); // Create new node in the left sub tree
		UpdateNodeAfterCapture(t->next_move[LEFT], board, LEFT, CurrPlayer); // Update capturing move
		t->next_move[RIGHT] = NULL; // No next move to the right
		t->next_move[LEFT] = FindSingleSourceMoveRec(t->next_move[LEFT], board, CurrPlayer); // Recursion call to find all the possible move after the captuing move to the left
	}
	if (NextMove == 5) { // If the next move if capturing move to the right
		t->next_move[RIGHT] = CreateNewSingleMoveNode(board, t->Pos, t->total_capture_so_far); // Create new node in the right sub tree
		UpdateNodeAfterCapture(t->next_move[RIGHT], board, RIGHT, CurrPlayer); // Update capturing move
		t->next_move[LEFT] = NULL; // No next move to the left
		t->next_move[RIGHT] = FindSingleSourceMoveRec(t->next_move[RIGHT], board, CurrPlayer); // Recursion call to find all the possible move after the captuing move to the right
	}
	if (NextMove == 6) { // If the next move is capture move to left AND right
		t->next_move[LEFT] = CreateNewSingleMoveNode(board, t->Pos, t->total_capture_so_far); // Create new node in the left sub tree
		UpdateNodeAfterCapture(t->next_move[LEFT], board, LEFT, CurrPlayer); // Update capturing move
		t->next_move[LEFT] = FindSingleSourceMoveRec(t->next_move[LEFT], board, CurrPlayer); // Recursion call to find all the possible move after the captuing move to the left
		t->next_move[RIGHT] = CreateNewSingleMoveNode(board, t->Pos, t->total_capture_so_far); // Create new node in the right sub tree
		UpdateNodeAfterCapture(t->next_move[RIGHT], board, RIGHT, CurrPlayer); // Update capturing move
		t->next_move[RIGHT] = FindSingleSourceMoveRec(t->next_move[RIGHT], board, CurrPlayer); // Recursion call to find all the possible move after the captuing move to the right
	}
	return t;
}

SingleSourceMoveTree* FindSingleSourceMove(SingleSourceMoveTreeNode *t, Board board, checkersPos *src) { // This function finds all the possible moves of the current "soldier"
	if (board[src->col][src->row] == ' ') // If the given position is empty - return
		return NULL; 
	char CurrPlayer = t->board[t->Pos->row - '0'][t->Pos->col - '0'];
	SingleSourceMoveTree* T = (SingleSourceMoveTree*)malloc(sizeof(SingleSourceMoveTree)); // Allocate the tree
	AllocationCheck(T); // Check the allocation
	t->total_capture_so_far = 0; // Update the current capture - zero
	T->source = FindSingleSourceMoveRec(t, board, CurrPlayer); // Build that tree using recursion function
	return T;
}