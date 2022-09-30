#include "Reversi.h"

Reversi::Reversi(unsigned int colSize, unsigned  int rowSize){
	Reversi::rowSize = rowSize;
	Reversi::colSize = colSize;
	Reversi::turn = REVERSI_TURN_DARK;

	// create 2d array
	Reversi::board = new short*[colSize];
	for (unsigned int i = 0; i < colSize; i++)
		Reversi::board[i] = new short[rowSize];
}

void Reversi::NewGame() {
	Reversi::turn = REVERSI_TURN_DARK;
	Reversi::diskNum = 4;

	// init array value
	for (unsigned int i = 0; i < colSize; i++) {
		for (unsigned int j = 0; j < rowSize; j++) {
			Reversi::board[i][j] = REVERSI_BOARD_ELEMENT_EMPTY;
		}
	}

	Reversi::board[colSize / 2 - 1][rowSize / 2 - 1] = REVERSI_BOARD_ELEMENT_LIGHT;
	Reversi::board[colSize / 2 - 1][rowSize / 2 - 0] = REVERSI_BOARD_ELEMENT_DARK;
	Reversi::board[colSize / 2 - 0][rowSize / 2 - 1] = REVERSI_BOARD_ELEMENT_DARK;
	Reversi::board[colSize / 2 - 0][rowSize / 2 - 0] = REVERSI_BOARD_ELEMENT_LIGHT;

	ValidPosUpdate(Reversi::turn);
}

int Reversi::Put(unsigned int rowIdx, unsigned int colIdx) {
	return Put(rowIdx, colIdx, Reversi::turn);
}
int Reversi::Put(unsigned int rowIdx, unsigned int colIdx, bool turn) {
	//std::cout << "turn:" << (turn ? "dark " : "light") << "  ";
	//std::cout << "pos:" << rowIdx << ", " << colIdx;

	if (Reversi::board[rowIdx][colIdx] == REVERSI_BOARD_ELEMENT_VAILD_LIGHT) {
		if (turn == REVERSI_TURN_LIGHT) {
			Reversi::board[rowIdx][colIdx] = REVERSI_BOARD_ELEMENT_LIGHT;
			Reversi::diskNum = Reversi::diskNum + 1;
			// exchange color
			ReplaceColor(rowIdx, colIdx, Reversi::turn);

			if (Reversi::diskNum == Reversi::rowSize * Reversi::colSize) {
				unsigned int darkDiskNum = CountDisks(REVERSI_TURN_DARK);
				if (darkDiskNum > Reversi::rowSize * Reversi::colSize / 2)// dark win
					return REVERSI_RESULT_DARK;
				if (darkDiskNum < Reversi::rowSize * Reversi::colSize / 2)// light win
					return REVERSI_RESULT_LIGHT;
				if (darkDiskNum == Reversi::rowSize * Reversi::colSize / 2)// draw
					return REVERSI_RESULT_DRAW;
			}

			Reversi::turn = !Reversi::turn;
			// update vaild positions
			while(ValidPosUpdate(Reversi::turn) == 0)
				Reversi::turn = !Reversi::turn;
			return 0;
		}
	}
	if (Reversi::board[rowIdx][colIdx] == REVERSI_BOARD_ELEMENT_VAILD_DARK) {
		if (turn == REVERSI_TURN_DARK) {
			Reversi::board[rowIdx][colIdx] = REVERSI_BOARD_ELEMENT_DARK;
			Reversi::diskNum = Reversi::diskNum + 1;
			// exchange color
			ReplaceColor(rowIdx, colIdx, Reversi::turn);

			if (Reversi::diskNum == Reversi::rowSize * Reversi::colSize) {
				unsigned int darkDiskNum = CountDisks(REVERSI_TURN_DARK);
				if (darkDiskNum > Reversi::rowSize * Reversi::colSize / 2)// dark win
					return REVERSI_RESULT_DARK;
				if (darkDiskNum < Reversi::rowSize * Reversi::colSize / 2)// light win
					return REVERSI_RESULT_LIGHT;
				if (darkDiskNum == Reversi::rowSize * Reversi::colSize / 2)// draw
					return REVERSI_RESULT_DRAW;
			}

			Reversi::turn = !Reversi::turn;
			// update vaild positions
			while (ValidPosUpdate(Reversi::turn) == 0)
				Reversi::turn = !Reversi::turn;
			return 0;
		}
	}

	return 1;
}
unsigned int Reversi::CountDisks(bool Color) {
	const short targetElement = (Color == REVERSI_TURN_DARK) ? REVERSI_BOARD_ELEMENT_DARK : REVERSI_BOARD_ELEMENT_LIGHT;
	unsigned int num = 0;
	for (unsigned int rowIdx = 0; rowIdx < colSize; rowIdx++) {
		for (unsigned int colIdx = 0; colIdx < rowSize; colIdx++) {
			if (Reversi::board[rowIdx][colIdx] == targetElement) {
				num = num + 1;
			}
		}
	}
	return num;
}
void Reversi::ReplaceColor(unsigned int newRowIdx, unsigned int newColIdx, bool newColor){
	const int directions[] = { 1, 1, 1, 0, 1, -1, 0, -1, -1, -1, -1, 0, -1, 1, 0, 1 };
	for (unsigned int i = 0; i < 8; i++) {
		int directionX = directions[2 * i + 1];
		int directionY = directions[2 * i];
		int currRowIdx = newRowIdx + directionY;
		int currColIdx = newColIdx + directionX;

		// rule check
		while (currRowIdx >= 0 && currRowIdx < Reversi::colSize && currColIdx >= 0 && currColIdx < Reversi::rowSize) {
			if ( ((Reversi::board[currRowIdx][currColIdx] == REVERSI_BOARD_ELEMENT_LIGHT) && (newColor == REVERSI_TURN_DARK)) ||
				 ((Reversi::board[currRowIdx][currColIdx] == REVERSI_BOARD_ELEMENT_DARK) && (newColor == REVERSI_TURN_LIGHT)) ) {
				currRowIdx = currRowIdx + directionY;
				currColIdx = currColIdx + directionX;
			}
			else {
				break;
			}
		}
		
		if (!(currRowIdx >= 0 && currRowIdx < Reversi::colSize && currColIdx >= 0 && currColIdx < Reversi::rowSize))
			continue;

		// check if different color between the new piece and an anchoring piece
		if (!( ((Reversi::board[currRowIdx][currColIdx] == REVERSI_BOARD_ELEMENT_LIGHT) && (newColor == REVERSI_TURN_LIGHT)) ||
			   ((Reversi::board[currRowIdx][currColIdx] == REVERSI_BOARD_ELEMENT_DARK)  && (newColor == REVERSI_TURN_DARK ))    ))
			continue;
		
		// if true then exchange color
		currRowIdx = currRowIdx - directionY;
		currColIdx = currColIdx - directionX;
		while (currRowIdx >= 0 && currRowIdx < Reversi::colSize && currColIdx >= 0 && currColIdx < Reversi::rowSize) {
			if (currRowIdx != newRowIdx || currColIdx != newColIdx) {
				// exchange color
				if (Reversi::board[currRowIdx][currColIdx] == REVERSI_BOARD_ELEMENT_DARK)
					Reversi::board[currRowIdx][currColIdx] = REVERSI_BOARD_ELEMENT_LIGHT;
				else if (Reversi::board[currRowIdx][currColIdx] == REVERSI_BOARD_ELEMENT_LIGHT)
					Reversi::board[currRowIdx][currColIdx] = REVERSI_BOARD_ELEMENT_DARK;
				// next position
				currRowIdx = currRowIdx - directionY;
				currColIdx = currColIdx - directionX;
			}
			else {
				break;
			}
		}
	}
}

