#include "Question_2.h"
#include "Question_1.h"

void MakeEmptyList(SingleSourceMoveList* LongestPathList) { // Make the given list an empty one
	LongestPathList->head = LongestPathList->tail = NULL;
}

int IsEmpty(SingleSourceMoveList* lst) { // Checks if the given list is empty or not
	return lst->head == NULL;
}

void insertNodeToHead(SingleSourceMoveList* lst, SingleSourceMovesListCell* NewCell) { // Insert node to head of list
	if (IsEmpty(lst)) { // Checks if the list is empty
		lst->head = lst->tail = NewCell; // Make head and tail point to the same cell
	}
	else { // If the list is not emptY
		NewCell->next = lst->head; // The new cell next is head
		lst->head = NewCell; // The head of the list points to the new cell
	}
}

void insertNodeToTail(SingleSourceMoveList* lst, SingleSourceMovesListCell* NewCell) { // Insert node to head of list
	if (IsEmpty(lst)) { // Checks if the list is empty
		lst->head = lst->tail = NewCell; // Make head and tail point to the same cell
	}
	else { // If the list is not empty
		lst->tail->next = NewCell; // Make the last cell points to the new cell
		lst->tail = NewCell; // Make the tail points to the new cell
	}
}

void insertDataToHeadList(SingleSourceMoveList* lst, unsigned short *captures, checkersPos *pos) { // Function that insert a new node to the head of the list
	SingleSourceMovesListCell* NewNode = CreateNewListNode(*captures, pos, NULL); // Making the new node with the desire value
	insertNodeToHead(lst, NewNode); // insert it to the head
	*(captures) = *(captures) - 1; // Update the number of captures after each node making
}

void FindSingleSourceOptimalMovesRec(SingleSourceMoveTreeNode* t, SingleSourceMoveList* lst, unsigned short* MaxMoves) { // Main recursion function
	// The idea is to build the list from the last cell to the first one in the list
	if (t == NULL) // If the current node points to NULL - return
		return;
	if (t->total_capture_so_far == *MaxMoves) { // If the total captures is equal to max moves (we got to the desire node)
		insertDataToHeadList(lst, MaxMoves, t->Pos); // Make new cell and insert to the start
		return;
	}
	else { // If we did not got to the desire node
		FindSingleSourceOptimalMovesRec(t->next_move[LEFT], lst, MaxMoves); // Search it in the sub left tree
		FindSingleSourceOptimalMovesRec(t->next_move[RIGHT], lst, MaxMoves); // Search it in the sub right tree
	}
	// This IF is making sure that we build the "next" (actually the new node will come before the current one) node correctly 
	// And not just any next node that we will encounter
	if (!IsEmpty(lst) && (t->Pos->col + 2 == lst->head->position->col || t->Pos->col - 2 == lst->head->position->col)) { // If the list is not empty and the head
		insertDataToHeadList(lst, MaxMoves, t->Pos); // Of the list is in "capturing distince" then make new node
		return;
	}
}

unsigned short FindThelongestpath(SingleSourceMoveTreeNode *t) { // Recursion function calculate the longest capture path
	if (t == NULL) // If the current node points to NULL - return
		return 0; 
	else {
		unsigned short leftsize = FindThelongestpath(t->next_move[LEFT]) + 1; // Check the longest path in the sub left tree
		unsigned short  rightsize = FindThelongestpath(t->next_move[RIGHT]) + 1; // Check the longest path in the sub right tree
		if (leftsize > rightsize) // Return the longer path
			return leftsize;
		else
			return rightsize;
	}
}

