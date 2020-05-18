#pragma warning(disable: 4996)
#include "Question_7.h"
int main() {
	int i, j;
	Board Testboard3;
	for (i = 0; i < BOARD_SIZE; i++) 
		for (j = 0; j < BOARD_SIZE; j++) 
				Testboard3[i][j] = ' ';
	
	Testboard3[5][0] = Testboard3[5][2] = Testboard3[5][4] = Testboard3[5][6] = Testboard3[6][1] = Testboard3[6][5] = Testboard3[6][3]
		= Testboard3[6][7] = Testboard3[7][0] = Testboard3[7][2] = Testboard3[7][4] = Testboard3[7][6] = 'B';
	Testboard3[1][0] = Testboard3[1][2] = Testboard3[1][4] = Testboard3[1][6] = Testboard3[0][1] = Testboard3[0][5] = Testboard3[0][3]
		= Testboard3[0][7] = Testboard3[2][1] = Testboard3[2][5] = Testboard3[2][3] = Testboard3[2][7] = 'T';
	PlayGame(Testboard3, 'B');
	system("pause");
	return 0;
}