unsigned int Reversi::ValidPosUpdate(bool Color) {
	const short currElement = (Color == REVERSI_TURN_DARK) ? REVERSI_BOARD_ELEMENT_DARK : REVERSI_BOARD_ELEMENT_LIGHT;
	const short diffElement = (Color != REVERSI_TURN_DARK) ? REVERSI_BOARD_ELEMENT_DARK : REVERSI_BOARD_ELEMENT_LIGHT;
	const short validElement = (Color == REVERSI_TURN_DARK) ? REVERSI_BOARD_ELEMENT_VAILD_DARK : REVERSI_BOARD_ELEMENT_VAILD_LIGHT;
	
	// clear prev state
	for (unsigned int rowIdx = 0; rowIdx < colSize; rowIdx++) {
		for (unsigned int colIdx = 0; colIdx < rowSize; colIdx++) {
			if (Reversi::board[rowIdx][colIdx] == REVERSI_BOARD_ELEMENT_VAILD_DARK ||
				Reversi::board[rowIdx][colIdx] == REVERSI_BOARD_ELEMENT_VAILD_LIGHT)
				Reversi::board[rowIdx][colIdx] = REVERSI_BOARD_ELEMENT_EMPTY;
		}
	}

	unsigned int validNum = 0;
	for (unsigned int rowIdx = 0; rowIdx < colSize; rowIdx++) {
		for (unsigned int colIdx = 0; colIdx < rowSize; colIdx++) {
			if (Reversi::board[rowIdx][colIdx] != currElement) continue;

			const int directions[] = { 1, 1, 1, 0, 1, -1, 0, -1, -1, -1, -1, 0, -1, 1, 0, 1 };
			for (unsigned int i = 0; i < 8; i++) {
				int directionX = directions[2 * i + 1];
				int directionY = directions[2 * i];
				int currRowIdx = rowIdx + directionY;
				int currColIdx = colIdx + directionX;

				while (currRowIdx >= 0 && currRowIdx < Reversi::colSize && currColIdx >= 0 && currColIdx < Reversi::rowSize) {
					if (Reversi::board[currRowIdx][currColIdx] == diffElement) { // diff color disk
						currRowIdx = currRowIdx + directionY;
						currColIdx = currColIdx + directionX;
					}
					else break;
				}

				// if out of board
				if (!(currRowIdx >= 0 && currRowIdx < Reversi::colSize && currColIdx >= 0 && currColIdx < Reversi::rowSize))
					continue;
				// if it didnt have a disk
				if ((Reversi::board[currRowIdx][currColIdx] != diffElement && Reversi::board[currRowIdx][currColIdx] != currElement) &&
					// if there is different color disk between
					(Reversi::board[currRowIdx - directionY][currColIdx - directionX] == diffElement)) {

					if (Reversi::board[currRowIdx][currColIdx] != validElement) {
						validNum = validNum + 1;
						Reversi::board[currRowIdx][currColIdx] = validElement;
					}
				}
			}

		}
	}
	return validNum;
}

void Reversi::Delete() {
	for (unsigned int i = 0; i < Reversi::rowSize; i++)
		delete Reversi::board[i];
	delete Reversi::board;
}