#include "Question_5N6.h"

void LoadBoard(char *filename, Board board) { // This function store the board from the file to the variable 
	int i, j;
	FILE* f = fopen(filename, "rb"); // Open the file to read in binary mode
	unsigned char mask, CurrHalfRow; // Variable that keeps the current data
	for (i = 0; i < BOARD_SIZE; i++) { // Runs until the end of the board
		fread(&CurrHalfRow, sizeof(unsigned char), 1, f); // Read from the file the half of the current row
		for (j = 0; j < BOARD_SIZE; j++) {
			if (j == BOARD_SIZE / 2) // If the program got to the middle of the row
				fread(&CurrHalfRow, sizeof(unsigned char), 1, f); // Read again
			mask = CurrHalfRow & 192; // 192 = 11000000 -> MSB are lit
			if (mask == 64) // 64 = 01000000 -> MSB are 01
				board[i][j] = 'T';
			else if (mask == 128) // 128 = 1000000 -> MSBB are 10
				board[i][j] = 'B';
			else // the only other possible option is space
				board[i][j] = ' ';
			CurrHalfRow <<= 2; // Move to the next two digit
		}
		mask = 0; // Reset the variable
	}
	fclose(f); // close the file
}

void StoreBoard(Board board, char *filename) { // This function save the current board in the given file
	FILE *f = fopen(filename, "wb"); // Open the file in write binary mode
	unsigned char mask;
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++) { // Runds untill the end of the board
		mask = 0;
		if (i == 4)
		//	printf("hello");
		for (j = 0; j < BOARD_SIZE; j++) {
			if (j == BOARD_SIZE / 2) {
				fwrite(&mask, sizeof(unsigned char), 1, f); // Write the first half row
				mask = 0; // Reset the variable
			}
			mask <<= 2; // Move to the next two digit
			if (board[i][j] == 'T')
				mask |= 1; // Adds to the current mask the current location -> 1, T = 01
			else if (board[i][j] == 'B')
				mask |= 2; // Adds to the current mask the current location -> 2, B = 10
		}
		fwrite(&mask, sizeof(unsigned char), 1, f); // Write the second half of the row
	}
	fclose(f); // Close the file
}