#include "Question_7.h"
#include "Question_4.h"
#include "Question_3.h"
#include "Question_2.h"
#include "Question_1.h"

void PrintBoard(Board board) {
	int i, j;
	printf("+-+-+-+-+-+-+-+-+-+\n"); // Print the first row
	printf("| |1|2|3|4|5|6|7|8|\n"); // Print the second line
	for (i = 0; i < BOARD_SIZE; i++) {
			printf("+-+-+-+-+-+-+-+-+-+\n|"); // Print the inbetween row
			printf("%c|", i + 'A'); // Print the indexes of the table
			for (j = 0; j < BOARD_SIZE; j++) {
				printf("%c|", board[i][j]); // Print the indexes of the table
			}
			printf("\n");
	}
	printf("+-+-+-+-+-+-+-+-+-+\n"); // Print the last row
}

int IsWin(Board board , Player *player) { // Find if a player has won in the last move  -- NEEDS TO ADD IF ALL SOLDIER HAS BEEN EATEN
	int i, j, countB = 0, countT = 0, flag = 0;
	if (board[0][0] != ' ') { // Checking for the special marking
		SwitchPlayer(player); // The other player wins
		return 1;
	}
	for (i = 0; i < BOARD_SIZE; i++) {
		if (board[0][i] == 'B') // If there is a 'B' in the first row
			return 1;
		if (board[BOARD_SIZE - 1][i] == 'T') // If there is a 'T' in the last row
			return 1;
	}
	for (i = 0; i < BOARD_SIZE; i++) { // This for check the board if there is a player that has no more pieces left
		if (i % 2 == 0) // Skip the irrelevant blocks
			j = 1;
		else
			j = 0;
		for (j = 0; j < BOARD_SIZE ; j++) {
			if (board[i][j] == 'B') // Count number of 'B's
				countB++; 
			if (board[i][j] == 'T') // Count number of 'T's
				countT++;
			if (countB > 0 && countT > 0) // If both of the player have at least 1 player then there is no win
				return 0;
		}
	}
	if (countB == 0 || countT == 0) // If one player have no more pieces left then there is a win 
		return 1;
	return 0; // If the program passed the "loop of fire" than return false
}

void SwitchPlayer(char* CurrPLayer) { // Switch players
	if (*CurrPLayer == 'T')
		*CurrPLayer = 'B';
	else
		*CurrPLayer = 'T';
}

void PlayGame(Board board, Player starting_player) {
	char CurrPlayer = starting_player;
	PrintBoard(board);
	Turn(board, CurrPlayer); // Do the first turn
	while (!IsWin(board, &CurrPlayer)) { // Untill someone has won
		SwitchPlayer(&CurrPlayer); // Every turn switch players
		Turn(board, CurrPlayer); // Do turn
	}
	printf("Player: %c WIN!!!\nGood job computer...\n", CurrPlayer);
}