void OnlySimpleMove(SingleSourceMoveTreeNode* t, SingleSourceMoveList* lst, int KindOfMove) { // Update the list with simple move node
	checkersPos *CurrPos;
	SingleSourceMovesListCell* NewNode = CreateNewListNode(0, t->Pos, NULL); // Making the new node with the desire value
	insertNodeToTail(lst, NewNode);
	if (KindOfMove == LEFT) { // Simple move to the left
		CurrPos = t->next_move[LEFT]->Pos;
		SingleSourceMovesListCell* NewLeftNode = CreateNewListNode(0, CurrPos, NULL); // Making the new node with the desire value
		insertNodeToTail(lst, NewLeftNode);
	}
	else if (KindOfMove == RIGHT) { // Simple move to the right
		CurrPos = t->next_move[RIGHT]->Pos;
		SingleSourceMovesListCell* NewRightNode = CreateNewListNode(0, CurrPos, NULL); // Making the new node with the desire value
		insertNodeToTail(lst, NewRightNode);
	}
	else if (KindOfMove == BOTH) { // Choose randomly path
		int RandomPath = rand() % 2; // The rand function return only zero OR one
		OnlySimpleMove(t->next_move[RandomPath], lst, RandomPath); // Continue randomly with one option
	}
}

void ImpossibleMove(SingleSourceMoveTreeNode* t, SingleSourceMoveList* lst) { // Making a list with only one node, the current position
	SingleSourceMovesListCell* NewNode = CreateNewListNode(0, t->Pos, NULL); // Making the new node with the desire value
	insertNodeToHead(lst, NewNode);
}

void FreeMoveTreeRec(SingleSourceMoveTreeNode *node) { // Freeing the tree recursively
	if (node == NULL)
		return;
	FreeMoveTreeRec(node->next_move[LEFT]); // Free the sub left tree
	FreeMoveTreeRec(node->next_move[RIGHT]); // Free the sub right tree
	free(node->Pos); // Free pos
	free(node); // Free node
}

void FreeMoveTree(SingleSourceMoveTree *moves_tree) { // Calling the rec free function
	SingleSourceMoveTreeNode *root = moves_tree->source;
	FreeMoveTreeRec(root); // Freeing the tree
	free(moves_tree); // Freeing the root
}

SingleSourceMoveList* FindSingleSourceOptimalMoveS(SingleSourceMoveTree *moves_tree) { // Main function to find the most optimal move
	SingleSourceMoveList *LongestPathList = (SingleSourceMoveList*)malloc(sizeof(SingleSourceMoveList)); // Make a new list
	AllocationCheck(LongestPathList); // Checks the allocation
	MakeEmptyList(LongestPathList); // Make the list empty
	SingleSourceMoveTreeNode *t = moves_tree->source;
	char CurrPlayer = t->board[t->Pos->row - '0'][t->Pos->col - '0'];
	int KindOfMove = CheckNextStep(t->board, t->Pos, CurrPlayer); 
	unsigned short LongestRout;
	if (KindOfMove == -1) // If the next step is illegal
		ImpossibleMove(t, LongestPathList);
	 else if (KindOfMove >= 0 && KindOfMove <= 2) // If the next step is simple move
		OnlySimpleMove(t, LongestPathList, KindOfMove);
	else { // Otherwise the next step is capture
		LongestRout = FindThelongestpath(moves_tree->source) -1; // Get the longest path, reduce one because count number of nodes
		FindSingleSourceOptimalMovesRec(moves_tree->source, LongestPathList, &LongestRout); // Recursion call to find the optimal move sequence
	}
	FreeMoveTree(moves_tree);
	return LongestPathList; // Return new sequense list
}

SingleSourceMovesListCell* CreateNewListNode(unsigned short Captures, checkersPos *pos, SingleSourceMovesListCell* Next) { // Create new list node
	SingleSourceMovesListCell* NewCell = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell)); // Allocate new node
	AllocationCheck(NewCell); // Checks the allocation
	NewCell->position = (checkersPos*)malloc(sizeof(checkersPos)); // Allocate the position field in the new node
	AllocationCheck(NewCell->position); // Checks the allocation
	NewCell->captures = Captures; // New cell captures value
	NewCell->next = Next; // Make the node points to the next node
	NewCell->position->col = pos->col; // Give the new cell the position of column
	NewCell->position->row = pos->row; // Give the new cell the position of row
	return NewCell;
}